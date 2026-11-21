// Work item 0114: USkeletalMeshInstance helpers (RVA 0xb57b0, 0xb5870).
typedef int INT;
typedef float FLOAT;
typedef unsigned long DWORD;

struct FVector { FLOAT X, Y, Z; };

inline FLOAT Abs(FLOAT A) { return (A >= 0.f) ? A : -A; }
inline FLOAT Max(FLOAT A, FLOAT B) { return (A >= B) ? A : B; }

template<class T> struct TArray { T *Data; INT ArrayNum; INT ArrayMax; INT Num() const { return ArrayNum; } T &operator()(INT i) { return Data[i]; } };

// Skeletal mesh fields seen through the instance's GetMesh() (vtable slot 0x80).
struct FMeshAnimSeq { INT Name; char Pad[0x3c]; };
struct USkeletalMesh_Partial {
    char Pad0[0x4c]; FLOAT Scale4c;
    char Pad50[0x74 - 0x50]; FVector Extent74;
    char Pad80[0xd4 - 0x80]; FLOAT Radius;
    char PadD8[0x19c - 0xd8]; TArray<FMeshAnimSeq> AnimSeqs;
    char Pad1a8[0x2cc - 0x1a8]; TArray<INT> AliasFrom; TArray<INT> AliasTo;
};

extern const FLOAT GScaleConst_b5870;

class USkeletalMeshInstance {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual USkeletalMesh_Partial *GetMesh();
    INT FindAnimIndex(INT SeqName);
    __forceinline INT MatchAnim(INT SeqName)
    {
        for (INT j = 0; j < GetMesh()->AnimSeqs.Num(); j++)
            if (GetMesh()->AnimSeqs(j).Name == SeqName)
                return j;
        return -1;
    }
    void SetMeshExtent(FVector Extent);
};

// FINDBEGIN
__forceinline INT ResolveAlias(USkeletalMesh_Partial *Mesh, INT SeqName)
{
    for (INT i = 0; i < Mesh->AliasFrom.Num(); i++)
        if (SeqName == Mesh->AliasFrom(i))
            return Mesh->AliasTo(i);
    return SeqName;
}

INT USkeletalMeshInstance::FindAnimIndex(INT SeqName)
{
    USkeletalMesh_Partial *Mesh = GetMesh();
    INT Result = -1;
    if (SeqName) {
        SeqName = ResolveAlias(Mesh, SeqName);
        Result = MatchAnim(SeqName);
    }
    return Result;
}
// FINDEND
void USkeletalMeshInstance::SetMeshExtent(FVector Extent)
{
    USkeletalMesh_Partial *Mesh = GetMesh();
    Mesh->Extent74 = Extent;
    Mesh->Radius = Max(Abs(Mesh->Extent74.X), Max(Abs(Mesh->Extent74.Y), Abs(Mesh->Extent74.Z))) * Mesh->Scale4c * GScaleConst_b5870;
}
