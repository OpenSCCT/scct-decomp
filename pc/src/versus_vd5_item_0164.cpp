// Work item 0164: UStaticMesh neighbours (RVA 0xcaff0-0xcb383).
// The object was built with VC7.0 /GL and linked /LTCG (0xcb020 calls
// 0xcb060 with `this` in EAX, which calls the TArray destructor with
// `this` on the stack).
#include "versus_build.h"
#include "versus_static_mesh_triangle.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    ~TArray()
    {
        Remove(0, ArrayNum, sizeof(T));
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

// 12-byte element; neutral name (member 2 tracks member 1).
struct FUnnamedRevision_caff0 { INT Unknown0; INT Revision; INT LastRevision; };

// 12-byte element of the owned render data at +0xbc; neutral name.
struct FUnnamedElement_cb060 { INT Unknown[3]; };

// Owned object at UStaticMesh+0xbc; destructor is RVA 0xcb060. Neutral name.
struct FUnnamedRenderData_cb060 {
    INT Unknown0;
    TArray<FUnnamedElement_cb060> Elements; // +4
    void operator delete(void *P) { GMalloc->Free(P); }
};

class UObject {
public:
    void Destroy(); // RVA 0x15ce0
};

// UStaticMesh fragment (offsets only; the vtable pointer lives in Pad).
class UStaticMesh : public UObject {
public:
    BYTE Pad[0xbc];
    FUnnamedRenderData_cb060 *RenderData;       // 0xbc
    BYTE Pad2[0xdc - 0xc0];
    TArray<FUnnamedRevision_caff0> Revisions;   // 0xdc
    INT UpdateRevisions();
    void Destroy();
};

// RVA 0xcaff0, UStaticMesh vtable slot 16.
INT UStaticMesh::UpdateRevisions()
{
    INT i;
    for (i = 0; i < Revisions.Num(); i++)
    {
        FUnnamedRevision_caff0 &R = Revisions(i);
        if (R.Revision != R.LastRevision)
            return R.LastRevision = R.Revision;
    }
    return i;
}

// RVA 0xcb020, UStaticMesh vtable slot 9.
void UStaticMesh::Destroy()
{
    if (RenderData)
    {
        delete RenderData;
        RenderData = 0;
    }
    UObject::Destroy();
}

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(void *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(FName &N);
    INT ArVer;
    INT Ver() { return ArVer; }
    void ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.ByteOrderSerialize(&D, sizeof(D)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.ByteOrderSerialize(&F, sizeof(F)); return Ar; }
};

inline FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
inline FArchive &operator<<(FArchive &Ar, FColor &C) { return Ar << C.R << C.G << C.B << C.A; }
inline FArchive &operator<<(FArchive &Ar, FStaticMeshUV &UV) { return Ar << UV.U << UV.V; }

inline FColor MeshColor(BYTE R, BYTE G, BYTE B, BYTE A)
{
    FColor Color = {B, G, R, A};
    return Color;
}

// Pre-version-111 vertex record (32 bytes); its serializer is RVA 0x86b40
// (LTCG: archive in ESI, vertex in EAX). Neutral name.
struct FStaticMeshVertexLegacy_86b40 {
    FVector Position;
    FVector Normal;
    FStaticMeshUV UV;
};
FArchive &operator<<(FArchive &Ar, FStaticMeshVertexLegacy_86b40 &V)
{
    return Ar << V.Position << V.Normal << V.UV;
}

// RVA 0xcb070 (LTCG: archive in EDI, triangle in EAX, returns the archive).
FArchive &operator<<(FArchive &Ar, FStaticMeshTriangle &T)
{
    if (Ar.Ver() < 111)
    {
        FStaticMeshVertexLegacy_86b40 OldVertices[3];
        Ar << OldVertices[0] << OldVertices[1] << OldVertices[2];
        T.Vertices[0] = OldVertices[0].Position;
        T.UVs[0][0] = OldVertices[0].UV;
        T.Colors[0] = MeshColor(255, 255, 255, 255);
        T.Vertices[1] = OldVertices[1].Position;
        T.UVs[1][0] = OldVertices[1].UV;
        T.Colors[1] = MeshColor(255, 255, 255, 255);
        T.Vertices[2] = OldVertices[2].Position;
        T.UVs[2][0] = OldVertices[2].UV;
        T.Colors[2] = MeshColor(255, 255, 255, 255);
        T.NumUVs = 1;
    }
    else
    {
        Ar << T.Vertices[0] << T.Vertices[1] << T.Vertices[2];
        Ar << T.NumUVs;
        for (INT UVIndex = 0; UVIndex < T.NumUVs; UVIndex++)
            Ar << T.UVs[0][UVIndex] << T.UVs[1][UVIndex] << T.UVs[2][UVIndex];
        Ar << T.Colors[0] << T.Colors[1] << T.Colors[2];
    }
    if (Ar.Ver() < 112)
    {
        FVector LegacyNormal;
        Ar << LegacyNormal;
        Ar << T.LegacyMaterialName << T.LegacyPolyFlags;
    }
    else
        Ar << T.MaterialIndex;
    Ar << T.SmoothingMask;
    return Ar;
}

// ---- Scaffolding for the LTCG link, not part of the unit. ----
void Escape(void *);
// Retail reaches these through the vtable; taking their address keeps the standard convention.
void Driver_caff0() { INT (UStaticMesh::*P)() = &UStaticMesh::UpdateRevisions; Escape(&P); }
void Driver_cb020() { Escape(&GMalloc); void (UStaticMesh::*P)() = &UStaticMesh::Destroy; Escape(&P); }
void Driver_cb070(FArchive &Ar, FStaticMeshTriangle &T) { Ar << T; }
