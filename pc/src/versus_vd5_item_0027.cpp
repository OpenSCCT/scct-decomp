// FD3DStats::Init (Versus RVA 0x5e790): registers the D3D render device's
// "Hardware" statistics with GStats, or, when they were registered before,
// copies the existing indices back into this object (UE2 FD3DStats pattern).
// FStats layout beyond the members used here is padding; field names follow
// the description strings and the unit (Combined_Default_MSec = count,
// MSec = cycles).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In);
    ~FString();
};

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

enum EStatsType { STATSTYPE_Global, STATSTYPE_Hardware, STATSTYPE_Render, STATSTYPE_MAX };
enum EStatsDataType { STATSDATATYPE_Integer, STATSDATATYPE_Float };
enum EStatsUnit
{
    STATSUNIT_Default,
    STATSUNIT_Combined_Default_MSec,
    STATSUNIT_Combined_Default_Default,
    STATSUNIT_Byte,
    STATSUNIT_KByte,
    STATSUNIT_MByte,
    STATSUNIT_MSec
};

struct FStatsData
{
    INT Index;
    INT Unknown[2];
};

class FStats
{
public:
    INT Unknown0;
    UBOOL Registered[STATSTYPE_MAX];
    BYTE Unknown10[0xb4 - 0x10];
    TArray<FStatsData> Stats[STATSTYPE_MAX];
    INT RegisterStats(EStatsType Type, EStatsDataType DataType, FString Description, FString SectionDescription, EStatsUnit StatsUnit);
};
extern FStats GStats;

// Retail keeps these literals in writable .data, so they are declared here.

extern const TCHAR D3DStatsSection_NumPrimitives[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_NumPrimitives[]; // L"NumPrimitives"
extern const TCHAR D3DStatsSection_NumSVPVertices[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_NumSVPVertices[]; // L"NumSVPVertices"
extern const TCHAR D3DStatsSection_NumTextures[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_NumTextures[]; // L"NumTextures"
extern const TCHAR D3DStatsSection_Textures[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Textures[]; // L"Textures"
extern const TCHAR D3DStatsSection_TotalResources[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_TotalResources[]; // L"Total Resources"
extern const TCHAR D3DStatsSection_PushState_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_PushState_Count[]; // L"PushState"
extern const TCHAR D3DStatsSection_PushState_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_PushState_Cycles[]; // L"PushState"
extern const TCHAR D3DStatsSection_PopState_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_PopState_Count[]; // L"PopState"
extern const TCHAR D3DStatsSection_PopState_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_PopState_Cycles[]; // L"PopState"
extern const TCHAR D3DStatsSection_SetRenderTarget_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetRenderTarget_Count[]; // L"SetRenderTarget"
extern const TCHAR D3DStatsSection_SetRenderTarget_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetRenderTarget_Cycles[]; // L"SetRenderTarget"
extern const TCHAR D3DStatsSection_SetMaterial_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetMaterial_Count[]; // L"SetMaterial"
extern const TCHAR D3DStatsSection_SetMaterial_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetMaterial_Cycles[]; // L"SetMaterial"
extern const TCHAR D3DStatsSection_SetMaterialBlending_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetMaterialBlending_Count[]; // L"SetMaterialBlending"
extern const TCHAR D3DStatsSection_SetMaterialBlending_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetMaterialBlending_Cycles[]; // L"SetMaterialBlending"
extern const TCHAR D3DStatsSection_SetVertexStream_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetVertexStream_Count[]; // L"SetVertexStream"
extern const TCHAR D3DStatsSection_SetVertexStream_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetVertexStream_Cycles[]; // L"SetVertexStream"
extern const TCHAR D3DStatsSection_SetDynStream_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetDynStream_Count[]; // L"SetDynStream"
extern const TCHAR D3DStatsSection_SetDynStream_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetDynStream_Cycles[]; // L"SetDynStream"
extern const TCHAR D3DStatsSection_SetIB_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetIB_Count[]; // L"SetIB"
extern const TCHAR D3DStatsSection_SetIB_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetIB_Cycles[]; // L"SetIB"
extern const TCHAR D3DStatsSection_SetDynIB_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetDynIB_Count[]; // L"SetDynIB"
extern const TCHAR D3DStatsSection_SetDynIB_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_SetDynIB_Cycles[]; // L"SetDynIB"
extern const TCHAR D3DStatsSection_DrawPrimitive_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DrawPrimitive_Count[]; // L"DrawPrimitive"
extern const TCHAR D3DStatsSection_DrawPrimitive_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DrawPrimitive_Cycles[]; // L"DrawPrimitive"
extern const TCHAR D3DStatsSection_Lock_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Lock_Count[]; // L"Lock"
extern const TCHAR D3DStatsSection_Lock_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Lock_Cycles[]; // L"Lock"
extern const TCHAR D3DStatsSection_Unlock_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Unlock_Count[]; // L"Unlock"
extern const TCHAR D3DStatsSection_Unlock_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Unlock_Cycles[]; // L"Unlock"
extern const TCHAR D3DStatsSection_Present_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Present_Count[]; // L"Present"
extern const TCHAR D3DStatsSection_Present_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Present_Cycles[]; // L"Present"
extern const TCHAR D3DStatsSection_StateChanges_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_StateChanges_Count[]; // L"StateChanges"
extern const TCHAR D3DStatsSection_StateChanges_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_StateChanges_Cycles[]; // L"StateChanges"
extern const TCHAR D3DStatsSection_TextureChanges_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_TextureChanges_Count[]; // L"TextureChanges"
extern const TCHAR D3DStatsSection_TextureChanges_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_TextureChanges_Cycles[]; // L"TextureChanges"
extern const TCHAR D3DStatsSection_TransformChanges_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_TransformChanges_Count[]; // L"TransformChanges"
extern const TCHAR D3DStatsSection_TransformChanges_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_TransformChanges_Cycles[]; // L"TransformChanges"
extern const TCHAR D3DStatsSection_LightChanges_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_LightChanges_Count[]; // L"LightChanges"
extern const TCHAR D3DStatsSection_LightChanges_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_LightChanges_Cycles[]; // L"LightChanges"
extern const TCHAR D3DStatsSection_LightSet_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_LightSet_Count[]; // L"LightSet"
extern const TCHAR D3DStatsSection_LightSet_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_LightSet_Cycles[]; // L"LightSet"
extern const TCHAR D3DStatsSection_Clear_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Clear_Count[]; // L"Clear"
extern const TCHAR D3DStatsSection_Clear_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_Clear_Cycles[]; // L"Clear"
extern const TCHAR D3DStatsSection_DynVBLock_Count[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DynVBLock_Count[]; // L"DynVBLock"
extern const TCHAR D3DStatsSection_DynVBLock_Cycles[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DynVBLock_Cycles[]; // L"DynVBLock"
extern const TCHAR D3DStatsSection_DynVBDiscards[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DynVBDiscards[]; // L"DynVBDiscards"
extern const TCHAR D3DStatsSection_DynVBBytes[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DynVBBytes[]; // L"DynVBBytes"
extern const TCHAR D3DStatsSection_DynIBBytes[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_DynIBBytes[]; // L"DynIBBytes"
extern const TCHAR D3DStatsSection_NumVertexStreams[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_NumVertexStreams[]; // L"NumVertexStreams"
extern const TCHAR D3DStatsSection_NumIndexBuffers[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_NumIndexBuffers[]; // L"NumIndexBuffers"
extern const TCHAR D3DStatsSection_VertexStreamBytes[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_VertexStreamBytes[]; // L"VertexStreamBytes"
extern const TCHAR D3DStatsSection_IndexBufferBytes[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_IndexBufferBytes[]; // L"IndexBufferBytes"
extern const TCHAR D3DStatsSection_StreamSourceChanges[]; // L"Hardware"
extern const TCHAR D3DStatsDesc_StreamSourceChanges[]; // L"StreamSourceChanges"

class FD3DStats
{
public:
    INT STATS_FirstEntry;
    INT PushState_Count; // 0x4
    INT PushState_Cycles; // 0x8
    INT PopState_Count; // 0xc
    INT PopState_Cycles; // 0x10
    INT SetRenderTarget_Count; // 0x14
    INT SetRenderTarget_Cycles; // 0x18
    INT SetMaterial_Count; // 0x1c
    INT SetMaterial_Cycles; // 0x20
    INT SetMaterialBlending_Count; // 0x24
    INT SetMaterialBlending_Cycles; // 0x28
    INT SetVertexStream_Count; // 0x2c
    INT SetVertexStream_Cycles; // 0x30
    INT SetDynStream_Count; // 0x34
    INT SetDynStream_Cycles; // 0x38
    INT SetIB_Count; // 0x3c
    INT SetIB_Cycles; // 0x40
    INT SetDynIB_Count; // 0x44
    INT SetDynIB_Cycles; // 0x48
    INT DrawPrimitive_Count; // 0x4c
    INT DrawPrimitive_Cycles; // 0x50
    INT NumPrimitives; // 0x54
    INT NumSVPVertices; // 0x58
    INT Lock_Count; // 0x5c
    INT Lock_Cycles; // 0x60
    INT Unlock_Count; // 0x64
    INT Unlock_Cycles; // 0x68
    INT Present_Count; // 0x6c
    INT Present_Cycles; // 0x70
    INT DynVBBytes; // 0x74
    INT DynIBBytes; // 0x78
    INT NumTextures; // 0x7c
    INT Textures; // 0x80
    INT NumVertexStreams; // 0x84
    INT VertexStreamBytes; // 0x88
    INT NumIndexBuffers; // 0x8c
    INT IndexBufferBytes; // 0x90
    INT StateChanges_Count; // 0x94
    INT StateChanges_Cycles; // 0x98
    INT TextureChanges_Count; // 0x9c
    INT TextureChanges_Cycles; // 0xa0
    INT TransformChanges_Count; // 0xa4
    INT TransformChanges_Cycles; // 0xa8
    INT LightChanges_Count; // 0xac
    INT LightChanges_Cycles; // 0xb0
    INT LightSet_Count; // 0xb4
    INT LightSet_Cycles; // 0xb8
    INT DynVBLock_Cycles; // 0xbc
    INT DynVBLock_Count; // 0xc0
    INT DynVBDiscards; // 0xc4
    INT Clear_Count; // 0xc8
    INT Clear_Cycles; // 0xcc
    INT StreamSourceChanges; // 0xd0
    INT TotalResources; // 0xd4

    void Init();
};

void FD3DStats::Init()
{
    // Already registered: retrieve the indices from GStats.
    if (GStats.Registered[STATSTYPE_Render])
    {
        INT *Dummy = &STATS_FirstEntry + 1;
        for (INT i = 0; i < GStats.Stats[STATSTYPE_Render].Num(); i++)
            *Dummy++ = GStats.Stats[STATSTYPE_Render](i).Index;
        return;
    }

    NumPrimitives = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_NumPrimitives, D3DStatsSection_NumPrimitives, STATSUNIT_Default);
    NumSVPVertices = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_NumSVPVertices, D3DStatsSection_NumSVPVertices, STATSUNIT_Default);
    NumTextures = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_NumTextures, D3DStatsSection_NumTextures, STATSUNIT_Default);
    Textures = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Textures, D3DStatsSection_Textures, STATSUNIT_KByte);
    TotalResources = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_TotalResources, D3DStatsSection_TotalResources, STATSUNIT_KByte);
    PushState_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_PushState_Count, D3DStatsSection_PushState_Count, STATSUNIT_Combined_Default_MSec);
    PushState_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_PushState_Cycles, D3DStatsSection_PushState_Cycles, STATSUNIT_MSec);
    PopState_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_PopState_Count, D3DStatsSection_PopState_Count, STATSUNIT_Combined_Default_MSec);
    PopState_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_PopState_Cycles, D3DStatsSection_PopState_Cycles, STATSUNIT_MSec);
    SetRenderTarget_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetRenderTarget_Count, D3DStatsSection_SetRenderTarget_Count, STATSUNIT_Combined_Default_MSec);
    SetRenderTarget_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetRenderTarget_Cycles, D3DStatsSection_SetRenderTarget_Cycles, STATSUNIT_MSec);
    SetMaterial_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetMaterial_Count, D3DStatsSection_SetMaterial_Count, STATSUNIT_Combined_Default_MSec);
    SetMaterial_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetMaterial_Cycles, D3DStatsSection_SetMaterial_Cycles, STATSUNIT_MSec);
    SetMaterialBlending_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetMaterialBlending_Count, D3DStatsSection_SetMaterialBlending_Count, STATSUNIT_Combined_Default_MSec);
    SetMaterialBlending_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetMaterialBlending_Cycles, D3DStatsSection_SetMaterialBlending_Cycles, STATSUNIT_MSec);
    SetVertexStream_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetVertexStream_Count, D3DStatsSection_SetVertexStream_Count, STATSUNIT_Combined_Default_MSec);
    SetVertexStream_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetVertexStream_Cycles, D3DStatsSection_SetVertexStream_Cycles, STATSUNIT_MSec);
    SetDynStream_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetDynStream_Count, D3DStatsSection_SetDynStream_Count, STATSUNIT_Combined_Default_MSec);
    SetDynStream_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetDynStream_Cycles, D3DStatsSection_SetDynStream_Cycles, STATSUNIT_MSec);
    SetIB_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetIB_Count, D3DStatsSection_SetIB_Count, STATSUNIT_Combined_Default_MSec);
    SetIB_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetIB_Cycles, D3DStatsSection_SetIB_Cycles, STATSUNIT_MSec);
    SetDynIB_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetDynIB_Count, D3DStatsSection_SetDynIB_Count, STATSUNIT_Combined_Default_MSec);
    SetDynIB_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_SetDynIB_Cycles, D3DStatsSection_SetDynIB_Cycles, STATSUNIT_MSec);
    DrawPrimitive_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DrawPrimitive_Count, D3DStatsSection_DrawPrimitive_Count, STATSUNIT_Combined_Default_MSec);
    DrawPrimitive_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DrawPrimitive_Cycles, D3DStatsSection_DrawPrimitive_Cycles, STATSUNIT_MSec);
    Lock_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Lock_Count, D3DStatsSection_Lock_Count, STATSUNIT_Combined_Default_MSec);
    Lock_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Lock_Cycles, D3DStatsSection_Lock_Cycles, STATSUNIT_MSec);
    Unlock_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Unlock_Count, D3DStatsSection_Unlock_Count, STATSUNIT_Combined_Default_MSec);
    Unlock_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Unlock_Cycles, D3DStatsSection_Unlock_Cycles, STATSUNIT_MSec);
    Present_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Present_Count, D3DStatsSection_Present_Count, STATSUNIT_Combined_Default_MSec);
    Present_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Present_Cycles, D3DStatsSection_Present_Cycles, STATSUNIT_MSec);
    StateChanges_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_StateChanges_Count, D3DStatsSection_StateChanges_Count, STATSUNIT_Combined_Default_MSec);
    StateChanges_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_StateChanges_Cycles, D3DStatsSection_StateChanges_Cycles, STATSUNIT_MSec);
    TextureChanges_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_TextureChanges_Count, D3DStatsSection_TextureChanges_Count, STATSUNIT_Combined_Default_MSec);
    TextureChanges_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_TextureChanges_Cycles, D3DStatsSection_TextureChanges_Cycles, STATSUNIT_MSec);
    TransformChanges_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_TransformChanges_Count, D3DStatsSection_TransformChanges_Count, STATSUNIT_Combined_Default_MSec);
    TransformChanges_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_TransformChanges_Cycles, D3DStatsSection_TransformChanges_Cycles, STATSUNIT_MSec);
    LightChanges_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_LightChanges_Count, D3DStatsSection_LightChanges_Count, STATSUNIT_Combined_Default_MSec);
    LightChanges_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_LightChanges_Cycles, D3DStatsSection_LightChanges_Cycles, STATSUNIT_MSec);
    LightSet_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_LightSet_Count, D3DStatsSection_LightSet_Count, STATSUNIT_Combined_Default_MSec);
    LightSet_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_LightSet_Cycles, D3DStatsSection_LightSet_Cycles, STATSUNIT_MSec);
    Clear_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Clear_Count, D3DStatsSection_Clear_Count, STATSUNIT_Combined_Default_MSec);
    Clear_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_Clear_Cycles, D3DStatsSection_Clear_Cycles, STATSUNIT_MSec);
    DynVBLock_Count = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DynVBLock_Count, D3DStatsSection_DynVBLock_Count, STATSUNIT_Combined_Default_MSec);
    DynVBLock_Cycles = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DynVBLock_Cycles, D3DStatsSection_DynVBLock_Cycles, STATSUNIT_MSec);
    DynVBDiscards = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DynVBDiscards, D3DStatsSection_DynVBDiscards, STATSUNIT_Default);
    DynVBBytes = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DynVBBytes, D3DStatsSection_DynVBBytes, STATSUNIT_KByte);
    DynIBBytes = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_DynIBBytes, D3DStatsSection_DynIBBytes, STATSUNIT_KByte);
    NumVertexStreams = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_NumVertexStreams, D3DStatsSection_NumVertexStreams, STATSUNIT_Default);
    NumIndexBuffers = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_NumIndexBuffers, D3DStatsSection_NumIndexBuffers, STATSUNIT_Default);
    VertexStreamBytes = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_VertexStreamBytes, D3DStatsSection_VertexStreamBytes, STATSUNIT_KByte);
    IndexBufferBytes = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_IndexBufferBytes, D3DStatsSection_IndexBufferBytes, STATSUNIT_KByte);
    StreamSourceChanges = GStats.RegisterStats(STATSTYPE_Render, STATSDATATYPE_Integer, D3DStatsDesc_StreamSourceChanges, D3DStatsSection_StreamSourceChanges, STATSUNIT_Default);

    GStats.Registered[STATSTYPE_Render] = 1;
}
