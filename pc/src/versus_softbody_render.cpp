#include "versus_build.h"
#include "versus_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_scene_level_types.h"
#include "versus_softbody.h"
#include "versus_dynamic_actor.h"
#include "versus_matrix_types.h"
#include "versus_projector_render_info.h"
#include "versus_projector_primitives.h"
#include "versus_mem_stack.h"

TList<FProjectorRenderBatch *> *GProjectorList;

inline FProjectorRenderBatch::FProjectorRenderBatch(UMaterial *Base, FProjectorRenderInfo *Info, UBOOL TwoSided)
    : BaseMaterial(Base), ProjectedMaterial(Info->Material), MaterialBlendingOp(Info->MaterialBlendingOp),
      FrameBufferBlendingOp(Info->FrameBufferBlendingOp), bTwoSided(TwoSided),
      bBorderClampMode((Info->ProjectorFlags & PRF_BorderClampMode) != 0), VertexDataSize(0), IndexDataSize(0)
{
    VertexStride = 28;
    if (Base)
        VertexStride = 36;
}

void FProjectorPrimitiveList::Add(FProjectorPrimitive *Primitive)
{
    if (!LastChunk || NumPrimitives - LastChunk->FirstPrimitiveIndex == 32) {
        FProjectorPrimitiveChunk *Chunk = new(GSceneMem) FProjectorPrimitiveChunk;
        Chunk->Next = 0;
        if (LastChunk) {
            Chunk->FirstPrimitiveIndex = LastChunk->FirstPrimitiveIndex + 32;
            LastChunk->Next = Chunk;
        } else {
            Chunk->FirstPrimitiveIndex = 0;
            FirstChunk = Chunk;
        }
        LastChunk = Chunk;
    }
    LastChunk->Primitives[NumPrimitives - LastChunk->FirstPrimitiveIndex] = Primitive;
    ++NumPrimitives;
}

void UESoftBody::Render(FDynamicActor *DynamicActor, FLevelSceneNode *SceneNode, FDynamicLightList *Lights,
                        TList<FProjectorRenderInfo *> *Projectors, FRenderInterface *RI)
{
    LastRenderTime = Owner->Level->TimeSeconds;
    AActor *Actor = DynamicActor->Actor;
    for (INT Index = 0; Index < Actor->StaticProjectors.Num(); ++Index) {
        FStaticProjectorInfo *Ref = Actor->StaticProjectors(Index);
        if (!Ref->RenderInfo->Render(DynamicActor->Actor->Level->TimeSeconds)) {
            delete Actor->StaticProjectors(Index);
            Actor->StaticProjectors.Remove(Index--);
        } else {
            FProjectorRenderBatch *Batch = 0;
            for (TList<FProjectorRenderBatch *> *Link = GProjectorList; Link; Link = Link->Next) {
                FProjectorRenderBatch *B = Link->Element;
                if (B->ProjectedMaterial == Ref->RenderInfo->Material &&
                    B->FrameBufferBlendingOp == Ref->RenderInfo->FrameBufferBlendingOp &&
                    B->MaterialBlendingOp == Ref->RenderInfo->MaterialBlendingOp &&
                    B->BaseMaterial == Ref->BaseMaterial && B->bTwoSided == Ref->bTwoSided &&
                    B->VertexDataSize < 100000)
                    Batch = B;
            }
            if (!Batch) {
                Batch = new(GSceneMem) FProjectorRenderBatch(Ref->BaseMaterial, Ref->RenderInfo, Ref->bTwoSided);
                GProjectorList = new(GSceneMem) TList<FProjectorRenderBatch *>(Batch, GProjectorList);
            }
            Batch->AddPrimitive(new(GSceneMem) FStaticProjectorPrimitive(Ref));
        }
    }
}
