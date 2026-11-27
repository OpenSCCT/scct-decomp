#include "versus_build.h"
#include "versus_shadow_bitmap_material.h"
#include "versus_solid_color_texture.h"
#include "versus_static_textures.h"
#include "versus_cubemap.h"
#include "versus_malloc.h"

unsigned __int64 GCacheCounter;

enum ECacheIDBase {
    CID_RenderTexture = 0xe0
};

// MakeCacheID reserves the low eight bits for the resource kind.
static inline unsigned __int64 MakeCacheID(ECacheIDBase Base)
{
    return GCacheCounter++ * 256 + Base;
}

// FSolidColorTexture::FSolidColorTexture assigns the one-texel resource a fresh cache ID.
__declspec(noinline) FSolidColorTexture::FSolidColorTexture(FColor InColor)
    : Color(InColor), Revision(1)
{
    CacheId = MakeCacheID(CID_RenderTexture);
}

static inline FColor MakeGrey(BYTE Value)
{
    FColor Color;
    Color.B = Value;
    Color.G = Value;
    Color.R = Value;
    Color.A = 255;
    return Color;
}

// UShadowBitmapMaterial::GetRenderInterface uses a single grey texel until the shadow is valid.
FRenderResource *UShadowBitmapMaterial::GetRenderInterface()
{
    static FSolidColorTexture GreyTexture(MakeGrey(127));
    if (Invalid)
        return &GreyTexture;
    return TextureInterfaces[0];
}

FStaticTexture::FStaticTexture(UTexture *InOwner)
    : Owner(InOwner)
{
    CacheId = MakeCacheID(CID_RenderTexture);
    Revision = 1;
}

FStaticCubemap::FStaticCubemap(UCubemap *InOwner)
    : Owner(InOwner)
{
    CacheId = MakeCacheID(CID_RenderTexture);
    Revision = 1;
}

// For a cubemap with faces, dimensions, mip levels and address modes come from face zero.
INT FStaticCubemap::GetWidth()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetWidth();
    return 4;
}

INT FStaticCubemap::GetHeight()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetHeight();
    return 4;
}

INT FStaticCubemap::GetFirstMip()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetFirstMip();
    return 0;
}

INT FStaticCubemap::GetNumMips()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetNumMips();
    return 1;
}

ETextureFormat FStaticCubemap::GetFormat()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetFormat();
    return TEXF_RGBA8;
}

ETexClampMode FStaticCubemap::GetUClamp()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetUClamp();
    return TC_Wrap;
}

ETexClampMode FStaticCubemap::GetVClamp()
{
    if (Owner->Faces[0])
        return FStaticTexture(Owner->Faces[0]).GetVClamp();
    return TC_Wrap;
}

INT FStaticCubemap::GetRevision()
{
    if (Owner->bRealtimeChanged) {
        ++Revision;
        Owner->bRealtimeChanged = 0;
    }
    for (INT i = 0; i < 6; ++i) {
        if (Owner->Faces[i] && Owner->Faces[i]->bRealtimeChanged) {
            ++Revision;
            Owner->Faces[i]->bRealtimeChanged = 0;
        }
    }
    return Revision;
}

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}

inline void operator delete(void *Data, const TCHAR *)
{
    GMalloc->Free(Data);
}

UCubemap::UCubemap()
{
    CubemapInterface = new(L"new") FStaticCubemap(this);
}


unsigned __int64 FStaticTexture::GetCacheId()
{
    return CacheId;
}

INT FStaticTexture::GetRevision()
{
    if (Owner->bRealtimeChanged) {
        ++Revision;
        Owner->bRealtimeChanged = 0;
    }
    return Revision;
}

INT FStaticTexture::GetWidth() { return Owner->USize; }
INT FStaticTexture::GetHeight() { return Owner->VSize; }
INT FStaticTexture::GetNumMips() { return Owner->Mips.Num(); }
ETextureFormat FStaticTexture::GetFormat() { return static_cast<ETextureFormat>(Owner->Format); }
ETexClampMode FStaticTexture::GetUClamp() { return static_cast<ETexClampMode>(Owner->UClampMode); }
ETexClampMode FStaticTexture::GetVClamp() { return static_cast<ETexClampMode>(Owner->VClampMode); }
