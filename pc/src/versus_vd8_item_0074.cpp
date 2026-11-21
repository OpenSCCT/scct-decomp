// w4_item_0074.cpp -- UModel::FastLineCheck and FastLineCheckNode (Versus RVA 0x141d90, 0x141ef0)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;

#define MAXWORD 0xffff
#define NF_NotCsg 0x01

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FPlane : public FVector {
    FLOAT W;

    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

struct FBspNode {
    FPlane Plane;
    BYTE unk_10[0x20];
    INT iChild[2];
    BYTE unk_38[0x23];
    BYTE NodeFlags;
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray {
public:
    T *GetData() { return (T *)Data; }
    INT Num() const { return ArrayNum; }
};

class UModel {
public:
    BYTE unk_00[0x54];
    TArray<FBspNode> Nodes;
    BYTE unk_60[0xa4];
    UBOOL RootOutside;

    BYTE FastLineCheck(const FVector &End, const FVector &Start);
};

// File-static in UnModel.cpp; declared extern so the verifier can bind 0x10c8bc0c.
extern FBspNode *GFastLineCheckNodes;

// FastLineCheckNode -- recursive BSP traversal for UModel::FastLineCheck (RVA 0x141d90)
BYTE FastLineCheckNode(_WORD iNode, FVector End, const FVector &Start, BYTE Outside)
{
    while (iNode < MAXWORD) {
        FBspNode *Node = &GFastLineCheckNodes[iNode];
        BYTE NotCsg = Node->NodeFlags & NF_NotCsg;
        FLOAT Dist1 = Node->Plane.PlaneDot(Start);
        INT Front1 = (*(INT *)&Dist1 >= 0);
        FLOAT Dist2 = Node->Plane.PlaneDot(End);
        INT Front2 = (*(INT *)&Dist2 >= 0);

        if (Front1 != Front2) {
            FLOAT Alpha = Dist1 / (Dist1 - Dist2);
            FVector Mid;
            Mid.X = Start.X + (End.X - Start.X) * Alpha;
            Mid.Y = Start.Y + (End.Y - Start.Y) * Alpha;
            Mid.Z = Start.Z + (End.Z - Start.Z) * Alpha;
            if (!FastLineCheckNode(
                    (_WORD)Node->iChild[Front2],
                    Mid,
                    End,
                    ((Outside ^ Front2) & NotCsg) ^ Front2)) {
                return 0;
            }
            End = Mid;
        }
        iNode = (_WORD)Node->iChild[Front1];
        Outside = ((Outside ^ Front1) & NotCsg) ^ Front1;
    }
    return Outside;
}

// UModel::FastLineCheck (RVA 0x141ef0; noinline: retail kept it out of line)
__declspec(noinline) BYTE UModel::FastLineCheck(const FVector &End, const FVector &Start)
{
    GFastLineCheckNodes = Nodes.GetData();
    return Nodes.Num() ? FastLineCheckNode(0, End, Start, RootOutside) : RootOutside;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
BYTE Driver_141ef0(UModel *M, const FVector &End, const FVector &Start)
{
    Escape(&GFastLineCheckNodes);
    return M->FastLineCheck(End, Start);
}
