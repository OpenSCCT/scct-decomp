// w4_item_0094.cpp -- Versus RVA 0x14e680-0x14e6b5 (1 function, 53 bytes).
// 0x14e680: UnnamedBspNodeList_14e680::AddNode (class and method names not
// independently evidenced; appends a BSP node index and its triangle count).

typedef unsigned char BYTE;
typedef short SWORD;
typedef int INT;
typedef float FLOAT;

#define INDEX_NONE -1

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FVector {
public:
    FLOAT X, Y, Z;
};

class FPlane : public FVector {
public:
    FLOAT W;
};

// FBspNode (0x5c bytes; layout from published versus_vd5_item_0311.cpp).
struct FBspNode {
    FPlane Plane;           // 0x00
    BYTE unk_10[0x20];
    INT iBack;              // 0x30
    INT iFront;             // 0x34
    BYTE unk_38[0x14];
    SWORD iLeaf[2];         // 0x4c
    BYTE unk_50[0x02];
    SWORD unk_52;           // 0x52
    BYTE unk_54[0x06];
    BYTE NumVertices;       // 0x5a
    BYTE unk_5b;
};

class UModel {
public:
    BYTE unk_00[0x54];
    TArray<FBspNode> Nodes; // 0x54
};

// Unnamed BSP node list structure (not independently evidenced).
class UnnamedBspNodeList_14e680 {
public:
    UModel *Model;          // 0x00
    INT unk_04;             // 0x04
    INT NumNodes;           // 0x08
    INT NumTriangles;       // 0x0c
    INT *Nodes;             // 0x10

    void AddNode(INT NodeIndex);
};

// UnnamedBspNodeList_14e680::AddNode (0x14e680)
// Appends a BSP node index and adds (NumVertices - 2) triangles when unk_52 != -1.
void UnnamedBspNodeList_14e680::AddNode(INT NodeIndex) {
    FBspNode &Node = Model->Nodes(NodeIndex);
    if (Node.unk_52 != INDEX_NONE) {
        Nodes[NumNodes++] = NodeIndex;
        NumTriangles += Node.NumVertices - 2;
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_14e680(UnnamedBspNodeList_14e680 *A, UnnamedBspNodeList_14e680 *B, INT I, INT J) {
    switch (I) {
    case 0:
        A->AddNode(J);
        break;
    case 1:
        B->AddNode(J);
        break;
    case 2:
        A->AddNode(J + 1);
        break;
    case 3:
        B->AddNode(J + 1);
        break;
    case 4:
        A->AddNode(J + 2);
        break;
    case 5:
        B->AddNode(J + 2);
        break;
    case 6:
        A->AddNode(J + 3);
        break;
    case 7:
        B->AddNode(J + 3);
        break;
    case 8:
        A->AddNode(J + 4);
        break;
    case 9:
        B->AddNode(J + 4);
        break;
    default:
        A->AddNode(I);
        B->AddNode(J);
        break;
    }
}
