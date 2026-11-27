// Work item 0248: UPalette constructor and Serialize, texture DXT conversion helpers.
// Engine object, compiled with /GL and linked /LTCG (custom register conventions).
//   0xf2ee0 UPalette::UPalette         MATCH  try_ltcg /O2 /Ob1 /Gy, root Driver_f2ee0
//   0xf2f00 UPalette::Serialize        MATCH  try_ltcg /O2 /Gy (root itself)
//   0xf2f60 UTexture::ConvertMip       near: 10 bytes, DecompressDXT1 (0xf32d0) scaffold gets Dest in
//                                      ECX instead of EDX; needs the real 0xf32d0 body
//   0xf30a0 ConvertDXT3                near: 31 bytes, register allocation of BlocksU/alpha loads
// Functions marked as scaffolding below exist only so the link chooses retail's registers.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef DWORD UBOOL;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Allocation tag at 0x10c109d8 (text not recovered).
extern const TCHAR DXTConvertTag[];

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(class UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    FArchive &operator<<(BYTE &B) { Serialize(&B, 1); return *this; }
};

struct FCompactIndex { INT Value; };
FArchive &operator<<(FArchive &Ar, FCompactIndex &I); // 0x1ea40, defined in the scaffolding
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);   // 0x44e0
    void Empty(INT ElementSize, INT Slack); // 0x4550
    INT Num() const { return ArrayNum; }
};

struct FColor {
    BYTE B, G, R, A;
};

inline FArchive &operator<<(FArchive &Ar, FColor &C)
{
    return Ar << C.R << C.G << C.B << C.A;
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// TArray<FColor> serializer (0xf48e0).
FArchive &operator<<(FArchive &Ar, FArray &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FColor), A.ArrayMax * sizeof(FColor));
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(FColor), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << ((FColor *)A.Data)[A.Add(1, sizeof(FColor))];
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << ((FColor *)A.Data)[i];
    }
    return Ar;
}

class UObject {
public:
    BYTE ObjectPad[0x28 - 4];
    UObject() {}
    virtual ~UObject();
    void Serialize(FArchive &Ar); // 0x15f50
};

class UPalette : public UObject {
public:
    FArray Colors; // 0x28
    INT Field34;   // 0x34
    INT Field38;   // 0x38, serialized from version 163
    UPalette();
    virtual ~UPalette();
    void Serialize(FArchive &Ar);
};

UPalette::UPalette() // 0xf2ee0
    : Field34(0), Field38(0)
{
}

void UPalette::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << Colors;
    if (Ar.Ver() < 66) {
        for (INT i = 0; i < Colors.Num(); i++)
            ((FColor *)Colors.Data)[i].A = 255;
    }
    if (Ar.Ver() >= 163)
        Ar.Serialize(&Field38, 4);
}

inline INT Min(INT A, INT B) { return A <= B ? A : B; }
inline INT Max(INT A, INT B) { return A >= B ? A : B; }

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

void DecompressDXT3(FDXT3Block *Src, INT USize, INT VSize, DWORD *Dest); // 0xf3560
struct FDXT5Block;
void DecompressDXT5(FDXT5Block *Src, INT USize, INT VSize, DWORD *Dest);
void DecompressDXT1(BYTE *Src, INT USize, INT VSize, DWORD *Dest);    // 0xf32d0

// 0xf30a0: a DXT3 surface with no transparency becomes DXT1; otherwise decompress to RGBA.
// Returns 1 when DXT1 data was produced.
UBOOL ConvertDXT3(INT USize, FDXT3Block *Src, INT VSize, UBOOL NoData, BYTE **Dest, UBOOL NoDXT1)
{
    INT BlocksU = USize / 4;
    DWORD AlphaBits = 0xffffffff;
    if (BlocksU < 1)
        BlocksU = 1;
    INT BlocksV = VSize / 4;
    if (BlocksV < 1)
        BlocksV = 1;
    INT Blocks = BlocksV * BlocksU;

    DWORD *In = (DWORD *)Src;
    for (INT n = Blocks; n--; ) {
        if (AlphaBits != 0xffffffff)
            break;
        DWORD A0 = *In++;
        AlphaBits = A0 & *In;
        In += 3;
    }

    if (AlphaBits == 0xffffffff && !NoDXT1) {
        DWORD *Out = (DWORD *)GMalloc->Malloc(Blocks * 8, DXTConvertTag);
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
        *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, DXTConvertTag);
        DecompressDXT3(Src, USize, VSize, (DWORD *)*Dest);
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
    INT BlocksU = USize / 4;
    if (BlocksU < 1)
        BlocksU = 1;
    _WORD AlphaEnds = 0xffff;
    INT BlocksV = VSize / 4;
    if (BlocksV < 1)
        BlocksV = 1;
    INT Blocks = BlocksV * BlocksU;

    FDXT5Block *Block = Src;
    for (INT n = Blocks; n--; Block++) {
        if (AlphaEnds != 0xffff)
            break;
        AlphaEnds = Block->Alpha;
    }

    if (AlphaEnds == 0xffff && !NoDXT1) {
        DWORD *Out = (DWORD *)GMalloc->Malloc(Blocks * 8, DXTConvertTag);
        *Dest = (BYTE *)Out;
        FDXTColorBlock *Color = &Src->Color;
        for (INT i = 0; i < Blocks; i++) {
            if (Color->Color1 > Color->Color0) {
                DWORD Colors = *(DWORD *)Color;
                *Out++ = (Colors >> 16) + (Colors << 16);
                *Out++ = Color->Indices ^ 0x55555555;
            } else {
                *Out++ = *(DWORD *)Color;
                *Out++ = Color->Indices;
            }
            Color = (FDXTColorBlock *)((BYTE *)Color + sizeof(FDXT5Block));
        }
        return 1;
    }

    if (!NoData) {
        *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, DXTConvertTag);
        DecompressDXT5(Src, USize, VSize, (DWORD *)*Dest);
    }
    return 0;
}

class FLazyLoader {
public:
    virtual void Load() = 0;
    virtual ~FLazyLoader();
    FArchive *SavedAr;
    INT SavedPos;
};

class FLazyByteArray : public FLazyLoader, public FArray {
public:
    void Load();
    // Frees lazily loaded data again (inlined at every use).
    void Unload()
    {
        if (SavedPos < 0) {
            ArrayNum = 0;
            if (Data) {
                GMalloc->Free(Data);
                Data = 0;
                ArrayMax = 0;
            }
            SavedPos = -SavedPos;
        }
    }
};

struct FMipmap {
    BYTE *DataPtr;
    INT USize;
    INT VSize;
    BYTE UBits, VBits;
    FLazyByteArray DataArray; // 0x10
};

#include "versus_texture_format.h"

class UTexture : public UObject {
public:
    BYTE Pad28[0x5c - 0x28];
    BYTE Format;          // 0x5c
    BYTE Pad5d[0x70 - 0x5d];
    FMipmap *MipsData;    // 0x70
    INT MipsNum;
    INT MipsMax;
    BYTE ConvertMip(INT MipIndex, UBOOL NoDXT1, UBOOL NoData, BYTE **Dest);
};

// 0xf2f60: hands a renderer that lacks DXT3/DXT5 (or DXT1) either DXT1 or RGBA8 data
// for one mip. Returns the format of the data written to *Dest.
BYTE UTexture::ConvertMip(INT MipIndex, UBOOL NoDXT1, UBOOL NoData, BYTE **Dest)
{
    if (MipsData[MipIndex].DataArray.Num() == 0)
        MipsData[MipIndex].DataArray.Load();
    INT USize = MipsData[MipIndex].USize;
    INT VSize = MipsData[MipIndex].VSize;
    UBOOL ToDXT1 = 0;
    switch (Format) {
    case TEXF_DXT1: {
        BYTE *Data = (BYTE *)MipsData[MipIndex].DataArray.Data;
        if (!NoData) {
            *Dest = (BYTE *)GMalloc->Malloc(USize * VSize * 4, DXTConvertTag);
            DecompressDXT1(Data, USize, VSize, (DWORD *)*Dest);
        }
        ToDXT1 = 0;
        break;
    }
    case TEXF_DXT3:
        ToDXT1 = ConvertDXT3(USize, (FDXT3Block *)MipsData[MipIndex].DataArray.Data, VSize, NoData, Dest, NoDXT1);
        break;
    case TEXF_DXT5:
        ToDXT1 = ConvertDXT5(USize, (FDXT5Block *)MipsData[MipIndex].DataArray.Data, VSize, NoData, Dest, NoDXT1);
        break;
    }
    MipsData[MipIndex].DataArray.Unload();
    return ToDXT1 ? TEXF_DXT1 : TEXF_RGBA8;
}

// ---- Scaffolding for the link, not part of the unit. ----
void Escape(void *);
void *AllocateObject(INT Kind);
UPalette *Driver_f2ee0(INT Kind)
{
    void *Mem = AllocateObject(Kind);
    UPalette *P = Mem ? new(Mem) UPalette : 0;
    Escape(P);
    Mem = AllocateObject(Kind + 1);
    return Mem ? new(Mem) UPalette : 0;
}
BYTE Driver_f2f60(UTexture *(*Get)(), INT Mip, UBOOL NoDXT1, BYTE **D)
{
    Escape(&GMalloc);
    BYTE A = Get()->ConvertMip(Mip, NoDXT1, 0, D);
    return A + Get()->ConvertMip(Mip + 1, 0, 0, D);
}
// Expands both 5:6:5 end points and the two interpolated colours of a block.
inline void DecodeColors(DWORD C, DWORD *Colors)
{
    DWORD R0 = ((C >> 8) & 0xf8) | ((C >> 13) & 7);
    DWORD G0 = ((C >> 3) & 0xfc) | ((C >> 9) & 3);
    DWORD B0 = ((C << 3) & 0xf8) | ((C >> 2) & 7);
    DWORD R1 = ((C >> 24) & 0xf8) | ((C >> 29) & 7);
    DWORD G1 = ((C >> 19) & 0xfc) | ((C >> 25) & 3);
    DWORD B1 = ((C >> 13) & 0xf8) | ((C >> 18) & 7);
    Colors[0] = (R0 << 16) | (G0 << 8) | B0;
    Colors[1] = (R1 << 16) | (G1 << 8) | B1;
    Colors[2] = (((R0 * 21 + R1 * 11) >> 5) << 16) | (((G0 * 21 + G1 * 11) >> 5) << 8) | ((B0 * 21 + B1 * 11) >> 5);
    Colors[3] = (((R0 * 11 + R1 * 21) >> 5) << 16) | (((G0 * 11 + G1 * 21) >> 5) << 8) | ((B0 * 11 + B1 * 21) >> 5);
}
void DecompressDXT1(BYTE *Src, INT USize, INT VSize, DWORD *Dest)
{
    INT BW = Min(4, USize), BH = Min(4, VSize);
    DWORD *End = Dest + USize * VSize;
    DWORD *Row = Dest;
    FDXTColorBlock *Block = (FDXTColorBlock *)Src;
    for (INT by = 0; by < Max(VSize / 4, 1); by++, Row += USize * 4) {
        DWORD *Out = Row;
        for (INT bx = 0; bx < Max(USize / 4, 1); bx++, Block++, Out += 4) {
            DWORD C = *(DWORD *)Block;
            DWORD Colors[4];
            Colors[0] = ((C & 0xf800) << 8) | ((C & 0x7e0) << 5) | ((C & 0x1f) << 3);
            Colors[1] = ((C >> 8) & 0xf80000) | ((C >> 11) & 0xfc00) | ((C >> 13) & 0xf8);
            Colors[2] = Colors[0] / 2 + Colors[1] / 2;
            Colors[3] = 0;
            DWORD Bits = Block->Indices;
            for (INT y = 0; y < BH; y++)
                for (INT x = 0; x < BW; x++, Bits >>= 2) {
                    DWORD *P = Out + y * USize + x;
                    if (P < End)
                        *P = Colors[Bits & 3];
                }
        }
    }
}
void DecompressDXT3(FDXT3Block *Src, INT USize, INT VSize, DWORD *Dest)
{
    INT BW = Min(4, USize), BH = Min(4, VSize);
    DWORD *End = Dest + USize * VSize;
    for (INT by = 0; by < Max(VSize / 4, 1); by++)
        for (INT bx = 0; bx < Max(USize / 4, 1); bx++, Src++) {
            DWORD Colors[4];
            DecodeColors(*(DWORD *)&Src->Color, Colors);
            DWORD Alpha0 = Src->Alpha[0], Alpha1 = Src->Alpha[1];
            DWORD Bits = Src->Color.Indices;
            DWORD *Row = Dest + (by * 4) * USize + bx * 4;
            for (INT y = 0; y < BH; y++, Row += USize) {
                DWORD *P = Row;
                for (INT x = 0; x < BW; x++, Bits >>= 2) {
                    if (P >= End)
                        return;
                    DWORD A = y < 2 ? Alpha0 : Alpha1;
                    A = (A >> (((y & 1) * 4 + x) * 4)) & 15;
                    *P++ = Colors[Bits & 3] | (A * 17) << 24;
                }
            }
        }
}
void DecompressDXT5(FDXT5Block *Src, INT USize, INT VSize, DWORD *Dest)
{
    INT BW = Min(4, USize), BH = Min(4, VSize);
    DWORD *End = Dest + USize * VSize;
    for (INT by = 0; by < Max(VSize / 4, 1); by++)
        for (INT bx = 0; bx < Max(USize / 4, 1); bx++, Src++) {
            DWORD Colors[4];
            DecodeColors(*(DWORD *)&Src->Color, Colors);
            for (INT y = 0; y < BH; y++)
                for (INT x = 0; x < BW; x++) {
                    DWORD *P = Dest + (by * 4 + y) * USize + bx * 4 + x;
                    if (P < End)
                        *P = Colors[(Src->Color.Indices >> (2 * (y * 4 + x))) & 3] | ((DWORD)(Src->Alpha & 0xff) << 24);
                }
        }
}

// Compact index serializer (0x1ea40, another unit), so the link gives it its retail registers.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    BYTE B0 = (I.Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40);
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40) {
        V >>= 6;
        BYTE B1 = V < 0x80 ? V : (V & 0x7f) + 0x80;
        Ar << B1;
        if (B1 & 0x80) {
            V >>= 7;
            BYTE B2 = V < 0x80 ? V : (V & 0x7f) + 0x80;
            Ar << B2;
            if (B2 & 0x80) {
                V >>= 7;
                BYTE B3 = V < 0x80 ? V : (V & 0x7f) + 0x80;
                Ar << B3;
                if (B3 & 0x80) {
                    V >>= 7;
                    BYTE B4 = V;
                    Ar << B4;
                    I.Value = B4;
                }
                I.Value = (I.Value << 7) + (B3 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B2 & 0x7f);
        }
        I.Value = (I.Value << 7) + (B1 & 0x7f);
    }
    I.Value = (I.Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}
