// Work item 0158: RVA 0xc82f0, a triangle clipper. A triangle given as three
// vertex indices is clipped (Sutherland-Hodgman) against the six outcode
// planes, then the resulting polygon is fan-triangulated into a 16-bit index
// list. Names are neutral: the owning class is not identified.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
};
extern FMalloc *GMalloc;

// String constants shared with other array code.
extern const TCHAR FArrayAdd_Tag[];  // L"FArray::Add"
extern const TCHAR FArray_Tag[];     // L"FArray"

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;

    void Realloc()
    {
        if (Data == 0)
            Data = (T *)GMalloc->Malloc(ArrayMax * sizeof(T), FArrayAdd_Tag);
        else
            Data = (T *)GMalloc->Realloc(Data, ArrayMax * sizeof(T), FArray_Tag);
    }
    INT Add(INT Count)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            Realloc();
        }
        return Index;
    }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1);
        Data[Index] = Item;
        return Index;
    }
    INT AddUniqueItem(const T &Item);
};

// Out of line in retail (0xc9bb0, custom LTCG convention: this in ESI, item in EBX).
template<class T> INT TArray<T>::AddUniqueItem(const T &Item)
{
    for (INT Index = 0; Index < ArrayNum; Index++)
        if (Data[Index] == Item)
            return Index;
    return AddItem(Item);
}

struct FClipVertex
{
    BYTE Pad[0x1c];
    BYTE Outcode;
};

struct FClipVertexData  // 0x34 bytes
{
    BYTE Pad[0x34];
};

struct UnnamedClipper_c82f0
{
    BYTE Pad0[8];
    BYTE *SharedVerts;              // 0x08, negative indices count back from here (0x20-byte entries)
    BYTE Pad1[8];
    TArray<FClipVertexData> Verts;  // 0x14
    TArray<INT> Indices;            // 0x20

    FClipVertex *GetVertex(INT Index)
    {
        if (Index < 0)
            return (FClipVertex *)(SharedVerts - (Index + 1) * 32);
        return (FClipVertex *)&Verts.Data[Index];
    }
    void ClipTriangle(TArray<_WORD> *Out, INT A, INT B, INT C);
};

// 0xc7e80: makes the intersection vertex on edge Prev-Cur for one plane.
INT __stdcall ClipEdge_c7e80(UnnamedClipper_c82f0 *This, INT Prev, INT Cur, BYTE Plane);

void UnnamedClipper_c82f0::ClipTriangle(TArray<_WORD> *Out, INT A, INT B, INT C)
{
    INT Cur = 0;
    FClipVertex *VA = GetVertex(A);
    FClipVertex *VB = GetVertex(B);
    FClipVertex *VC = GetVertex(C);
    if (VA->Outcode & VB->Outcode & VC->Outcode)
        return;

    INT Num[2];
    DWORD Planes[6];
    INT Poly[2][16];
    Poly[0][0] = A;
    Poly[0][1] = B;
    Poly[0][2] = C;
    Num[0] = 3;
    Planes[0] = 1;
    Planes[1] = 2;
    Planes[2] = 4;
    Planes[3] = 8;
    Planes[4] = 16;
    Planes[5] = 32;

    for (INT P = 0; P < 6; P++)
    {
        INT Prev = Poly[Cur][Num[Cur] - 1];
        Cur = 1 - Cur;
        Num[Cur] = 0;
        for (INT i = 0; i < Num[1 - Cur]; i++)
        {
            INT V = Poly[1 - Cur][i];
            FClipVertex *VP = GetVertex(V);
            FClipVertex *PP = GetVertex(Prev);
            if (VP->Outcode & Planes[P])
            {
                if (!(PP->Outcode & Planes[P]))
                    Poly[Cur][Num[Cur]++] = ClipEdge_c7e80(this, Prev, V, (BYTE)Planes[P]);
            }
            else if (PP->Outcode & Planes[P])
            {
                Poly[Cur][Num[Cur]++] = ClipEdge_c7e80(this, Prev, V, (BYTE)Planes[P]);
                Poly[Cur][Num[Cur]++] = Poly[1 - Cur][i];
            }
            else
                Poly[Cur][Num[Cur]++] = V;
            Prev = Poly[1 - Cur][i];
        }
        if (Num[Cur] == 0)
            break;
    }

    if (Num[Cur])
    {
        _WORD First = (_WORD)Indices.AddUniqueItem(Poly[Cur][0]);
        _WORD Last = (_WORD)Indices.AddUniqueItem(Poly[Cur][1]);
        for (INT i = 2; i < Num[Cur]; i++)
        {
            Out->AddItem(First);
            Out->AddItem(Last);
            Last = (_WORD)Indices.AddUniqueItem(Poly[Cur][i]);
            Out->AddItem(Last);
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c82f0(UnnamedClipper_c82f0 *Clipper, TArray<_WORD> *Out, INT A, INT B, INT C)
{
    Escape(&GMalloc);
    Clipper->ClipTriangle(Out, A, B, C);
}
