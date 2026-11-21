// Work item 0311: BSP leaf gathering for a box (RVA 0x108320, 0x1085d0).
// Both functions were compiled with /GL and linked with /LTCG.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned short TCHAR;
typedef short SWORD;
#define INDEX_NONE -1

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

template <class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
inline FLOAT Fabs(FLOAT F) { *(DWORD *)&F &= 0x7fffffff; return F; }
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    INT Num() const { return ArrayNum; }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item) { INT Index = Add(1, sizeof(T)); (*this)(Index) = Item; return Index; }
};

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT GetMin() const { return Min(Min(X, Y), Z); }
    FLOAT GetMax() const { return Max(Max(X, Y), Z); }
    FLOAT Size() const { return (FLOAT)sqrt(X * X + Y * Y + Z * Z); }
};

class FPlane : public FVector
{
public:
    FLOAT W;
    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
};

class FBox
{
public:
    FVector Min;
    FVector Max;
};

// FBspNode-like record (0x5c bytes).
struct FBspNode
{
    FPlane Plane;           // 0x00
    char Pad10[0x20];
    INT iBack;              // 0x30
    INT iFront;             // 0x34
    char Pad38[0x14];
    SWORD iLeaf[2];         // 0x4c
    char Pad50[0x0c];
};

class UModel
{
public:
    char Pad0[0x54];
    TArray<FBspNode> Nodes; // 0x54
    void GetBoxLeaves(TArray<INT> &Leaves, const FBox &Box);
};

extern FLOAT Half_0_5;

// Retail 0x10992880 (box centre and half-size; LTCG: Box in EAX, Center in EDX, Extents in ECX).
__declspec(noinline) void GetCenterAndExtents(const FBox &Box, FVector &Center, FVector &Extents)
{
    Extents = Box.Max - Box.Min;
    Extents *= 0.5f;
    Center = Box.Min + Extents;
}

// Was a local static in the gathering function.
extern TArray<INT> GatherLeaves_NodeStack;

// Near miss (27 bytes): x87 stack layout around the radius fsqrt and operand order of some products.
void GatherLeaves(UModel *Model, INT iNode, const FVector &Extent, const FVector &Point, TArray<INT> &Leaves)
{
    if (GatherLeaves_NodeStack.Num() < Model->Nodes.Num())
        GatherLeaves_NodeStack.Add(Model->Nodes.Num() - GatherLeaves_NodeStack.Num(), sizeof(INT));
    INT *Stack = (INT *)GatherLeaves_NodeStack.Data;
    Stack[0] = iNode;
    INT Top = 0;
    if (Extent.GetMin() * 2.f > Extent.GetMax())
    {
        FLOAT Radius = Extent.Size();
        do
        {
            FBspNode &Node = Model->Nodes(Stack[Top--]);
            FLOAT Dist = (Node.Plane | Point) - Node.Plane.W;
            if (Dist < Radius)
            {
                if (Node.iBack != INDEX_NONE)
                    Stack[++Top] = Node.iBack;
                else if (Node.iLeaf[0] != INDEX_NONE)
                    Leaves.AddItem(Node.iLeaf[0]);
            }
            if (-Dist < Radius)
            {
                if (Node.iFront != INDEX_NONE)
                    Stack[++Top] = Node.iFront;
                else if (Node.iLeaf[1] != INDEX_NONE)
                    Leaves.AddItem(Node.iLeaf[1]);
            }
        } while (Top >= 0);
    }
    else
    {
        do
        {
            FBspNode &Node = Model->Nodes(Stack[Top--]);
            FLOAT PushOut = Fabs(Node.Plane.X * Extent.X) + Fabs(Node.Plane.Y * Extent.Y) + Fabs(Node.Plane.Z * Extent.Z);
            FLOAT Dist = (Node.Plane | Point) - Node.Plane.W;
            if (Dist < PushOut)
            {
                if (Node.iBack != INDEX_NONE)
                    Stack[++Top] = Node.iBack;
                else if (Node.iLeaf[0] != INDEX_NONE)
                    Leaves.AddItem(Node.iLeaf[0]);
            }
            if (-Dist < PushOut)
            {
                if (Node.iFront != INDEX_NONE)
                    Stack[++Top] = Node.iFront;
                else if (Node.iLeaf[1] != INDEX_NONE)
                    Leaves.AddItem(Node.iLeaf[1]);
            }
        } while (Top >= 0);
    }
}

void UModel::GetBoxLeaves(TArray<INT> &Leaves, const FBox &Box)
{
    if (Nodes.Num())
    {
        Leaves.Empty(sizeof(INT), Leaves.ArrayMax);
        FVector Center, Extent;
        GetCenterAndExtents(Box, Center, Extent);
        GatherLeaves(this, 0, Extent, Center, Leaves);
    }
    else
    {
        Leaves.ArrayNum = 0;
        if (Leaves.Data)
        {
            GMalloc->Free(Leaves.Data);
            Leaves.Data = 0;
            Leaves.ArrayMax = 0;
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1085d0(UModel *Model, TArray<INT> *Leaves, const FBox *Box)
{
    Escape(&GMalloc);
    Escape(&GatherLeaves_NodeStack);
    Model->GetBoxLeaves(*Leaves, *Box);
}
void Driver_92880(FBox *B, FVector *C, FVector *E) { GetCenterAndExtents(*B, *C, *E); }
