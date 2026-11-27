#include "versus_build.h"
#include "versus_stats_render_context.h"
#include "versus_name_table.h"

extern DOUBLE GSecondsPerCycle;
extern FLOAT GActorStatMinimum;

inline const TCHAR *UObject::GetName() const { return FName_Names(Name.Index)->Name; }

#define POSITION_STAT_LINE() \
    do \
    { \
        if ((FLOAT)(canvas->CurY + 32.f) >= viewport->SizeY) \
        { \
            column += 300; \
            canvas->CurY = 8.f; \
        } \
        canvas->CurX = (FLOAT)column; \
    } while (0)

#define STAT_TIMING(member) \
    POSITION_STAT_LINE(); \
    canvas->WrappedPrintf( \
        canvas->TinyFont, 0, \
        *FString::Printf(L"%02.1f %s ms", \
                         (DOUBLE)Integers.Previous(GEngineStats.member) * GSecondsPerCycle * 1000.0, \
                         *Integers.Descriptions(GEngineStats.member)))
#define STAT_COUNT(member) \
    POSITION_STAT_LINE(); \
    canvas->WrappedPrintf(canvas->TinyFont, 0, \
                          *FString::Printf(L"%u %s", Integers.Previous(GEngineStats.member), \
                                           *Integers.Descriptions(GEngineStats.member)))
#define STAT_HEADING(text, color) \
    canvas->DrawColor = color; \
    canvas->CurY += 4.f; \
    line = text; \
    POSITION_STAT_LINE(); \
    canvas->WrappedPrintf(canvas->TinyFont, 0, *line)

void FStats::Render(UViewport *viewport, UEngine *options)
{

    UCanvas *canvas = viewport->Canvas;
    FString line;
    FLOAT frameTime = (DOUBLE)Integers.Previous(GEngineStats.FrameTime) * GSecondsPerCycle;
    AverageFrameTime = AverageFrameTime ? AverageFrameTime * 0.98f + frameTime * 0.02f : frameTime;
    if (options->FPS)
    {
        INT width = 0, height = 0;
        FLOAT fps = AverageFrameTime ? 1.f / AverageFrameTime : 0.f;
        FLOAT currentFPS = 1.f / frameTime;
        if (fps < 20.f)
            canvas->DrawColor = FColor(128, 0, 0);
        else if (fps < 30.f)
            canvas->DrawColor = FColor(128, 0, 128);
        else if (fps < 40.f)
            canvas->DrawColor = FColor(128, 128, 0);
        else
            canvas->DrawColor = FColor(0, 128, 0);
        canvas->CurX = 0.f;
        canvas->CurY = 0.f;
        line = FString::Printf(L"avg : %03.1f FPS / %04.0f mVBLs / %04.1f ms", fps,
                               AverageFrameTime * 60000.f, AverageFrameTime * 1000.f);
        canvas->WrappedStrLenf(canvas->SmallFont, width, height, *line);
        FLOAT inset = (FLOAT)(width + 40);
        canvas->CurX = viewport->SizeX - inset;
        canvas->CurY = 50.f;
        canvas->WrappedPrintf(canvas->SmallFont, 1.f, 1.f, 0,
                              *FString::Printf(L"cur : %03.1f FPS / %04.0f mVBLs / %04.1f ms",
                                               currentFPS, frameTime * 60000.f, frameTime * 1000.f));
        canvas->CurX = viewport->SizeX - inset;
        canvas->CurY = (FLOAT)height + 50.f;
        canvas->WrappedPrintf(canvas->SmallFont, 1.f, 1.f, 0, *line);
    }
    INT column = 32;
    canvas->CurY = 8.f;
    if (options->RenderPage)
    {
        if (options->RenderPage == 1)
        {
            STAT_HEADING(L"- Frame ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(FrameTime);
            STAT_TIMING(FrameRender);
            STAT_TIMING(FrameStatsRender);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- BSP -----------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(BSPRender);
            STAT_COUNT(BSPSections);
            STAT_COUNT(BSPNodes);
            STAT_COUNT(BSPTriangles);
            STAT_TIMING(BSPDynamicLighting);
            STAT_COUNT(BSPDynamicLights);
            STAT_HEADING(L"- Projector -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(ProjectorRender);
            STAT_TIMING(ProjectorAttach);
            STAT_COUNT(ProjectorProjectors);
            STAT_COUNT(ProjectorTriangles);
            STAT_HEADING(L"- Particle -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(ParticleSpriteSetup);
            STAT_COUNT(ParticleParticles);
            STAT_COUNT(ParticleParticlesTicked);
            STAT_TIMING(ParticleRender);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- Visibility ----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(VisibilitySetup);
            STAT_TIMING(VisibilityTraverse);
            STAT_TIMING(VisibilityMeshLight);
            STAT_TIMING(VisibilityRelevantLights);
            STAT_COUNT(VisibilityEchelonlights);
            STAT_HEADING(L"- Mesh ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            SmoothCounter(GEngineStats.MeshSkin, 40);
            SmoothCounter(GEngineStats.MeshPose, 40);
            SmoothCounter(GEngineStats.MeshSkel, 40);
            SmoothCounter(GEngineStats.MeshDraw, 40);
            STAT_TIMING(MeshSkin);
            STAT_TIMING(MeshPose);
            STAT_TIMING(MeshSkel);
            STAT_TIMING(MeshDraw);
            STAT_HEADING(L"- StaticMesh ---", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(StaticMeshCount);
            STAT_COUNT(StaticMeshTriangles);
            STAT_TIMING(StaticMeshRender);
            STAT_TIMING(StaticMeshDrawSections);
            STAT_TIMING(StaticMeshSetMaterial);
        }
        else if (options->RenderPage == 2)
        {
            STAT_HEADING(L"- Frame ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(FrameTime);
            STAT_TIMING(FrameRender);
            STAT_TIMING(FrameStatsRender);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- Visibility ----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(VisibilitySetup);
            STAT_TIMING(VisibilityTraverse);
            STAT_TIMING(VisibilityMeshLight);
            STAT_TIMING(VisibilityRelevantLights);
            STAT_HEADING(L"- Mesh ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            SmoothCounter(GEngineStats.MeshSkin, 40);
            SmoothCounter(GEngineStats.MeshResult, 40);
            SmoothCounter(GEngineStats.MeshLOD, 40);
            SmoothCounter(GEngineStats.MeshPose, 40);
            SmoothCounter(GEngineStats.MeshSkel, 40);
            SmoothCounter(GEngineStats.MeshDraw, 40);
            STAT_TIMING(MeshSkin);
            STAT_TIMING(MeshResult);
            STAT_TIMING(MeshLOD);
            STAT_TIMING(MeshPose);
            STAT_TIMING(MeshSkel);
            STAT_TIMING(MeshDraw);
            STAT_HEADING(L"- Batch --------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(BatchBatches);
            STAT_COUNT(BatchPrimitives);
            STAT_TIMING(BatchRender);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- StaticMesh ---", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(StaticMeshCount);
            STAT_COUNT(StaticMeshTriangles);
            STAT_TIMING(StaticMeshRender);
            STAT_TIMING(StaticMeshDrawSections);
            STAT_TIMING(StaticMeshSetMaterial);
            STAT_HEADING(L" ==> Batched", FColor(50, 100, 50));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(StaticMeshCountAll);
            STAT_COUNT(StaticMeshSortedTriangles);
            STAT_COUNT(StaticMeshSortedSections);
            STAT_TIMING(StaticMeshSort);
            STAT_COUNT(StaticMeshUnsortedSections);
            STAT_COUNT(StaticMeshUnsortedTriangles);
            STAT_TIMING(StaticMeshRenderSecondary);
            STAT_HEADING(L" ==> UnBatched", FColor(50, 100, 50));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(StaticMeshSortedSectionsSecondary);
            STAT_COUNT(StaticMeshSortedTrianglesSecondary);
            STAT_TIMING(StaticMeshSortSecondary);
            STAT_COUNT(StaticMeshUnsortedSectionsSecondary);
            STAT_COUNT(StaticMeshUnsortedTrianglesSecondary);
            STAT_TIMING(StaticMeshRenderTertiary);
        }
        else if (options->RenderPage == 3)
        {
            STAT_HEADING(L"- Frame ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(FrameTime);
            STAT_TIMING(FrameRender);
            STAT_TIMING(FrameStatsRender);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- Visibility ----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(VisibilitySetup);
            STAT_COUNT(VisibilityMaskTests);
            STAT_COUNT(VisibilityMaskRejects);
            STAT_COUNT(VisibilityBoxTests);
            STAT_COUNT(VisibilityBoxRejects);
            STAT_TIMING(VisibilityTraverse);
            STAT_COUNT(VisibilityScratchBytes);
            STAT_TIMING(VisibilityMeshLight);
            STAT_TIMING(VisibilityRelevantLights);
            STAT_COUNT(VisibilityEchelonlights);
            STAT_HEADING(L" ", FColor(50, 100, 50));
            STAT_HEADING(L"- BSP Dynamic Lights ----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            for (TMap<UObject *, INT>::TIterator it(*GEngineStats.BspDynamicLightCounts); it; ++it)
            {
                FString text = FString::Printf(L"%s (x %ld)", it.GetKey()->GetName(), it.GetValue());
                STAT_HEADING(*text, FColor(50, 100, 50));
                canvas->DrawColor = FColor(255, 255, 255);
            }
            for (INT blank = 0; blank < 5 - GEngineStats.BspDynamicLightCounts->Num(); ++blank)
            {
                STAT_HEADING(L" ", FColor(50, 100, 50));
                canvas->DrawColor = FColor(255, 255, 255);
            }
            STAT_HEADING(L"- Particle -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(ParticleSpriteSetup);
            STAT_COUNT(ParticleParticles);
            STAT_COUNT(ParticleParticlesTicked);
            STAT_TIMING(ParticleRender);
            STAT_HEADING(L"- LightMap ------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(LightMapTime);
            STAT_COUNT(LightMapUpdates);
            STAT_HEADING(L"- Stencil -------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(StencilRender);
            STAT_COUNT(StencilNodes);
            STAT_COUNT(StencilTriangles);
        }
        else if (options->RenderPage == 4)
        {
            STAT_HEADING(L"- Frame ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(FrameTime);
            STAT_TIMING(FrameRender);
            STAT_TIMING(FrameStatsRender);
            STAT_HEADING(L"- BSP -----------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(BSPRender);
            STAT_COUNT(BSPSections);
            STAT_COUNT(BSPNodes);
            STAT_COUNT(BSPTriangles);
            STAT_TIMING(BSPDynamicLighting);
            STAT_COUNT(BSPDynamicLights);
            STAT_HEADING(L"- LightMap ------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(LightMapTime);
            STAT_COUNT(LightMapUpdates);
            STAT_HEADING(L"- Projector -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(ProjectorRender);
            STAT_TIMING(ProjectorAttach);
            STAT_COUNT(ProjectorProjectors);
            STAT_COUNT(ProjectorTriangles);
            STAT_HEADING(L"- Stencil -------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(StencilRender);
            STAT_COUNT(StencilNodes);
            STAT_COUNT(StencilTriangles);
            STAT_HEADING(L"- Visibility ----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(VisibilitySetup);
            STAT_COUNT(VisibilityMaskTests);
            STAT_COUNT(VisibilityMaskRejects);
            STAT_COUNT(VisibilityBoxTests);
            STAT_COUNT(VisibilityBoxRejects);
            STAT_TIMING(VisibilityTraverse);
            STAT_COUNT(VisibilityScratchBytes);
            STAT_TIMING(VisibilityMeshLight);
            STAT_TIMING(VisibilityRelevantLights);
            STAT_COUNT(VisibilityEchelonlights);
            STAT_HEADING(L"- Mesh ---------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            SmoothCounter(GEngineStats.MeshSkin, 40);
            SmoothCounter(GEngineStats.MeshResult, 40);
            SmoothCounter(GEngineStats.MeshLOD, 40);
            SmoothCounter(GEngineStats.MeshPose, 40);
            SmoothCounter(GEngineStats.MeshSkel, 40);
            SmoothCounter(GEngineStats.MeshRigid, 40);
            SmoothCounter(GEngineStats.MeshDraw, 40);
            STAT_TIMING(MeshSkin);
            STAT_TIMING(MeshResult);
            STAT_TIMING(MeshLOD);
            STAT_TIMING(MeshPose);
            STAT_TIMING(MeshSkel);
            STAT_TIMING(MeshRigid);
            STAT_TIMING(MeshDraw);
            STAT_HEADING(L"- Particle -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(ParticleSpriteSetup);
            STAT_COUNT(ParticleParticles);
            STAT_COUNT(ParticleParticlesTicked);
            STAT_TIMING(ParticleRender);
            STAT_HEADING(L"- StaticMesh ---", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(StaticMeshCount);
            STAT_COUNT(StaticMeshTriangles);
            STAT_TIMING(StaticMeshRender);
            STAT_TIMING(StaticMeshDrawSections);
            STAT_TIMING(StaticMeshSetMaterial);
            canvas->CurY += 4.f;
            STAT_HEADING(L"           Batched", FColor(50, 100, 50));
            canvas->DrawColor = FColor(255, 255, 255);
            canvas->CurY += 2.f;
            STAT_COUNT(StaticMeshCountAll);
            STAT_COUNT(StaticMeshSortedTriangles);
            STAT_COUNT(StaticMeshSortedSections);
            STAT_TIMING(StaticMeshSort);
            STAT_COUNT(StaticMeshUnsortedSections);
            STAT_COUNT(StaticMeshUnsortedTriangles);
            STAT_TIMING(StaticMeshRenderSecondary);
            canvas->CurY += 4.f;
            STAT_HEADING(L"         UnBatched", FColor(50, 100, 50));
            canvas->DrawColor = FColor(255, 255, 255);
            canvas->CurY += 2.f;
            STAT_COUNT(StaticMeshSortedSectionsSecondary);
            STAT_COUNT(StaticMeshSortedTrianglesSecondary);
            STAT_TIMING(StaticMeshSortSecondary);
            STAT_COUNT(StaticMeshUnsortedSectionsSecondary);
            STAT_COUNT(StaticMeshUnsortedTrianglesSecondary);
            STAT_TIMING(StaticMeshRenderTertiary);
            STAT_HEADING(L"- Batch --------", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(BatchBatches);
            STAT_COUNT(BatchPrimitives);
            STAT_TIMING(BatchRender);
        }
        if (options->RenderPage == 5)
        {
            STAT_HEADING(L"- Particle -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(ParticleParticles);
            STAT_COUNT(ParticleUsedKB);
            STAT_COUNT(ParticleAllocatedKB);
            STAT_COUNT(ParticlePeakKB);
            STAT_HEADING(L"- Projector -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(ProjectorProjectors);
            STAT_HEADING(L"- Scene Mem -----", FColor(0, 128, 128));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_COUNT(SceneUsedKB);
            STAT_COUNT(SceneAllocatedKB);
            STAT_COUNT(ScenePeakKB);
        }
    }
    if (options->Game == 2)
    {
        STAT_HEADING(L"- Actors ----", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(GameActor);
        canvas->DrawColor = FColor(0, 128, 128);
        canvas->CurY += 4.f;
        line = FString::Printf(L"- Detail : MinValue : %f ----", GActorStatMinimum);
        POSITION_STAT_LINE();
        canvas->WrappedPrintf(canvas->TinyFont, 0, *line);
        canvas->DrawColor = FColor(255, 255, 255);
        for (INT i = 0; i < viewport->Actor->XLevel->Actors.Num(); ++i)
        {
            AActor *actor = viewport->Actor->XLevel->Actors(i);
            FLOAT ms =
                (DOUBLE)Integers.Previous(GEngineStats.ActorIndices(i)) * GSecondsPerCycle * 1000.0;
            if (actor && ms > GActorStatMinimum)
            {
                FString name(actor->GetName());
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0, *FString::Printf(L"%f %s", ms, *name));
            }
        }
    }
    if (options->Game == 1)
    {
        STAT_HEADING(L"- Collision ----", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(CollisionStaticMesh);
        STAT_TIMING(CollisionStMPrimLineCheck);
        STAT_TIMING(CollisionStMCylinderLineFast);
        STAT_TIMING(CollisionStMCylinderLine);
        STAT_COUNT(StaticMeshCacheHits);
        STAT_COUNT(StaticMeshCacheMisses);
        STAT_COUNT(StaticMeshCacheFlushes);
        STAT_TIMING(CollisionBSP);
        STAT_TIMING(CollisionCorona);
        STAT_HEADING(L"- Game ---------", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(GameScript);
        STAT_TIMING(GameScriptTick);
        STAT_TIMING(GameActor);
        STAT_TIMING(GameSee);
        STAT_TIMING(GameSpawning);
        STAT_TIMING(GameAudio);
        STAT_TIMING(GameCleanupDestroyed);
        STAT_TIMING(GameUnused);
        STAT_TIMING(GameNet);
        STAT_TIMING(GameParticle);
        STAT_TIMING(GameCanvas);
        STAT_TIMING(GamePhysics);
        STAT_TIMING(GameMoveSecondary);
        STAT_COUNT(GameMove);
        STAT_TIMING(GameMLChecks);
        STAT_TIMING(GameMPChecks);
        STAT_TIMING(GameRenderData);
        STAT_TIMING(GameHUDPostRender);
        STAT_TIMING(GameHudER);
        STAT_TIMING(GameMagmaPageRefresh);
        STAT_TIMING(GameMagmaRendering);
        STAT_TIMING(GameInteractionPre);
        STAT_TIMING(GameInteractionPost);
        STAT_TIMING(GameScriptDebug);
        STAT_TIMING(GameIK);
    }
    if (options->Performance)
    {
        STAT_HEADING(L"- Frame ---------", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(FrameTime);
        STAT_TIMING(FrameRender);
        STAT_TIMING(FrameStatsRender);
        STAT_HEADING(L"- Game ---------", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(GameScript);
        STAT_TIMING(GameHUDPostRender);
        STAT_TIMING(GameHudER);
        STAT_TIMING(GameMagmaPageRefresh);
        STAT_TIMING(GameMagmaRendering);
        STAT_TIMING(GamePhysics);
        STAT_HEADING(L"- Collision ----", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(CollisionStaticMesh);
        STAT_TIMING(CollisionBSP);
        STAT_TIMING(CollisionCorona);
        STAT_HEADING(L"- Visibility ----", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(VisibilitySetup);
        STAT_HEADING(L"- StaticMesh ---", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_COUNT(StaticMeshTriangles);
        STAT_TIMING(StaticMeshRender);
        STAT_TIMING(StaticMeshRenderTertiary);
        STAT_HEADING(L"- BSP -----------", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(BSPRender);
    }
    if (options->Hardware)
    {
        STAT_HEADING(L"- Hardware -----", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        const TArray<FStatsData> &Descriptors = GStats.Stats[STATSTYPE_Hardware];
        for (INT entry = 0; entry < Descriptors.Num(); ++entry)
        {
            const FStatsData *data = &Descriptors(entry);
            switch (data->Unit)
            {
            case STATSUNIT_Default:
            case STATSUNIT_Byte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u %s", Integers.Previous(data->Index),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_KByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u KByte %s",
                                                       Integers.Previous(data->Index) / 1024,
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u MByte %s",
                                                       Integers.Previous(data->Index) / (1024 * 1024),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(
                    canvas->TinyFont, 0,
                    *FString::Printf(L"%2.1f %s ms",
                                     (DOUBLE)Integers.Previous(data->Index) * GSecondsPerCycle * 1000.0,
                                     *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_Combined_Default_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%2.1f %s ms [%u]",
                                                       (DOUBLE)Integers.Previous(data[1].Index) *
                                                           GSecondsPerCycle * 1000.0,
                                                       *Integers.Descriptions(data->Index),
                                                       Integers.Previous(data->Index)));
                ++entry;
                break;
            case STATSUNIT_Combined_Default_Default:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"In: %i, Out: %i %s",
                                                       Integers.Previous(data->Index),
                                                       Integers.Previous(data[1].Index),
                                                       *Integers.Descriptions(data->Index)));
                ++entry;
                break;
            }
        }
    }
    if (options->Audio)
    {
        STAT_HEADING(L"- Audio --------", FColor(0, 128, 128));
        canvas->DrawColor = FColor(255, 255, 255);
        const TArray<FStatsData> &Descriptors = GStats.Stats[STATSTYPE_Audio];
        for (INT entry = 0; entry < Descriptors.Num(); ++entry)
        {
            const FStatsData *data = &Descriptors(entry);
            switch (data->Unit)
            {
            case STATSUNIT_Default:
            case STATSUNIT_Byte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u %s", Integers.Previous(data->Index),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_KByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u KByte %s",
                                                       Integers.Previous(data->Index) / 1024,
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u MByte %s",
                                                       Integers.Previous(data->Index) / (1024 * 1024),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(
                    canvas->TinyFont, 0,
                    *FString::Printf(L"%2.1f %s ms",
                                     (DOUBLE)Integers.Previous(data->Index) * GSecondsPerCycle * 1000.0,
                                     *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_Combined_Default_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%2.1f %s ms [%u]",
                                                       (DOUBLE)Integers.Previous(data[1].Index) *
                                                           GSecondsPerCycle * 1000.0,
                                                       *Integers.Descriptions(data->Index),
                                                       Integers.Previous(data->Index)));
                ++entry;
                break;
            case STATSUNIT_Combined_Default_Default:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"In: %i, Out: %i %s",
                                                       Integers.Previous(data->Index),
                                                       Integers.Previous(data[1].Index),
                                                       *Integers.Descriptions(data->Index)));
                ++entry;
                break;
            }
        }
    }

    if (options->Net && viewport->Actor->XLevel->NetDriver)
    {
        UNetDriver *driver = viewport->Actor->XLevel->NetDriver;
        UNetConnection *connection;
        if ((connection = driver->ServerConnection) != 0)
        {
            INT channels = connection->OpenChannels.Num();
            Integers.Current(GEngineStats.NetPing) = (INT)(connection->Lag * 1000.f);
            Integers.Current(GEngineStats.NetChannels) = channels;
            Integers.Current(GEngineStats.NetUnorderd) = (INT)connection->InUnordered;
            Integers.Current(GEngineStats.NetUnordered) = (INT)connection->OutUnordered;
            Integers.Current(GEngineStats.NetPacketLoss) = (INT)connection->InLoss;
            Integers.Current(GEngineStats.NetPacketLossSecondary) = (INT)connection->OutLoss;
            Integers.Current(GEngineStats.NetPackets) = (INT)connection->InPackets;
            Integers.Current(GEngineStats.NetPacketsSecondary) = (INT)connection->OutPackets;
            Integers.Current(GEngineStats.NetBunches) = (INT)connection->InBunches;
            Integers.Current(GEngineStats.NetBunchesSecondary) = (INT)connection->OutBunches;
            Integers.Current(GEngineStats.NetBytes) = (INT)connection->InBytes;
            Integers.Current(GEngineStats.NetBytesSecondary) = (INT)connection->OutBytes;
            Integers.Current(GEngineStats.NetSpeed) = connection->CurrentNetSpeed;
            Integers.Current(GEngineStats.NetVoiceBytes) = (INT)connection->InVoiceBytes;
            Integers.Current(GEngineStats.NetVoiceBytesSecondary) = (INT)connection->OutVoiceBytes;
        }
        else
        {
            INT count = driver->ClientConnections.Num();
            if (count > 0)
            {
                INT totalChannelCount = 0;
                INT totalInUnordered = 0;
                INT totalOutUnordered = 0;
                INT totalInLoss = 0;
                INT totalOutLoss = 0;
                INT totalInPackets = 0;
                INT totalOutPackets = 0;
                INT totalInBunches = 0;
                INT totalOutBunches = 0;
                INT totalCurrentNetSpeed = 0;
                INT totalInBytes = 0;
                INT totalOutBytes = 0;
                INT totalInVoiceBytes = 0;
                INT totalOutVoiceBytes = 0;
                for (INT i = 0; i < driver->ClientConnections.Num(); ++i)
                {
                    connection = driver->ClientConnections(i);
                    totalChannelCount += connection->OpenChannels.Num();
                    totalInUnordered += connection->InUnordered;
                    totalOutUnordered += connection->OutUnordered;
                    totalInLoss += connection->InLoss;
                    totalOutLoss += connection->OutLoss;
                    totalInPackets += connection->InPackets;
                    totalOutPackets += connection->OutPackets;
                    totalInBunches += connection->InBunches;
                    totalOutBunches += connection->OutBunches;
                    totalInBytes += connection->InBytes;
                    totalOutBytes += connection->OutBytes;
                    totalInVoiceBytes += connection->InVoiceBytes;
                    totalOutVoiceBytes += connection->OutVoiceBytes;
                    totalCurrentNetSpeed += connection->CurrentNetSpeed;
                }
                totalCurrentNetSpeed /= count;
                Integers.Current(GEngineStats.NetPing) = (INT)(connection->Lag * 1000.f);
                Integers.Current(GEngineStats.NetChannels) = totalChannelCount;
                Integers.Current(GEngineStats.NetUnorderd) = totalInUnordered;
                Integers.Current(GEngineStats.NetUnordered) = totalOutUnordered;
                Integers.Current(GEngineStats.NetPacketLoss) = totalInLoss;
                Integers.Current(GEngineStats.NetPacketLossSecondary) = totalOutLoss;
                Integers.Current(GEngineStats.NetPackets) = totalInPackets;
                Integers.Current(GEngineStats.NetPacketsSecondary) = totalOutPackets;
                Integers.Current(GEngineStats.NetBunches) = totalInBunches;
                Integers.Current(GEngineStats.NetBunchesSecondary) = totalOutBunches;
                Integers.Current(GEngineStats.NetBytes) = totalInBytes;
                Integers.Current(GEngineStats.NetBytesSecondary) = totalOutBytes;
                Integers.Current(GEngineStats.NetVoiceBytes) = totalInVoiceBytes;
                Integers.Current(GEngineStats.NetVoiceBytesSecondary) = totalOutVoiceBytes;
                Integers.Current(GEngineStats.NetSpeed) = totalCurrentNetSpeed;
            }
        }
        STAT_HEADING(L" ", FColor(50, 100, 50));
        STAT_HEADING(L"- Net ----------", FColor(0, 128, 128));
        STAT_HEADING(L" ", FColor(50, 100, 50));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(GameNet);
        STAT_HEADING(L" ", FColor(50, 100, 50));
        canvas->DrawColor = FColor(255, 255, 255);
        STAT_TIMING(GameNetDispatch);
        STAT_TIMING(GameNetPart1Super);
        STAT_TIMING(GameNetPart2recvfrom);
        STAT_TIMING(GameNetPart3decryptaudio);
        STAT_TIMING(GameNetPart4ReceivedRawPacket);
        if (viewport->Actor->XLevel->NetDriver->ClientConnections.Num() > 0)
        {
            STAT_HEADING(L" ", FColor(50, 100, 50));
            canvas->DrawColor = FColor(255, 255, 255);
            STAT_TIMING(GameNetServerSend);
            STAT_TIMING(GameNetPart1InitClientConnection);
            STAT_TIMING(GameNetPart2PriorityLists);
            STAT_TIMING(GameNetPart3InitChannels);
            STAT_TIMING(GameNetPart4ConsiderActors);
            STAT_TIMING(GameNetPart5NetRelevancy);
            STAT_TIMING(GameNetPart6VisibleChannels);
            STAT_TIMING(GameNetPart7ClosedChannels);
            STAT_TIMING(GameNetPart8FastLineCheck);
            STAT_TIMING(GameNetPart9CheckDistance);
            STAT_TIMING(GameNetPart10ReplicateActor);
        }
        else
        {
            STAT_TIMING(GameNetClientSend);
        }
        const TArray<FStatsData> &Descriptors = GStats.Stats[STATSTYPE_Net];
        for (INT entry = 0; entry < Descriptors.Num(); ++entry)
        {
            const FStatsData *data = &Descriptors(entry);
            switch (data->Unit)
            {
            case STATSUNIT_Default:
            case STATSUNIT_Byte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u %s", Integers.Previous(data->Index),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_KByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u KByte %s",
                                                       Integers.Previous(data->Index) / 1024,
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MByte:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%u MByte %s",
                                                       Integers.Previous(data->Index) / (1024 * 1024),
                                                       *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(
                    canvas->TinyFont, 0,
                    *FString::Printf(L"%2.1f %s ms",
                                     (DOUBLE)Integers.Previous(data->Index) * GSecondsPerCycle * 1000.0,
                                     *Integers.Descriptions(data->Index)));
                break;
            case STATSUNIT_Combined_Default_MSec:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"%2.1f %s ms [%u]",
                                                       (DOUBLE)Integers.Previous(data[1].Index) *
                                                           GSecondsPerCycle * 1000.0,
                                                       *Integers.Descriptions(data->Index),
                                                       Integers.Previous(data->Index)));
                ++entry;
                break;
            case STATSUNIT_Combined_Default_Default:
                POSITION_STAT_LINE();
                canvas->WrappedPrintf(canvas->TinyFont, 0,
                                      *FString::Printf(L"In: %i, Out: %i %s",
                                                       Integers.Previous(data->Index),
                                                       Integers.Previous(data[1].Index),
                                                       *Integers.Descriptions(data->Index)));
                ++entry;
                break;
            }
        }
    }
}
