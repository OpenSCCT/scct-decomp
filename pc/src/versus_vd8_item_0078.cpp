// Work item w4_0078: Versus RVA 0x143490-0x14377f (UModel::ConvexVolumeMultiCheck and helper).
//   0x143490 ConvexVolumeMultiCheckFilter (BSP traversal helper)
//   0x143590 UModel::ConvexVolumeMultiCheck
// Compiled with VC7.0 /GL and linked with /LTCG.

typedef unsigned char BYTE;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;

#define INDEX_NONE -1
#define PF_Invisible 0x00000001

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

template <class T> class TTransArray : public TArray<T>
{
public:
    void *Owner;
};

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};

struct FPlane : public FVector
{
    FLOAT W;

    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
};

struct FBox
{
    FVector Min;
    FVector Max;
    BYTE IsValid;

    FVector GetCenter() const { return FVector((Min + Max) * 0.5f); }
    FVector GetExtent() const { return (Max - Min) * 0.5f; }
};

FLOAT BoxPushOut(const FVector &Normal, const FVector &Size);

struct FVert
{
    SWORD pVertex;
};

struct FBspNode
{
    FPlane Plane;               // 0x00
    BYTE unk_10[0x28 - 0x10];
    INT iVertPool;              // 0x28
    INT iSurf;                  // 0x2c
    INT iBack;                  // 0x30
    INT iFront;                 // 0x34
    INT iPlane;                 // 0x38
    BYTE unk_3c[0x5a - 0x3c];
    BYTE NumVertices;           // 0x5a
    BYTE unk_5b;
};

struct FBspSurf
{
    BYTE unk_00[0x14];
    DWORD PolyFlags;            // 0x14
    BYTE unk_18[0x2c - 0x18];
};

class UModel
{
public:
    BYTE unk_00[0x54];
    TTransArray<FBspNode> Nodes;    // 0x54
    TTransArray<FVert> Verts;       // 0x64
    TTransArray<FVector> Vectors;   // 0x74
    TTransArray<FVector> Points;    // 0x84
    TTransArray<FBspSurf> Surfs;    // 0x94

    INT ConvexVolumeMultiCheck(
        FBox &Box, FPlane *Planes, INT NumPlanes, const FVector &Dir, TArray<INT> &Result);
};

// RVA 0x143490: recursive BSP node filter for ConvexVolumeMultiCheck.
void ConvexVolumeMultiCheckFilter(
    UModel *Model, INT iNode, const FVector &Location, const FVector &Extent,
    const FVector &Dir, TArray<INT> &Result)
{
    while (iNode != INDEX_NONE)
    {
        FBspNode &Node = Model->Nodes(iNode);
        FLOAT PushOut = BoxPushOut(Node.Plane, Extent);
        FLOAT Dist = Node.Plane.PlaneDot(Location);

        if (Dist > PushOut)
        {
            iNode = Node.iFront;
        }
        else if (Dist < -PushOut)
        {
            iNode = Node.iBack;
        }
        else
        {
            while (iNode != INDEX_NONE)
            {
                FVector Normal = Model->Nodes(iNode).Plane;
                if ((Normal | Dir) < -0.0001f)
                    Result.AddItem(iNode);
                iNode = Model->Nodes(iNode).iPlane;
            }
            ConvexVolumeMultiCheckFilter(Model, Node.iFront, Location, Extent, Dir, Result);
            iNode = Node.iBack;
        }
    }
}

// RVA 0x143590: UModel::ConvexVolumeMultiCheck.
INT UModel::ConvexVolumeMultiCheck(
    FBox &Box, FPlane *Planes, INT NumPlanes, const FVector &Dir, TArray<INT> &Result)
{
    Result.Empty();
    if (Nodes.Num())
    {
        ConvexVolumeMultiCheckFilter(
            this, 0, Box.GetCenter(), Box.GetExtent() * 1.1f, Dir, Result);
        for (INT NodeIndex = 0; NodeIndex < Result.Num(); NodeIndex++)
        {
            FBspNode &Node = Nodes(Result(NodeIndex));
            if (!(Surfs(Node.iSurf).PolyFlags & PF_Invisible))
            {
                for (INT PlaneIndex = 0; PlaneIndex < NumPlanes; PlaneIndex++)
                {
                    UBOOL Outside = 1;
                    for (INT VertexIndex = 0; VertexIndex < Node.NumVertices; VertexIndex++)
                    {
                        if (Planes[PlaneIndex].PlaneDot(
                                Points(Verts(Node.iVertPool + VertexIndex).pVertex)) > 0.0f)
                        {
                            Outside = 0;
                            break;
                        }
                    }
                    if (Outside)
                    {
                        Result.Remove(NodeIndex--);
                        break;
                    }
                }
            }
        }
    }
    return Result.Num();
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

// Stand-in for retail 0xc9d60 (BoxPushOut, published in versus_vd5_item_0160.cpp).
// Reproduces its LTCG calling convention (Normal in ecx, Size in eax), no-memory-write
// property, and caller-saved edx kill-set from the retail multi-object link.
__declspec(noinline) FLOAT BoxPushOut(const FVector &Normal, const FVector &Size)
{
    FLOAT PX = Normal.X * Size.X;
    FLOAT PY = Normal.Y * Size.Y;
    FLOAT PZ = Normal.Z * Size.Z;
    DWORD A = *(DWORD *)&PX & 0x7fffffff;
    DWORD B = *(DWORD *)&PY & 0x7fffffff;
    DWORD C = *(DWORD *)&PZ & 0x7fffffff;
    *(DWORD *)&PX = A % (B | 1);
    *(DWORD *)&PY = B;
    *(DWORD *)&PZ = C;
    return PX + PY + PZ;
}

#pragma inline_depth(0)
INT Driver_143590(
    UModel *Model, FBox *Box, FPlane *Planes, INT NumPlanes,
    const FVector *Dir, TArray<INT> *Result)
{
    Escape(&GMalloc);
    return Model->ConvexVolumeMultiCheck(*Box, Planes, NumPlanes, *Dir, *Result);
}
#pragma inline_depth()
