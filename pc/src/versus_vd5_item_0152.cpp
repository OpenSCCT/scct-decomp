// Work item 0152: Versus RVA 0xc5270-0xc56d0.
inline void *operator new(unsigned int, void *P) { return P; }
typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

// Six floats read from the owning actor at +0x444 (two FVectors).
struct FProjectorExtent { FVector Min, Max; };

class AActor;

// Owner actor; only the extent field at 0x444 is used here.
class AProjector_Unnamed {
public:
    char Pad[0x444];
    FProjectorExtent Extent;
};

// UProjectorPrimitive, vtable slot 26 (reflected_vtable UProjectorPrimitive@309320[26]).
class UProjectorPrimitive {
public:
    virtual FProjectorExtent GetExtent(AProjector_Unnamed *Owner);
};

FProjectorExtent UProjectorPrimitive::GetExtent(AProjector_Unnamed *Owner)
{
    return Owner->Extent;
}

// ---------------------------------------------------------------------------
// 0xc5270 (LTCG, this in ESI): constructor of a render-resource style object.
// Neutral name: vtable at 0x10c04908 is unlabelled. The 64-bit field at 0x10
// is a cache id made from a global 64-bit counter and type tag 0xE1.
typedef unsigned __int64 QWORD;
extern QWORD GCacheIdCounter_Unnamed;

// Unreal headers pack to 4, so the QWORD follows the three ints directly.
#pragma pack(push, 4)
struct FArray_Unnamed {
    void *Data; INT ArrayNum; INT ArrayMax;
    FArray_Unnamed() : Data(0), ArrayNum(0), ArrayMax(0) {}
};
inline QWORD MakeCacheID_Unnamed(QWORD Type) { return GCacheIdCounter_Unnamed++ * 256 + Type; }
class FUnnamedResource_c5270 {
public:
    FUnnamedResource_c5270();
    virtual ~FUnnamedResource_c5270();
    FArray_Unnamed Items;
    QWORD CacheId;
};
#pragma pack(pop)

// Retail keeps this base constructor out of line; auto_inline(off) stands in.
#pragma auto_inline(off)
FUnnamedResource_c5270::FUnnamedResource_c5270()
{
    CacheId = MakeCacheID_Unnamed(0xE1);
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
class FUnnamedDerived_c5270 : public FUnnamedResource_c5270 {
public:
    FUnnamedDerived_c5270(INT V) : Value(V) {}
    INT Value;
};
void UseResource(FUnnamedResource_c5270 *);
void Driver_c5270(INT V)
{
    // No Escape: retail hoists the counter load above the field stores.
    FUnnamedDerived_c5270 R(V);
    UseResource(&R);
}
void Driver2_c5270(INT V)
{
    FUnnamedDerived_c5270 R(V);
    UseResource(&R);
}

// ---------------------------------------------------------------------------
// 0xc52d0 (LTCG, object in EAX): resolve an object to its owning object.
// Classes are unlabelled; names are neutral. UObject::Class is at 0x24 and
// UField::SuperField at 0x28 as in Unreal Engine 2.
class UClass;
class UObject {
public:
    char ObjectPad[0x24];
    UClass *Class;
    inline DWORD IsA(UClass *SomeBase) const;
};
class UField : public UObject {
public:
    UField *SuperField;
};
class UClass : public UField {
};
inline DWORD UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}
template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

// The three classes share an owner reference at 0x4c.
class UOwnedObject_Unnamed : public UObject {
public:
    char OwnedPad[0x4c - 0x28];
    UObject *OwnerObject;
};
class UUnnamedClass_cc49e8 : public UOwnedObject_Unnamed {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class UUnnamedClass_cc47b8 : public UOwnedObject_Unnamed {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class UUnnamedClass_cc48d0 : public UOwnedObject_Unnamed {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

#pragma auto_inline(off)
UObject *ResolveOwner_c52d0(UObject *Obj)
{
    if (Obj) {
        if (Cast<UUnnamedClass_cc49e8>(Obj))
            return ((UUnnamedClass_cc49e8 *)Obj)->OwnerObject;
        if (Cast<UUnnamedClass_cc47b8>(Obj)) {
            UObject *Owner = ((UUnnamedClass_cc47b8 *)Obj)->OwnerObject;
            if (Cast<UUnnamedClass_cc48d0>(Owner))
                return ((UUnnamedClass_cc48d0 *)Owner)->OwnerObject;
            return Owner;
        }
        if (Cast<UUnnamedClass_cc48d0>(Obj)) {
            UObject *Owner = ((UUnnamedClass_cc48d0 *)Obj)->OwnerObject;
            UUnnamedClass_cc47b8 *BOwner = Cast<UUnnamedClass_cc47b8>(Owner);
            if (!BOwner)
                return Owner;
            return BOwner->OwnerObject;
        }
    }
    return Obj;
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Driver_c52d0(UObject **Out, UObject *Obj)
{
    *Out = ResolveOwner_c52d0(Obj);
}

// ---------------------------------------------------------------------------
// 0xc5360 (LTCG: this on the stack and unused, Info in EBX, Obj on the stack,
// ret 8): build or refresh a chain of three cached projector materials.
// The material layout matches UE2's UMaterial (FallbackMaterial, UseFallback)
// but the classes are unlabelled, so names are neutral.
struct FName { INT Index; FName(INT N) : Index(N) {} };
class FOutputDevice;
extern FOutputDevice *GError;
extern UObject *GTransientPackage_Unnamed;  // UObject::GetTransientPackage() inlined

struct FArray {
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);   // @add_array@12
};
template <class T> struct TArray : public FArray {
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

struct FMatrix { FLOAT M[4][4]; };

UObject *StaticConstructObject_Unnamed(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
    UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot, INT Extra);
template <class T> inline T *ConstructObject(UClass *Class, UObject *Outer = GTransientPackage_Unnamed,
    FName Name = 0, DWORD SetFlags = 0, UObject *Template = 0, FOutputDevice *Error = GError,
    UObject *SubobjectRoot = 0, INT Extra = 0)
{
    return (T *)StaticConstructObject_Unnamed(Class, Outer, Name, SetFlags, Template, Error, SubobjectRoot, Extra);
}

// Object whose TArray at 0x28 holds addresses of permanently referenced objects.
class URootHolder_Unnamed : public UObject {
public:
    TArray<UObject **> RootRefs;
};
extern URootHolder_Unnamed *GRootHolder_Unnamed;
extern void (*GObjectCreatedHook_Unnamed)(UObject *);

class UMaterial_Unnamed : public UObject {
public:
    char MaterialPad[0x3c - 0x28];
    UMaterial_Unnamed *FallbackMaterial;   // 0x3c
    INT Pad40;
    DWORD UseFallback : 1;                 // 0x44
    INT Pad48;
};
class UProjMaterial_Unnamed : public UMaterial_Unnamed {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    FMatrix Matrix;            // 0x4c
    FMatrix BaseMatrix;        // 0x8c
    INT ValueCC;               // 0xcc
    INT ValueD0;               // 0xd0
    UObject *SourceObject;     // 0xd4
    unsigned char BlendD8;     // 0xd8
    unsigned char BlendD9;     // 0xd9
    DWORD Bit0 : 1;            // 0xdc
    DWORD Bit1 : 1;
    DWORD Bit2 : 1;
    DWORD Bit3 : 1;
    DWORD Bit4 : 1;
    DWORD Bit5 : 1;
    DWORD Bit6 : 1;
    DWORD Bit7 : 1;
};

struct FProjInfo_Unnamed {
    char Pad[0x18];
    INT ValueD0;               // 0x18
    INT ValueCC;               // 0x1c
    unsigned char BlendD8;     // 0x20
    unsigned char BlendD9;     // 0x21
    char Pad22[2];
    FMatrix Matrix;            // 0x24
    char Pad64[0x11c - 0x64];
    FMatrix BaseMatrix;        // 0x11c
    DWORD Bit0 : 1;            // 0x15c
    DWORD Bit1 : 1;
    DWORD Bit2 : 1;
    DWORD Bit3 : 1;
    DWORD Bit4 : 1;
    DWORD Bit5 : 1;
};

class UFlagSourceA_Unnamed : public UObject {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    char Pad[0x70 - 0x28];
    DWORD bFlag : 1;           // 0x70
};
class UFlagSourceB_Unnamed : public UObject {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    char Pad[0x60 - 0x28];
    DWORD bFlag : 1;           // 0x60
};
class UFlagSourceC_Unnamed : public UObject {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    char Pad[0x54 - 0x28];
    DWORD Bits0 : 3;           // 0x54
    DWORD bFlag : 1;
};

// The three cached materials (rooted globals).
extern UProjMaterial_Unnamed *GProjMaterial0_Unnamed;
extern UProjMaterial_Unnamed *GProjMaterial1_Unnamed;
extern UProjMaterial_Unnamed *GProjMaterial2_Unnamed;

inline void InitProjMaterial(UProjMaterial_Unnamed *&Material)
{
    if (!Material) {
        UProjMaterial_Unnamed *New = ConstructObject<UProjMaterial_Unnamed>(UProjMaterial_Unnamed::StaticClass());
        if (New)
            GObjectCreatedHook_Unnamed(New);
        Material = New;
        GRootHolder_Unnamed->RootRefs.AddItem((UObject **)&Material);
    }
}

class UProjHelper_Unnamed {
public:
    UProjMaterial_Unnamed *GetMaterial(FProjInfo_Unnamed *Info, UObject *Obj);
};

#pragma auto_inline(off)
UProjMaterial_Unnamed *UProjHelper_Unnamed::GetMaterial(FProjInfo_Unnamed *Info, UObject *Obj)
{
    Obj = ResolveOwner_c52d0(Obj);
    InitProjMaterial(GProjMaterial0_Unnamed);
    InitProjMaterial(GProjMaterial1_Unnamed);
    InitProjMaterial(GProjMaterial2_Unnamed);

    UProjMaterial_Unnamed *Materials[3] = { GProjMaterial0_Unnamed, GProjMaterial1_Unnamed, GProjMaterial2_Unnamed };
    GProjMaterial0_Unnamed->FallbackMaterial = GProjMaterial1_Unnamed;
    GProjMaterial1_Unnamed->FallbackMaterial = GProjMaterial2_Unnamed;

    UFlagSourceA_Unnamed *A = Cast<UFlagSourceA_Unnamed>(Obj);
    UFlagSourceB_Unnamed *B = Cast<UFlagSourceB_Unnamed>(Obj);
    UFlagSourceC_Unnamed *C = Cast<UFlagSourceC_Unnamed>(Obj);
    DWORD Flag = 0;
    if (A)
        Flag = A->bFlag;
    else if (B)
        Flag = B->bFlag;
    else if (C)
        Flag = C->bFlag;

    for (INT i = 0; i < 3; i++) {
        Materials[i]->ValueCC = Info->ValueCC;
        Materials[i]->ValueD0 = Info->ValueD0;
        Materials[i]->SourceObject = Obj;
        Materials[i]->BlendD8 = Info->BlendD8;
        Materials[i]->BlendD9 = Info->BlendD9;
        Materials[i]->Matrix = Info->Matrix;
        Materials[i]->BaseMatrix = Info->BaseMatrix;
        Materials[i]->UseFallback = 0;
        Materials[i]->Bit0 = Info->Bit0;
        Materials[i]->Bit1 = Info->Bit1;
        Materials[i]->Bit2 = Info->Bit2;
        Materials[i]->Bit3 = Info->Bit3;
        Materials[i]->Bit4 = Info->Bit4;
        Materials[i]->Bit6 = Info->Bit5;
        Materials[i]->Bit5 = 0;
        Materials[i]->Bit7 = Flag;
    }
    Materials[1]->Bit2 = 0;
    Materials[2]->Bit2 = 0;
    Materials[2]->Bit4 = 1;
    return GProjMaterial0_Unnamed;
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c5360(UProjHelper_Unnamed *Helper, FProjInfo_Unnamed *Info, UObject *Obj, UObject **Out)
{
    Escape(&GProjMaterial0_Unnamed);
    Escape(&GProjMaterial1_Unnamed);
    Escape(&GProjMaterial2_Unnamed);
    Escape(&GRootHolder_Unnamed);
    *Out = Helper->GetMaterial(Info, Obj);
}
