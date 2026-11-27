#include "versus_build.h"
#include "versus_native_class_types.h"
#include "versus_canvas_materials.h"
#include "versus_lazy_archive.h"

template<class T> inline T Min(T A, T B) { return A <= B ? A : B; }
template<class T> inline T Max(T A, T B) { return A >= B ? A : B; }

template<> class TLazyArray<BYTE> : public FLazyLoader, public TArray<BYTE> {
public:
    void Load();
    void Unload() {
        if (SavedPos < 0) {
            Empty();
            SavedPos = -SavedPos;
        }
    }
};

struct FMipmapBase {
    BYTE *DataPtr;
    INT USize, VSize;
    BYTE UBits, VBits;
};

struct FMipmap : public FMipmapBase {
    TLazyArray<BYTE> DataArray;
};

// DXT block layout.
struct FDXTColorBlock {
    _WORD Color0;
    _WORD Color1;
    DWORD Indices;
};
struct FDXT3Block {
    DWORD Alpha[2];
    FDXTColorBlock Color;
};

void DecompressDXT1(const DWORD *Src, INT Width, INT Height, DWORD *Dest);
void DecompressDXT3(const DWORD *Src, INT Width, INT Height, DWORD *Dest);
void DecompressDXT5(const DWORD *Src, INT Width, INT Height, DWORD *Dest);

// 0xf30a0: a DXT3 surface with no transparency becomes DXT1; otherwise decompress to RGBA.
// Returns 1 when DXT1 data was produced.
UBOOL ConvertDXT3(INT USize, FDXT3Block *Src, INT VSize, UBOOL NoData, BYTE **Dest, UBOOL NoDXT1)
{
    DWORD AlphaBits = 0xffffffff;
    INT BlocksU = Max(USize / 4, 1);
    INT BlocksV = Max(VSize / 4, 1);
    INT Blocks = BlocksV * BlocksU;

    INT n = Blocks;
    DWORD *In = (DWORD *)Src;
    while (n--) {
        if (AlphaBits != 0xffffffff)
            break;
        AlphaBits = *In++;
        AlphaBits &= *In;
        In += 3;
    }

    if (AlphaBits == 0xffffffff && !NoDXT1) {
        DWORD *Out = (DWORD *)GMalloc->Malloc(Blocks * 8, L"new");
        *Dest = (BYTE *)Out;
        In = (DWORD *)Src + 2;
        for (INT i = 0; i < Blocks; i++) {
            if (((_WORD *)In)[1] > ((_WORD *)In)[0]) {
                // Colour 0 must be the larger for four-colour mode: swap and remap indices.
                *Out++ = (*In >> 16) + (*In << 16);
                In++;
                *Out++ = *In ^ 0x55555555;
            } else {
                *Out++ = *In++;
                *Out++ = *In;
            }
            In += 3;
        }
        return 1;
    }

    if (!NoData) {
        *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, L"new");
        DecompressDXT3((const DWORD *)Src, USize, VSize, (DWORD *)*Dest);
    }
    return 0;
}

struct FDXT5Block {
    _WORD Alpha;      // alpha0, alpha1
    _WORD AlphaBits[3];
    FDXTColorBlock Color;
};

// 0xf31b0: a DXT5 surface whose alpha endpoints are all opaque becomes DXT1.
UBOOL ConvertDXT5(INT USize, FDXT5Block *Src, INT VSize, UBOOL NoData, BYTE **Dest, UBOOL NoDXT1)
{
    _WORD AlphaEnds = 0xffff;
    INT BlocksU = Max(USize / 4, 1);
    INT BlocksV = Max(VSize / 4, 1);
    INT Blocks = BlocksV * BlocksU;

    INT n = Blocks;
    FDXT5Block *Block = Src;
    while (n--) {
        if (AlphaEnds != 0xffff)
            break;
        AlphaEnds = Block++->Alpha;
    }

    if (AlphaEnds == 0xffff && !NoDXT1) {
        DWORD *Out = (DWORD *)GMalloc->Malloc(Blocks * 8, L"new");
        *Dest = (BYTE *)Out;
        DWORD *In = (DWORD *)Src + 2;
        for (INT i = 0; i < Blocks; i++) {
            if (((_WORD *)In)[1] > ((_WORD *)In)[0]) {
                // Colour 0 must be the larger for four-colour mode: swap and remap indices.
                *Out++ = (*In >> 16) + (*In << 16);
                In++;
                *Out++ = *In ^ 0x55555555;
            } else {
                *Out++ = *In++;
                *Out++ = *In;
            }
            In += 3;
        }
        return 1;
    }

    if (!NoData) {
        *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, L"new");
        DecompressDXT5((const DWORD *)Src, USize, VSize, (DWORD *)*Dest);
    }
    return 0;
}

ETextureFormat UTexture::ConvertDXT(INT MipIndex, UBOOL NoDXT1, UBOOL NoData, BYTE **Dest)
{
    if (Mips(MipIndex).DataArray.Num() == 0)
        Mips(MipIndex).DataArray.Load();
    INT USize = Mips(MipIndex).USize;
    INT VSize = Mips(MipIndex).VSize;
    UBOOL ToDXT1 = 0;
    switch (Format) {
    case TEXF_DXT1: {
        BYTE *Data = (BYTE *)Mips(MipIndex).DataArray.Data;
        if (!NoData) {
            *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, L"new");
            DecompressDXT1((const DWORD *)Data, USize, VSize, (DWORD *)*Dest);
        }
        ToDXT1 = 0;
        break;
    }
    case TEXF_DXT3:
        ToDXT1 = ConvertDXT3(USize, (FDXT3Block *)Mips(MipIndex).DataArray.Data, VSize, NoData, Dest, NoDXT1);
        break;
    case TEXF_DXT5:
        ToDXT1 = ConvertDXT5(USize, (FDXT5Block *)Mips(MipIndex).DataArray.Data, VSize, NoData, Dest, NoDXT1);
        break;
    }
    Mips(MipIndex).DataArray.TLazyArray<BYTE>::Unload();
    return ToDXT1 ? TEXF_DXT1 : TEXF_RGBA8;
}

void DecompressDXT1(const DWORD *Src, INT Width, INT Height, DWORD *Dest)
{
    INT BlockW = Min(4, Width);
    INT BlockH = Min(4, Height);
    DWORD *End = Dest + Width * Height;
    const DWORD *In = Src;
    DWORD *Block = Dest;
    for (INT by = 0; by < Max(Height / 4, 1); by++)
    {
        for (INT bx = 0; bx < Max(Width / 4, 1); bx++)
        {
            DWORD Colors = In[0];
            DWORD Indices = In[1];
            In += 2;
            DWORD Color[4];
            // Expand the two RGB565 end points to 8 bits per channel, in place.
            DWORD R0 = (((Colors & 0xf800) << 5) | (Colors & 0xe000)) << 3;
            DWORD G0 = ((Colors & 0x07e0) << 5) | ((Colors >> 1) & 0x300);
            DWORD B0 = ((Colors & 0x001f) << 3) | ((Colors >> 2) & 0x7);
            DWORD R1 = ((Colors & 0xf8000000) | ((Colors >> 5) & 0x7000000)) >> 8;
            DWORD G1 = (((Colors >> 6) & 0x180000) | (Colors & 0x7e00000)) >> 11;
            DWORD B1 = (((Colors >> 5) & 0xe000) | (Colors & 0x1f0000)) >> 13;
            Color[0] = B0 | G0 | R0;
            Color[1] = B1 | G1 | R1;
            Color[2] = (((G1 * 11 + G0 * 21) & 0x1fe000) | ((B1 * 11 + B0 * 21) & 0x1fe0) | ((R1 * 11 + R0 * 21) & 0x1fe00000)) >> 5;
            Color[3] = (((G1 * 21 + G0 * 11) & 0x1fe000) | ((B1 * 21 + B0 * 11) & 0x1fe0) | ((R1 * 21 + R0 * 11) & 0x1fe00000)) >> 5;

            const INT UseTransparent = Color[0] <= Color[1];
            DWORD *Row = Block;
            for (INT y = 0; y < BlockH; y++)
            {
                for (INT x = 0; x < BlockW; x++)
                {
                    DWORD *Pixel = &Row[x];
                    if (Pixel >= End)
                        return;
                    DWORD Index = Indices & 3;
                    if (Index == 3 && UseTransparent)
                        *Pixel = Color[Index];
                    else
                        *Pixel = Color[Index] | 0xff000000;
                    Indices >>= 2;
                }
                Row += Width;
            }
            Block += 4;
        }
        Block += Width * 3;
    }
}

void DecompressDXT3(const DWORD *Src, INT Width, INT Height, DWORD *Dest)
{
    INT BlockW = Min(4, Width);
    INT BlockH = Min(4, Height);
    DWORD *End = Dest + Width * Height;
    const DWORD *In = Src;
    for (INT by = 0; by < Max(Height / 4, 1); by++)
    {
        for (INT bx = 0; bx < Max(Width / 4, 1); bx++)
        {
            DWORD AlphaLo = In[0];
            DWORD AlphaHi = In[1];
            DWORD Colors  = In[2];
            DWORD Indices = In[3];
            In += 4;

            DWORD Color[4];
            // Expand the two RGB565 end points to 8 bits per channel, in place.
            DWORD R0 = (((Colors & 0xf800) << 5) | (Colors & 0xe000)) << 3;
            DWORD G0 = ((Colors & 0x07e0) << 5) | ((Colors >> 1) & 0x300);
            DWORD B0 = ((Colors & 0x001f) << 3) | ((Colors >> 2) & 0x7);
            DWORD R1 = ((Colors & 0xf8000000) | ((Colors >> 5) & 0x7000000)) >> 8;
            DWORD G1 = (((Colors >> 6) & 0x180000) | (Colors & 0x7e00000)) >> 11;
            DWORD B1 = (((Colors >> 5) & 0xe000) | (Colors & 0x1f0000)) >> 13;
            Color[0] = B0 | G0 | R0;
            Color[1] = B1 | G1 | R1;
            Color[2] = (((G1 * 11 + G0 * 21) & 0x1fe000) | ((B1 * 11 + B0 * 21) & 0x1fe0) | ((R1 * 11 + R0 * 21) & 0x1fe00000)) >> 5;
            Color[3] = (((G1 * 21 + G0 * 11) & 0x1fe000) | ((B1 * 21 + B0 * 11) & 0x1fe0) | ((R1 * 21 + R0 * 11) & 0x1fe00000)) >> 5;

            DWORD *Row = Dest;
            for (INT y = 0; y < BlockH; y++)
            {
                DWORD *Pixel = Row;
                for (INT x = 0; x < BlockW; x++, Pixel++)
                {
                    if (Pixel >= End)
                        return;
                    DWORD Alpha;
                    if (y < 2) {
                        Alpha = AlphaLo;
                        AlphaLo >>= 4;
                    } else {
                        Alpha = AlphaHi;
                        AlphaHi >>= 4;
                    }
                    *Pixel = (((Alpha & 15) | (Alpha << 4)) << 24) | Color[Indices & 3];
                    Indices >>= 2;
                }
                Row += Width;
            }
            Dest += BlockW;
        }
        Dest += Width * 3;
    }
}

#include "versus_dxt5_decode.inl"
