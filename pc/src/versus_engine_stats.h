#ifndef VERSUS_ENGINE_STATS_H
#define VERSUS_ENGINE_STATS_H

#include "unreal_types.h"
#include "versus_stats_arrays.h"
#if !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_object.h"
#endif

template<class Key, class Value> class TMap {
    struct TPair {
        INT HashNext;
        Key Object;
        Value Data;
    };
    TArray<TPair> Pairs;
    INT *Hash, HashCount;
    void Rehash();
public:
    INT Num() const { return Pairs.Num(); }

    class TIterator {
        TMap &Owner;
        TArray<TPair> &Pairs;
        INT Index;

    public:
        TIterator(TMap &Map) : Owner(Map), Pairs(Map.Pairs), Index(0) {}
        void operator++() { ++Index; }
        operator UBOOL() const { return Index < Pairs.Num(); }
        Key &GetKey() const { return Pairs(Index).Object; }
        Value &GetValue() const { return Pairs(Index).Data; }
    };

    TMap() : Hash(0), HashCount(8) { Rehash(); }
};


template<class Key, class Value> void TMap<Key, Value>::Rehash()
{
    INT *newHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    for (INT i = 0; i < HashCount; ++i)
        newHash[i] = -1;
    for (i = 0; i < Pairs.Num(); ++i) {
        TPair &pair = Pairs(i);
        INT index = (pair.Object ? pair.Object->Index : 0) & (HashCount - 1);
        pair.HashNext = newHash[index];
        newHash[index] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = newHash;
}

#include "versus_stats_data.h"

class FEngineStats {
public:
    TArray<INT> ActorIndices;
    // FBspLightDrawList::Render keys the map by Light->Actor.
    TMap<UObject *, INT> *BspDynamicLightCounts;
    INT FirstStat;  // The editor constructor fills the following stat indices with -1.
    INT FrameTime;
    INT FrameRender;
    INT BSPRender;
    INT BSPSections;
    INT BSPNodes;
    INT BSPTriangles;
    INT BSPDynamicLighting;
    INT BSPDynamicLights;
    INT CollisionBSP;
    INT LightMapUpdates;
    INT LightMapTime;
    INT ProjectorRender;
    INT ProjectorAttach;
    INT ProjectorProjectors;
    INT ProjectorTriangles;
    INT ProjectorAllocatedKB;
    INT StencilRender;
    INT StencilNodes;
    INT StencilTriangles;
    INT VisibilitySetup;
    INT VisibilityMaskTests;
    INT VisibilityMaskRejects;
    INT VisibilityBoxTests;
    INT VisibilityBoxRejects;
    INT VisibilityTraverse;
    INT VisibilityScratchBytes;
    INT VisibilityMeshLight;
    INT VisibilityRelevantLights;
    INT VisibilityEchelonlights;
    INT Unknown88;
    INT Unknown8c;
    INT Unknown90;
    INT MatineeTick;
    INT MeshSkin;
    INT MeshResult;
    INT MeshLOD;
    INT MeshSkel;
    INT MeshPose;
    INT MeshRigid;
    INT MeshDraw;
    INT ParticleSpriteSetup;
    INT ParticleParticles;
    INT ParticleParticlesTicked;
    INT ParticleRender;
    INT ParticleUsedKB;
    INT ParticleAllocatedKB;
    INT ParticlePeakKB;
    INT SceneUsedKB;
    INT SceneAllocatedKB;
    INT ScenePeakKB;
    INT Unknowndc;
    INT Unknowne0;
    INT Unknowne4;
    INT StaticMeshCountAll;
    INT StaticMeshSortedSections;
    INT StaticMeshSortedTriangles;
    INT StaticMeshSort;
    INT StaticMeshUnsortedSections;
    INT StaticMeshUnsortedTriangles;
    INT StaticMeshRenderSecondary;
    INT StaticMeshSortedSectionsSecondary;
    INT StaticMeshSortedTrianglesSecondary;
    INT StaticMeshSortSecondary;
    INT StaticMeshUnsortedSectionsSecondary;
    INT StaticMeshUnsortedTrianglesSecondary;
    INT StaticMeshRenderTertiary;
    INT StaticMeshCount;
    INT StaticMeshTriangles;
    INT StaticMeshRender;
    INT StaticMeshDrawSections;
    INT StaticMeshSetMaterial;
    INT CollisionStaticMesh;
    INT StaticMeshCacheHits;
    INT StaticMeshCacheMisses;
    INT StaticMeshCacheFlushes;
    INT CollisionStMPrimLineCheck;
    INT CollisionStMCylinderLineFast;
    INT CollisionStMCylinderLine;
    INT BatchBatches;
    INT BatchPrimitives;
    INT BatchRender;
    INT FrameStatsRender;
    INT GameScript;
    INT GameScriptTick;
    INT GameActor;
    INT Unknown168;
    INT GameSee;
    INT GameSpawning;
    INT GameAudio;
    INT GameCleanupDestroyed;
    INT GameUnused;
    INT GameNet;
    INT GameNetServerSend;
    INT GameNetPart1InitClientConnection;
    INT GameNetPart2PriorityLists;
    INT GameNetPart3InitChannels;
    INT GameNetPart4ConsiderActors;
    INT GameNetPart5NetRelevancy;
    INT GameNetPart6VisibleChannels;
    INT GameNetPart7ClosedChannels;
    INT GameNetPart8FastLineCheck;
    INT GameNetPart9CheckDistance;
    INT GameNetPart10ReplicateActor;
    INT GameNetClientSend;
    INT GameNetDispatch;
    INT GameNetPart1Super;
    INT GameNetPart2recvfrom;
    INT GameNetPart3decryptaudio;
    INT GameNetPart4ReceivedRawPacket;
    INT GameParticle;
    INT GameCanvas;
    INT GamePhysics;
    INT GameMoveSecondary;
    INT GameMove;
    INT GameMLChecks;
    INT GameMPChecks;
    INT GameRenderData;
    INT GameHUDPostRender;
    INT GameHudER;
    INT GameMagmaPageRefresh;
    INT GameMagmaRendering;
    INT GameInteractionPre;
    INT GameInteractionPost;
    INT GameScriptDebug;
    INT GameIK;
    INT CollisionCorona;
    INT NetNetReplic;
    INT NetNetRepInit;
    INT NetNetRepSearchNative;
    INT NetNetRepSearchScript;
    INT NetNetRepSearchDirty;
    INT NetNetRepBunch;
    INT NetNetRepFunc;
    INT NetPing;
    INT NetChannels;
    INT NetUnorderd;
    INT NetUnordered;
    INT NetPacketLoss;
    INT NetPacketLossSecondary;
    INT NetPackets;
    INT NetPacketsSecondary;
    INT NetBunches;
    INT NetBunchesSecondary;
    INT NetBytes;
    INT NetBytesSecondary;
    INT NetVoiceBytes;
    INT NetVoiceBytesSecondary;
    INT NetSpeed;
    INT GameReps;
    INT GameNativeRepsTested;
    INT GameScriptRepsTested;
    INT GameRPC;
    INT GamePV;
    INT PS2GPUDMASynchro;
    INT PS2UploadTexture;
    INT PS2AddUniqueData;
    INT PS2DrawPrimOrthoTime;
    INT PS2DrawPrimOrthoCount;
    INT PS2WastedDataBYTES;
    INT PS2MaxBlockSizeBYTES;
    void Init();
};
extern FEngineStats GEngineStats;

#endif
