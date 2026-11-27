#include "versus_build.h"
#include "versus_shadow_bitmap_material.h"
#include "versus_solid_color_texture.h"

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
