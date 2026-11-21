// RVA 0xb6240: builds a bone remap table between two skeletal meshes.
// Class and member names are neutral guesses (no vtable/string evidence).
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(unsigned long Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, unsigned long Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

// 64-byte bone entry; first field is the bone name.
struct FMeshBone_b6240 {
    INT Name;
    INT Pad[15];
};

// Neutral name: mesh object with its bone array at 0x19c.
class UnnamedMesh_b6240 {
public:
    char Pad[0x19c];
    TArray<FMeshBone_b6240> Bones;
};

// Neutral name: owner of the remap table at 0xc.
class UnnamedRemap_b6240 {
public:
    char Pad[0xc];
    TArray<INT> Map;
    INT __cdecl Build(UnnamedMesh_b6240 *Src, UnnamedMesh_b6240 *Dst);
};

INT __cdecl UnnamedRemap_b6240::Build(UnnamedMesh_b6240 *Src, UnnamedMesh_b6240 *Dst)
{
    INT Matched = 0;
    Map.Empty();
    Map.Add(Src->Bones.Num(), sizeof(INT));
    for (INT i = 0; i < Src->Bones.Num(); i++) {
        Map(i) = -1;
        for (INT j = 0; j < Dst->Bones.Num(); j++) {
            if (Dst->Bones(j).Name == Src->Bones(i).Name) {
                Map(i) = j;
                Matched++;
                break;
            }
        }
    }
    return Matched;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_b6240(UnnamedRemap_b6240 *R, UnnamedMesh_b6240 *A, UnnamedMesh_b6240 *B)
{
    Escape(&GMalloc);
    return R->Build(A, B);
}
