#ifndef VERSUS_SHADOW_BITMAP_MATERIAL_H
#define VERSUS_SHADOW_BITMAP_MATERIAL_H

#include "versus_build.h"
#include "unreal_math.h"
#include "versus_canvas_materials.h"

class AActor;

// Engine.ShadowBitmapMaterial is 0x94 bytes. The script declaration exposes
// the two native texture interfaces as a fixed two-element integer array.
class UShadowBitmapMaterial : public UBitmapMaterial {
public:
    virtual ~UShadowBitmapMaterial();
    virtual FRenderResource *GetRenderInterface();

    FRenderResource *TextureInterfaces[2];
    AActor *ShadowActor;
    FVector LightDirection;
    FLOAT LightDistance;
    FLOAT LightFOV;
    BITFIELD Dirty : 1;
    BITFIELD Invalid : 1;
    BITFIELD bBlobShadow : 1;
    FLOAT CullDistance;
    BYTE ShadowDarkness;
    UBitmapMaterial *BlobShadow;
};

#endif
