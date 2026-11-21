// Work item 0128: USkeletalMeshInstance vtable slots 76 and 77 (RVA 0xb8830, 0xb8800).
// Field and helper names are neutral; layout recovered from the retail code only.
typedef int INT;

struct FMeshAnimEntry_110 {          // 0x110-byte element of the mesh array at +0x1ac
    char Pad0[0x18];
    INT Value18;
    char Pad1[0x110 - 0x1c];
};

template<class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

struct USkeletalMesh_Partial {
    char Pad[0x1ac];
    TArray<FMeshAnimEntry_110> Entries;
};

struct USkeletalMeshInstance {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual USkeletalMesh_Partial *GetMesh();   // slot 32 (+0x80)

    char Pad[0xf0 - 4];
    INT CurrentIndex;                 // +0xf0

    INT GetEntryValue();              // slot 77
    INT CallHelper(INT Arg);          // slot 76
};

extern "C" INT FUN_109b8860(USkeletalMesh_Partial *Mesh, USkeletalMeshInstance *Inst, INT Arg, INT Zero, INT *ArgPtr);

INT USkeletalMeshInstance::GetEntryValue()
{
    INT Index = CurrentIndex;
    return GetMesh()->Entries(Index).Value18;
}

INT USkeletalMeshInstance::CallHelper(INT Arg)
{
    return FUN_109b8860(GetMesh(), this, Arg, 0, &Arg);
}
