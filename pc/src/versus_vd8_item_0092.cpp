// Work item 0092: Versus RVA 0x14ca50-0x14ce92 (VC7.0 /GL, linked /LTCG).
// 0x14ca50: UpdateStaticMeshLighting (near miss: retail inlines UE2's multi-instruction
//           __asm appMemzero from UnVcWin32.h; pure C++ memset matches the rest of the
//           function structurally).
// 0x14cdd0: RenderSortedStaticMeshSection (MATCH, LTCG, RI in EBX).

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

extern "C" void *__cdecl memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern "C" __declspec(dllimport) double __cdecl floor(double);

inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }
inline INT appFloor(FLOAT F) { return (INT)floor(F); }
inline INT Clamp(INT X, INT Min, INT Max) { return X < Min ? Min : X < Max ? X : Max; }

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    __declspec(noinline) FVector SafeNormal() const;
};

__declspec(dllimport) extern const FVector GZeroVector;

class FPlane : public FVector
{
public:
    FLOAT W;
    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    __declspec(noinline) FColor(const FPlane &P);
    void operator+=(FColor C);
};

class FMatrix
{
public:
    FLOAT M[4][4];

    FPlane TransformFPlane(const FPlane &P) const;
    inline FVector TransformFPoint(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f));
    }
    inline FPlane TransformNormal(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 0.0f));
    }
    __declspec(noinline) FVector TransformFVector(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f));
    }
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

struct FStaticMeshSection
{
    INT f0;                 // +0x00
    INT IsStrip;            // +0x04
    _WORD FirstIndex;       // +0x08
    _WORD MinVertexIndex;   // +0x0a
    _WORD MaxVertexIndex;   // +0x0c
    _WORD NumTriangles;     // +0x0e
    _WORD NumPrimitives;    // +0x10
    _WORD Pad12;            // +0x12
};

struct FStaticMeshVertex
{
    FVector Position;       // +0x00
    FVector Normal;         // +0x0c
};

struct FStaticMeshColorStream
{
    void *Vtbl;                     // +0x00
    TArray<FColor> Colors;          // +0x04
    BYTE unk_10[0x08];              // +0x10
    INT Revision;                   // +0x18
};

class UStaticMesh
{
public:
    BYTE unk_00[0x50];
    TArray<FStaticMeshSection> Sections;    // +0x50
    void *VertexStreamVtbl;                 // +0x5c
    TArray<FStaticMeshVertex> Vertices;     // +0x60
    BYTE unk_6c[0x10];                      // +0x6c
    TArray<FColor> Colors;                  // +0x7c
    BYTE unk_88[0x148 - 0x88];
    UBOOL UseVertexColor;                   // +0x148
};

class FDynamicLight;

class AActor
{
public:
    BYTE unk_00[0x258];
    FLOAT LightScale;                       // +0x258
    TArray<AActor *> ExcludedLights;        // +0x25c
    BYTE unk_268[0x2d2 - 0x268];
    BYTE LightEffect;                       // +0x2d2

    FDynamicLight *GetLightRenderData();
};

class FDynamicLight
{
public:
    AActor *Actor;                          // +0x00
    INT Revision;                           // +0x04
    FVector Color;                          // +0x08
    BYTE unk_14[0x10];                      // +0x14
    FVector Direction;                      // +0x24
    INT unk_30;                             // +0x30
    DWORD Flags;                            // +0x34

    __declspec(noinline) FLOAT SampleIntensity(FVector Position, FVector Normal);
};

struct FStaticMeshLightInfo
{
    AActor *LightActor;             // +0x00
    TArray<BYTE> VisibilityBits;    // +0x04
    UBOOL Applied;                  // +0x10
};

class UStaticMeshInstance
{
public:
    BYTE unk_00[0x28];
    TArray<FStaticMeshLightInfo> Lights;    // +0x28
    FStaticMeshColorStream ColorStream;     // +0x34
};

struct FDynamicActor
{
    AActor *Actor;          // +0x00
    BYTE unk_04[0x0c];      // +0x04
    FMatrix LocalToWorld;   // +0x10
    FMatrix WorldToLocal;   // +0x50
};

struct FLevelSceneNode
{
    BYTE unk_00[0x194];
    FVector ViewOrigin;     // +0x194
};

class UMaterial;
class FRenderInterface;

class FIndexBuffer
{
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT GetRevision() = 0;
    virtual INT GetSize() = 0;
    virtual void GetContents(void *Data) = 0;
};

class FSortedIndexBuffer : public FIndexBuffer
{
public:
    UStaticMesh *StaticMesh;        // +0x04
    INT SectionIndex;               // +0x08
    FVector ViewOrigin;             // +0x0c
    BYTE unk_18[0x10];              // +0x18
    _WORD BaseVertexIndex;          // +0x28
    UBOOL ReverseOrder;             // +0x2c
    QWORD CacheId;                  // +0x30

    FSortedIndexBuffer(UStaticMesh *InStaticMesh, INT InSectionIndex, FVector InViewOrigin, _WORD InBaseVertexIndex, UBOOL InReverseOrder)
    :   StaticMesh(InStaticMesh)
    ,   SectionIndex(InSectionIndex)
    ,   ViewOrigin(InViewOrigin)
    ,   BaseVertexIndex(InBaseVertexIndex)
    ,   ReverseOrder(InReverseOrder)
    {}

    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetSize();
    virtual void GetContents(void *Data);
};

class FRenderState
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20();
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *Material, INT Flags); // +0x24
};

class FRenderInterface
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual INT SetDynamicIndexBuffer(FIndexBuffer *IndexBuffer, INT BaseIndex);    // +0x60
    virtual void DrawPrimitive(INT PrimitiveType, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // +0x64
    BYTE unk_04[0x10];
    FRenderState *State;    // +0x14
};

// RVA 0x14ca50: recompute static mesh instance vertex lighting from its static lights.
// Near miss: retail inlines UE2's multi-instruction __asm appMemzero (UnVcWin32.h);
// pure C++ memset reproduces the exact 0xa4 frame and every subsequent loop structurally
// but cannot match the __asm block or its EBX clobber / register allocation cascade.
__declspec(noinline) void UpdateStaticMeshLighting(
    UStaticMesh *StaticMesh,
    UStaticMeshInstance *Instance,
    FDynamicActor *DynamicActor)
{
    appMemzero(&Instance->ColorStream.Colors(0), Instance->ColorStream.Colors.Num() * sizeof(FColor));
    Instance->ColorStream.Revision++;

    for (INT LightIndex = 0; LightIndex < Instance->Lights.Num(); LightIndex++)
    {
        FStaticMeshLightInfo *LightInfo = &Instance->Lights(LightIndex);
        LightInfo->Applied = 0;
        if (LightInfo->LightActor)
        {
            FDynamicLight *Light = LightInfo->LightActor->GetLightRenderData();
            UBOOL bExcluded = 0;
            for (INT i = 0; i < DynamicActor->Actor->ExcludedLights.Num(); i++)
            {
                if (LightInfo->LightActor == DynamicActor->Actor->ExcludedLights(i))
                {
                    bExcluded = 1;
                    break;
                }
            }
            if (bExcluded)
                continue;
            if (Light && !(Light->Flags & 3))
            {
                FColor *DestStaticLighting = &Instance->ColorStream.Colors(0);
                FStaticMeshVertex *SrcVertex = &StaticMesh->Vertices(0);
                BYTE *VisibilityByte = LightInfo->VisibilityBits.Num() ? &LightInfo->VisibilityBits(0) : 0;
                BYTE BitMask = 1;

                for (INT VertexIndex = 0; VertexIndex < StaticMesh->Vertices.Num(); VertexIndex++)
                {
                    FVector SamplePoint = DynamicActor->LocalToWorld.TransformFPoint(SrcVertex->Position);
                    FVector SampleNormal = DynamicActor->LocalToWorld.TransformNormal(SrcVertex->Normal).SafeNormal();

                    if (*VisibilityByte & BitMask)
                    {
                        *DestStaticLighting += FColor(FPlane(
                            Light->Color * DynamicActor->Actor->LightScale * Light->SampleIntensity(SamplePoint, SampleNormal),
                            0.0f));
                    }

                    DestStaticLighting++;
                    SrcVertex++;
                    BitMask <<= 1;
                    if (!BitMask)
                    {
                        VisibilityByte++;
                        BitMask = 1;
                    }
                }
                LightInfo->Applied = 1;
            }
        }
    }

    FColor *SrcColor = &StaticMesh->Colors(0);
    FColor *DestColor = &Instance->ColorStream.Colors(0);
    for (INT VertexIndex = 0; VertexIndex < StaticMesh->Vertices.Num(); VertexIndex++)
    {
        if (StaticMesh->UseVertexColor)
        {
            DestColor->R = (SrcColor->R * DestColor->R) / 255;
            DestColor->G = (SrcColor->G * DestColor->G) / 255;
            DestColor->B = (DestColor->B * SrcColor->B) / 255;
        }
        DestColor->A = SrcColor->A;
        SrcColor++;
        DestColor++;
    }
}

// RVA 0x14cdd0: render a single sorted translucent static mesh section.
__declspec(noinline) void RenderSortedStaticMeshSection(
    FLevelSceneNode *SceneNode,
    FDynamicActor *DynamicActor,
    UStaticMesh *StaticMesh,
    INT SectionIndex,
    UMaterial *Material,
    FRenderInterface *RI)
{
    FStaticMeshSection &Section = StaticMesh->Sections(SectionIndex);
    if (Section.NumPrimitives > 0)
    {
        RI->State->SetMaterial(RI, Material, 0);
        FSortedIndexBuffer IndexBuffer(
            StaticMesh,
            SectionIndex,
            DynamicActor->WorldToLocal.TransformFVector(SceneNode->ViewOrigin),
            Section.MinVertexIndex,
            0);
        INT BaseIndex = RI->SetDynamicIndexBuffer(&IndexBuffer, 0);
        RI->DrawPrimitive(
            Section.IsStrip ? 1 : 0,
            BaseIndex,
            Section.NumPrimitives,
            Section.MinVertexIndex,
            Section.MaxVertexIndex);
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: LTCG callee bodies (matched
// in their own items or approximated for calling convention) and drivers.
void Escape(void *);

FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

FColor::FColor(const FPlane &P)
:   B((BYTE)Clamp(appFloor(P.Z * 256.f), 0, 255))
,   G((BYTE)Clamp(appFloor(P.Y * 256.f), 0, 255))
,   R((BYTE)Clamp(appFloor(P.X * 256.f), 0, 255))
,   A((BYTE)Clamp(appFloor(P.W * 256.f), 0, 255))
{
}

FLOAT FDynamicLight::SampleIntensity(FVector Position, FVector Normal)
{
    if (Actor->LightEffect == 0x13)
    {
        FLOAT Dot = Normal.X * Direction.X + Normal.Y * Direction.Y + Normal.Z * Direction.Z;
        if (Dot < 0.0f)
            return 0.0f;
        return Dot * 2.0f;
    }
    FLOAT DX = Position.X - Direction.X;
    FLOAT DY = Position.Y - Direction.Y;
    FLOAT DZ = Position.Z - Direction.Z;
    return DX * Normal.X + DY * Normal.Y + DZ * Normal.Z;
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }

void Driver_14ca50(
    UStaticMesh *StaticMesh,
    UStaticMeshInstance *Instance,
    FDynamicActor *DynamicActor,
    FColor *C,
    FPlane *P,
    FVector *V)
{
    Escape((void *)&UpdateStaticMeshLighting);
    FVector N = V->SafeNormal();
    Escape(&N);
    new (C) FColor(*P);
    new (C + 1) FColor(*(P + 1));
    UpdateStaticMeshLighting(StaticMesh, Instance, DynamicActor);
}

void Driver_14cdd0(
    FLevelSceneNode *SceneNode,
    FDynamicActor *DynamicActor,
    UStaticMesh *StaticMesh,
    INT SectionIndex,
    UMaterial *Material,
    FRenderInterface *RI)
{
    FVector V = DynamicActor->WorldToLocal.TransformFVector(SceneNode->ViewOrigin);
    Escape(&V);
    RenderSortedStaticMeshSection(SceneNode, DynamicActor, StaticMesh, SectionIndex, Material, RI);
    RenderSortedStaticMeshSection(SceneNode, DynamicActor, StaticMesh, SectionIndex + 1, Material, RI);
}
