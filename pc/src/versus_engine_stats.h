#ifndef VERSUS_ENGINE_STATS_H
#define VERSUS_ENGINE_STATS_H

#include "unreal_types.h"
#include "unreal_object.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
inline void *operator new(unsigned int Size) { return GMalloc->Malloc(Size, L"new"); }
void operator delete(void *Block);

class FArray {
public:
    void *Data;
    INT ArrayNum, ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray() { if (Data) GMalloc->Free(Data); }
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Add(INT Count, INT ElementSize);
    INT AddZeroed(INT ElementSize, INT Count);
};

template<class T> class TArray : public FArray {
public:
    ~TArray() {
        for (INT i = 0; i < ArrayNum; ++i)
            (*this)(i).~T();
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty() {
        for (INT i = 0; i < ArrayNum; ++i)
            (*this)(i).~T();
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
    INT AddZeroed(INT Count) { return FArray::AddZeroed(sizeof(T), Count); }
    INT AddItem(const T &Item) {
        INT i = FArray::Add(1, sizeof(T));
        (*this)(i) = Item;
        return i;
    }
};

class FString : public TArray<TCHAR> {
public:
    FString(const TCHAR *In);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    static FString __cdecl Printf(const TCHAR *Format, ...);
};

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

enum EStatsType {
    STATSTYPE_Render = 0, STATSTYPE_Game = 1, STATSTYPE_Hardware = 2, STATSTYPE_Net = 6
};
enum EStatsDataType { STATSDATATYPE_Integer, STATSDATATYPE_Float, STATSDATATYPE_String };
enum EStatsUnit {
    STATSUNIT_Default, STATSUNIT_Combined_Default_MSec, STATSUNIT_Combined_Default_Default,
    STATSUNIT_Byte, STATSUNIT_KByte, STATSUNIT_MByte, STATSUNIT_MSec
};
struct FStatsData { INT Index; EStatsDataType DataType; EStatsUnit Unit; };

class FStats {
public:
    DWORD Unknown00;
    UBOOL Registered[8];
    template<class T> struct Values {
        TArray<T> Current, Previous;
        TArray<FString> Descriptions, FullDescriptions;
    };
    Values<DWORD> Integers;
    Values<FLOAT> Floats;
    Values<FString> Strings;
    TArray<FStatsData> Stats[8];
    struct FMovingAverage {
        INT WriteIndex, Window, Count;
        DWORD Unknown0c;
        TArray<DWORD> Samples;
    };
    TArray<FMovingAverage> History;
    void SmoothCounter(INT Index, INT Window);
    INT RegisterStats(EStatsType Type, EStatsDataType DataType, FString Description,
                      FString SectionDescription, EStatsUnit Unit);
};
extern FStats GStats;

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
