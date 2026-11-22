// Work item w3 0176: Versus RVA 0xdf4e0-0xdf6dc (Engine UnMeshAnim / UnMesh, LTCG objects).
// 0xdf4e0 UMesh::MeshGetInstance(const AActor*): returns the owner's mesh instance
//         (AActor+0x1d4) or the mesh's default instance (UMesh+0x50), creating a
//         new one of MeshGetInstanceClass() (default UMeshInstance class object at
//         0x10cbf1f0) through an inlined StaticConstructObject.
// 0xdf5e0 FMeshAnimSeq::UpdateOldNotifies(UObject*): converts old by-name notifies
//         into UAnimNotify_Script objects (class 0x10cc1220, NotifyName at +0x2c).
//         this in EDI, one stack argument, ret 4.
// 0xdf670 operator<<(FArchive&, FMeshAnimSeq&): Ar in ESI, sequence in EAX.
// Names follow Unreal Engine 2 (UnMeshAnim.h); the virtual slot names of
// UMeshInstance and the AActor flag bit are neutral guesses.
// All three match with try_ltcg.py --flags "/O2 /Gy" rooted at Driver_df4e0 / Driver_df5e0 / Driver_df670.
// The compact-index serializer below is a stand-in (item 0116) so the link gives
// the TArray<FName> serializer (0x1fd80) its retail Ar-in-EAX, array-in-EBX convention.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

enum EName { NAME_None = 0 };
class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator!=(const FName &O) const { return Index != O.Index; }
};

class UObject;
class UClass;
class FOutputDevice;
extern FOutputDevice *GError;            // 0x10c71aa8

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(FName &N);                 // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &D) { Ar.Serialize(&D, sizeof(D)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &D) { Ar.Serialize(&D, sizeof(D)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
    INT Add(INT Count) { return FArray::Add(Count, sizeof(T)); }

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(&((T *)A.Data)[A.Add(1)]) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};
inline void *operator new(unsigned int, void *Mem) { return Mem; }

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;          // 0x18
    UObject *GetOuter() const { return Outer; }
    DWORD ObjectFlags;       // 0x1c
    FName Name;              // 0x20
    UClass *Class;           // 0x24

    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                         UObject *Template, FOutputDevice *Error, UObject *Ptr,
                                         UObject *SubobjectRoot);       // 0x1d380
    static UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                          UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot);
};

class UClass
{
public:
    DWORD Pad[0xac / 4];
    UObject *DefaultObject;                 // +0xac (template object)
    DWORD Pad2[(0x104 - 0xb0) / 4];
    void (*ClassConstructor)(void *);       // +0x104
};

inline UObject *UObject::StaticConstructObject(UClass *InClass, UObject *InOuter, FName InName, DWORD SetFlags,
                                               UObject *InTemplate, FOutputDevice *Error, UObject *SubobjectRoot)
{
    UObject *Result = StaticAllocateObject(InClass, InOuter, InName, SetFlags, InTemplate, Error, 0, SubobjectRoot);
    if (Result)
        (*InClass->ClassConstructor)(Result);
    return Result;
}

class UMesh;
class AActor;

class UMeshInstance : public UObject
{
public:
    virtual void V1(); virtual void V2();
    virtual void Destroy(INT Mode);                     // +0x0c
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual AActor *GetActor();                         // +0x78
    virtual void SetActor(AActor *InActor);             // +0x7c
    virtual UMesh *GetMesh();                           // +0x80
    virtual void SetMesh(UMesh *InMesh);                // +0x84
    virtual void Release(INT Mode);                     // +0x88
    virtual DWORD GetInstanceFlags();                   // +0x8c
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x1d4 - 0x28];
    UMeshInstance *MeshInstance;        // 0x1d4
    BYTE Pad1d8[0x2e8 - 0x1d8];
    DWORD ActorBits0 : 15;              // 0x2e8
    DWORD bDeleteMe : 1;                // 0x2e8 bit 15 (neutral guess at the name)
};

extern UClass UMeshInstance_PrivateStaticClass;     // 0x10cbf1f0

class UMesh : public UObject
{
public:
    virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual UClass *MeshGetInstanceClass();             // +0x78

    BYTE Pad28[0x50 - 0x28];
    UMeshInstance *DefaultInstance;     // 0x50

    virtual UMeshInstance *MeshGetInstance(const AActor *InOwner);   // virtual in retail
};

// RVA 0xdf4e0
UMeshInstance *UMesh::MeshGetInstance(const AActor *InOwner)
{
    UMeshInstance **InstPtr;
    if (!InOwner) {
        if (DefaultInstance)
            return DefaultInstance;
        InstPtr = &DefaultInstance;
    } else if (InOwner->bDeleteMe) {
        if (DefaultInstance)
            return DefaultInstance;
        InstPtr = &DefaultInstance;
    } else {
        UMeshInstance *&Inst = ((AActor *)InOwner)->MeshInstance;
        if (Inst) {
            if (Inst->GetActor() == InOwner && Inst->GetMesh() == this)
                return Inst;
            if (!(Inst->GetInstanceFlags() & 1)) {
                if (Inst)
                    Inst->Destroy(1);
            } else
                Inst->Release(2);
        }
        InstPtr = &Inst;
    }
    UClass *InstanceClass = MeshGetInstanceClass();
    if (!InstanceClass)
        InstanceClass = &UMeshInstance_PrivateStaticClass;
    *InstPtr = (UMeshInstance *)StaticConstructObject(InstanceClass, GetOuter(), NAME_None, 0x84004,
                                                      InstanceClass->DefaultObject, GError, 0);
    (*InstPtr)->SetMesh(this);
    (*InstPtr)->SetActor((AActor *)InOwner);
    return *InstPtr;
}

// Old-style notify: a function name, converted into a UAnimNotify_Script.
class UAnimNotify_Script : public UObject
{
public:
    INT Pad28;
    FName NotifyName;                   // 0x2c
};
extern UClass UAnimNotify_Script_PrivateStaticClass;    // 0x10cc1220
extern UObject *GObjTransientPkg;                      // 0x10c925b4

struct FMeshAnimNotify
{
    FLOAT Time;
    FName Function;
    UObject *NotifyObject;
    friend FArchive &operator<<(FArchive &Ar, FMeshAnimNotify &N);
};

struct FMeshAnimSeq
{
    FName Name;                         // 0x00
    TArray<FName> Groups;               // 0x04
    INT StartFrame;                     // 0x10
    INT NumFrames;                      // 0x14
    FLOAT Rate;                         // 0x18
    TArray<FMeshAnimNotify> Notifys;    // 0x1c
    INT Bookmark;                       // 0x28 (neutral name)

    void UpdateOldNotifies(UObject *InOuter);
    friend FArchive &operator<<(FArchive &Ar, FMeshAnimSeq &A);
};

template <class T> inline T *ConstructObject(UClass *Class, UObject *Outer = (UObject *)-1, FName Name = NAME_None,
                                             DWORD SetFlags = 0, UObject *Template = 0)
{
    if (Outer == (UObject *)-1)
        Outer = GObjTransientPkg;
    return (T *)UObject::StaticConstructObject(Class, Outer, Name, SetFlags, Template, GError, 0);
}

// RVA 0xdf5e0
void FMeshAnimSeq::UpdateOldNotifies(UObject *InOuter)
{
    for (INT i = 0; i < Notifys.Num(); i++) {
        if (Notifys(i).Function != NAME_None) {
            UAnimNotify_Script *N = ConstructObject<UAnimNotify_Script>(&UAnimNotify_Script_PrivateStaticClass, InOuter, NAME_None, 4);
            N->NotifyName = Notifys(i).Function;
            Notifys(i).NotifyObject = N;
            Notifys(i).Function = NAME_None;
        }
    }
}

// RVA 0xdf670
FArchive &operator<<(FArchive &Ar, FMeshAnimSeq &A)
{
    if (Ar.Ver() >= 0x73)
        Ar << A.Bookmark;
    else
        A.Bookmark = 0;
    Ar << A.Name;
    Ar << A.Groups;
    Ar << A.StartFrame;
    Ar << A.NumFrames;
    Ar << A.Notifys;
    Ar << A.Rate;
    return Ar;
}

// ---- Stand-ins for callees of other units, not part of this unit's match ----
FArchive &operator<<(FArchive &Ar, FMeshAnimNotify &N)
{
    return Ar << N.Time << N.Function << N.NotifyObject;
}

// 0x1ea40 (archive in ESI, index in EDI in retail), from item 0116.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_df4e0(UMesh *M, const AActor *A)
{
    // Retail reaches MeshGetInstance through the vtable, so its address is taken.
    UMeshInstance *(UMesh::*Fn)(const AActor *) = &UMesh::MeshGetInstance;
    Escape(&Fn);
    Escape(&GError);
    Escape(M->UMesh::MeshGetInstance(A));
}
void Driver_df5e0(FMeshAnimSeq *S, UObject *O)
{
    Escape(&GError);
    Escape(&GObjTransientPkg);
    S->UpdateOldNotifies(O);
}
void Driver_df670(FArchive *Ar, FMeshAnimSeq *S)
{
    Escape(&(*Ar << *S));
}
