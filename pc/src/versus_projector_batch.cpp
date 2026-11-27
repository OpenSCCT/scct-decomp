#include "versus_build.h"
#include "versus_native_class_init.h"
#include "versus_construct_object.h"
#include "versus_global_temp_objects.h"
#include "versus_projector_material.h"
#include "versus_composite_projector_streams.h"
#include "versus_render_interface.h"
#include "versus_render_transform_target.h"
#include "versus_canvas_matrix.h"
#include "versus_projector_batch.h"
#include "versus_sphere.h"

inline void FRenderInterface::EnableLighting(INT Dynamic, INT Static, INT Modulate, INT LightingOnly, FSphere LightSphere)
{
    TransformTarget->EnableLighting(this, Dynamic, Static, Modulate, LightingOnly, LightSphere);
}

inline void FRenderInterface::SetMaterial(UMaterial *Material, INT Flags)
{
    TransformTarget->SetMaterial(this, Material, Flags);
}

inline INT FRenderInterface::SetDynamicStream(INT Index, FVertexStream *Stream)
{
    return TransformTarget->SetDynamicStream(this, Index, Stream);
}

extern UObject *GObjTransientPkg;
extern UGlobalTempObjects *GGlobalTempObjects;
extern FVector *GZeroVector;
// The CRT constructs this object at 0x2d9bb0. The Engine registrar initializes its class metadata later.
UClass UProjectorMaterial::PrivateStaticClass(0);

enum { PT_TriangleList = 0 };

template<class T> inline T *CastVisionMaterial(UMaterial *Material)
{
    return Material && Material->IsA(&T::PrivateStaticClass) ? static_cast<T *>(Material) : 0;
}

// Heat and EMF materials can wrap each other. Projectors use the underlying material.
UMaterial *UnwrapVisionMaterial(UMaterial *Material)
{
    if (USpecialVisionTextureModifier *Vision = CastVisionMaterial<USpecialVisionTextureModifier>(Material))
        return Vision->Material;
    if (UHeatTextureModifier *Heat = CastVisionMaterial<UHeatTextureModifier>(Material)) {
        UMaterial *Inner = Heat->Material;
        UEMFTextureModifier *EMF = CastVisionMaterial<UEMFTextureModifier>(Inner);
        return EMF ? EMF->Material : Inner;
    }
    if (UEMFTextureModifier *EMF = CastVisionMaterial<UEMFTextureModifier>(Material)) {
        UMaterial *Inner = EMF->Material;
        UHeatTextureModifier *Heat = CastVisionMaterial<UHeatTextureModifier>(Inner);
        return Heat ? Heat->Material : Inner;
    }
    return Material;
}

inline FCompositeVertexStream::FCompositeVertexStream(FProjectorRenderBatch *InInfo)
    : Info(InInfo), Size(InInfo->VertexDataSize)
{
    Stride = Info->BaseMaterial ? 0x24 : 0x1c;
}

inline FCompositeIndexBuffer::FCompositeIndexBuffer(FProjectorRenderBatch *InInfo)
    : Info(InInfo), Size((INT)InInfo->IndexDataSize)
{
}

// Retail RVA 0x14a9c0
void FProjectorRenderBatch::Render(FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    static UProjectorMaterial *Material;

    if (!Material) {
        Material = static_cast<UProjectorMaterial *>(ConstructObject(
            &UProjectorMaterial::PrivateStaticClass, GObjTransientPkg));
        GGlobalTempObjects->GlobalObjectPtrs.AddItem(reinterpret_cast<UObject **>(&Material));
        Material->bStaticProjector = 1;
    }

    Material->Projected = ProjectedMaterial;
    Material->BaseMaterial = UnwrapVisionMaterial(BaseMaterial);
    Material->BaseMaterialBlending = (BYTE)MaterialBlendingOp;
    Material->FrameBufferBlending = (BYTE)FrameBufferBlendingOp;
    Material->bStaticProjector = 1;
    Material->bBorderClampMode = bBorderClampMode;
    Material->bTwoSided = bTwoSided;

    RI->PushState();
    RI->EnableLighting(0, 1, 0, 0, FSphere(*GZeroVector, 0.0f));
    RI->SetMaterial(Material, 0);
    RI->SetZBias(1);

    FCompositeVertexStream VertexStream(this);
    FCompositeIndexBuffer IndexBuffer(this);

    INT BaseVertexIndex = RI->SetDynamicStream(0, &VertexStream);
    INT BaseIndex = RI->SetDynamicIndexBuffer(&IndexBuffer, BaseVertexIndex);
    RI->DrawPrimitive(PT_TriangleList, BaseIndex, IndexDataSize / (3 * sizeof(_WORD)),
                      0, VertexDataSize / VertexStride - 1);
    RI->PopState();
}
