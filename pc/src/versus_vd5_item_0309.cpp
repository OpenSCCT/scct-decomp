// Work item w3 0309: Versus RVA 0x107960-0x107f3a. LTCG unit (custom conventions).
//   0x107960 operator<<(FArchive&, FUnnamedRecord_107960&)  (record in EAX, Ar on the stack)
//   0x107bd0 Serialize of the class the analyzer labels UModel@308b08 (slot 10)
//   0x107e10 UObject::PostLoad
//   0x107e30 Destroy of the class the analyzer labels UModel@308b08 (slot 9)
// Struct and class names marked Unnamed are neutral: the evidence gives only layouts.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FName
{
public:
    INT Index;
};

struct FCompactIndex
{
    INT Value;
};
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
    UBOOL IsTrans() { return ArIsTrans; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, QWORD &Q) { Ar.Serialize(&Q, 8); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                 // 0x44e0
    void Realloc(INT ElementSize);                       // 0x4600
    void Empty(INT ElementSize, INT Slack);              // 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);  // 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    __declspec(noinline) INT RemoveItem(const T &Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                Remove(Index--);
        return OriginalNum - ArrayNum;
    }
    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(A) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

// 16-byte vector serialized by 0x86060 (archive ESI, value EAX); see item 0314.
struct FUnnamedVec4_86060
{
    FLOAT X, Y, Z, W;
};
FArchive &operator<<(FArchive &Ar, FUnnamedVec4_86060 &V);

// Pointer records serialized by 0x92420 (Ar in EAX, array in EBX); see item 0335.
struct FRecordA
{
    BYTE Pad[0x18];
    UObject *ObjA;      // 0x18
    UObject *ObjB;      // 0x1c
    friend FArchive &operator<<(FArchive &Ar, FRecordA *R) { return Ar << R->ObjA << R->ObjB; }
};
struct FRecordB
{
    FRecordA *Record;   // 0x00
    UObject *Obj;       // 0x04
    friend FArchive &operator<<(FArchive &Ar, FRecordB *R) { return Ar << R->Record << R->Obj; }
};

// ---------------------------------------------------------------------------
// RVA 0x107960.
struct FUnnamedRecord_107960
{
    INT A, B, C, D;                  // 0x00
    FUnnamedVec4_86060 Vec;          // 0x10
    QWORD Bits;                      // 0x20
    INT Index28, Index2c;            // 0x28 (compact indices)
    INT Index30, Index34, Index38;   // 0x30
    INT Value3c;                     // 0x3c
    TArray<FRecordB *> Records;      // 0x40
    SWORD Word4c, Word4e;            // 0x4c
    SWORD Word50, Word52;            // 0x50
    SWORD Word54, Word56;            // 0x54 (compact indices)
    BYTE Byte58, Byte59, Byte5a;     // 0x58
    BYTE Flags5b;                    // 0x5b
    FUnnamedRecord_107960();         // 0x109e00
    ~FUnnamedRecord_107960();        // 0xa8a40
};

FArchive &operator<<(FArchive &Ar, FUnnamedRecord_107960 &R)
{
    Ar << R.A << R.B << R.C << R.D;
    Ar << R.Bits;
    Ar << R.Flags5b;
    Ar << AR_INDEX(R.Index28);
    Ar << AR_INDEX(R.Index2c);
    Ar << AR_INDEX(R.Index30) << AR_INDEX(R.Index34) << AR_INDEX(R.Index38);
    INT Tmp;
    Tmp = R.Word54; Ar << AR_INDEX(Tmp); R.Word54 = Tmp;
    Tmp = R.Word56; Ar << AR_INDEX(Tmp); R.Word56 = Tmp;
    if (Ar.Ver() >= 70) {
        FUnnamedVec4_86060 Dummy;
        Ar << R.Vec << Dummy;
    }
    Ar << R.Byte58 << R.Byte59 << R.Byte5a;
    Tmp = R.Word4c; Ar << Tmp; R.Word4c = Tmp;
    Tmp = R.Word4e; Ar << Tmp; R.Word4e = Tmp;
    if (Ar.Ver() < 92) {
        R.Value3c = -1;
        R.Word50 = -1;
        R.Word52 = -1;
    } else if (Ar.Ver() < 93) {
        INT Dummy = -1;
        Ar << Dummy;
        R.Value3c = -1;
        R.Word50 = -1;
        R.Word52 = -1;
    } else if (Ar.Ver() < 101) {
        INT Dummy1 = -1, Dummy2 = -1;
        Ar << Dummy1 << Dummy2;
        R.Value3c = -1;
        R.Word50 = -1;
        R.Word52 = -1;
    } else {
        Tmp = R.Word50; Ar << Tmp; R.Word50 = Tmp;
        Tmp = R.Word52; Ar << Tmp; R.Word52 = Tmp;
        Ar << R.Value3c;
        if (Ar.IsLoading() && Ar.Ver() < 108)
            R.Value3c = -1;
    }
    if (!Ar.IsSaving() && !Ar.IsLoading())
        Ar << R.Records;
    if (Ar.IsLoading())
        R.Flags5b &= 0x1f;
    return Ar;
}

// ---------------------------------------------------------------------------
// UObject: ObjectFlags at 0x1c (UE2 layout).
class UObject
{
public:
    virtual ~UObject();
    void *Index_; void *HashNext; void *StateFrame; void *_Linker; INT _LinkerIndex; UObject *Outer;
    DWORD ObjectFlags;
    void LoadLocalized();
    virtual void PostLoad();
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);
};

// RVA 0x107e10: UObject::PostLoad.
void UObject::PostLoad()
{
    ObjectFlags |= 0x20000000; // RF_DebugPostLoad
    if (ObjectFlags & 0x100)
        LoadLocalized();
}

// ---------------------------------------------------------------------------
// RVA 0x107e30 (vtable slot 9 of the class the analyzer labels UModel@308b08).
// Names below are neutral: the evidence does not identify the class.

// Reference-counted payload: count at +4, freed directly through GMalloc.
struct FSharedBlock_107e30
{
    void *Unknown0;
    INT RefCount;
    void Release()
    {
        if (--RefCount == 0)
            GMalloc->Free(this);
    }
};

// Element of the per-entry list: first field points at the shared block.
// Its implicit destructor is 0x8ffe0 (members at 0x20, 0x14, 0x08).
struct FMemberA_107e30 { INT X[3]; ~FMemberA_107e30(); };
struct FMemberB_107e30 { INT X[3]; ~FMemberB_107e30(); };
struct FMemberC_107e30 { INT X[3]; ~FMemberC_107e30(); };
class FListItem_107e30
{
public:
    FSharedBlock_107e30 *Shared;
    INT Unknown4;
    FMemberA_107e30 A;   // 0x08
    FMemberB_107e30 B;   // 0x14
    FMemberC_107e30 C;   // 0x20
    void operator delete(void *P) { GMalloc->Free(P); }
};

struct FOwner_107e30
{
    char Pad[0x4abc];
    TArray<TArray<FListItem_107e30 *> *> Pending;
};

struct FOwnerRef_107e30
{
    void *Unknown0;
    FOwner_107e30 *Owner;
};

struct FEntry_107e30
{
    char Pad[0x40];
    TArray<FListItem_107e30 *> Items;
    char Pad2[0x5c - 0x4c];
};

class UnnamedClass_107e30 : public UObject
{
public:
    char Pad[0x54 - 0x20];
    TArray<FEntry_107e30> Entries;           // 0x54
    char Pad2[0xe0 - 0x60];
    TArray<FOwnerRef_107e30> OwnersA;        // 0xe0
    TArray<FOwnerRef_107e30> OwnersB;        // 0xec
    void Destroy();
};

void UnnamedClass_107e30::Destroy()
{
    FOwner_107e30 *Owner = 0;
    if (OwnersA.Num())
        Owner = OwnersA(0).Owner;
    if (!Owner && OwnersB.Num())
        Owner = OwnersB(0).Owner;

    for (INT i = 0; i < Entries.Num(); i++)
    {
        FEntry_107e30 &Entry = Entries(i);
        if (Owner && Entry.Items.Num() > 0)
            Owner->Pending.RemoveItem(&Entry.Items);
        INT Num;
        while ((Num = Entry.Items.Num()) > 0)
        {
            Entry.Items(Num - 1)->Shared->Release();
            delete Entry.Items(Num - 1);
            Entry.Items.Remove(Num - 1);
        }
    }
    UObject::Destroy();
}

// ---------------------------------------------------------------------------
// RVA 0x107bd0: UModel::Serialize (vtable slot 10 of UModel@308b08). The
// UPrimitive part (bounding box and sphere) is inlined; the parent call is
// UObject::Serialize at 0x115f50. Member names follow UE2's UModel where the
// serialization order identifies them (Vectors, Points, Nodes, Surfs, Verts,
// NumSharedSides, Zones, Polys, RootOutside, Linked); the rest are neutral.

class FVector
{
public:
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

// 24-byte box serialized by 0x860d0 (archive ESI, value EDI); see item 0314.
struct FUnnamedPair_860d0
{
    FVector A;
    FVector B;
    FUnnamedPair_860d0() { A.X = 1.f; B.X = 0.f; }
};
FArchive &operator<<(FArchive &Ar, FUnnamedPair_860d0 &P);

template <class T> class TTransArray : public TArray<T>
{
public:
    UObject *Owner;
    friend FArchive &operator<<(FArchive &Ar, TTransArray &A)
    {
        if (!Ar.IsTrans())
            Ar << (TArray<T> &)A;
        return Ar;
    }
};

// Element types of the other arrays (serializers in items w3 0314 and 0315).
struct UnnamedWord_109d00
{
    SWORD Value;
    friend FArchive &operator<<(FArchive &Ar, UnnamedWord_109d00 &W)
    {
        INT V = W.Value;
        Ar << AR_INDEX(V);
        W.Value = V;
        V = 0;
        Ar << AR_INDEX(V);
        return Ar;
    }
};
struct UnnamedElement_2c
{
    DWORD Data[4];
    UObject *Object;            // 0x10
    DWORD Flags;                // 0x14
    BYTE Pad18[8];
    void *Shape;                // 0x20
    BYTE Pad24[8];
    ~UnnamedElement_2c() { if (Shape) GMalloc->Free(Shape); }
    friend FArchive &operator<<(FArchive &Ar, UnnamedElement_2c &E);
};
struct FUnnamedBulk_c3280 { INT Value; };
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedBulk_c3280> &A);   // 0xc3280
FArchive &operator<<(FArchive &Ar, TArray<FVector> &A);              // 0x86bb0
FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A);            // 0xf85a0
// 4-byte element: serializer 0x10a1b0 (archive in EAX, element in EBX), item w3 0314.
struct UnnamedElement_4
{
    unsigned short A;
    short B;
};
FArchive &operator<<(FArchive &Ar, UnnamedElement_4 &E);
struct UnnamedElement_38
{
    BYTE Pad[0x38];
    UnnamedElement_38();
    ~UnnamedElement_38();
};
FArchive &operator<<(FArchive &Ar, UnnamedElement_38 &E);
// 0x70-byte element and its sub-records (item w3 0314).
struct UnnamedRecord_c : public FArray {};      // serializer RVA 0xc3280
FArchive &operator<<(FArchive &Ar, UnnamedRecord_c &A);
struct UnnamedVec_18
{
    BYTE Pad[0x18];
    UnnamedVec_18();            // RVA 0x10a6b0
    ~UnnamedVec_18();           // RVA 0xa8df0
};
FArchive &operator<<(FArchive &Ar, UnnamedVec_18 &V);   // RVA 0xe5b80
BYTE CeilLogTwo_12050(INT V);                          // RVA 0x12050
class UnnamedRecord_50
{
public:
    UnnamedRecord_50();
    ~UnnamedRecord_50();
    virtual void V00();
    UnnamedVec_18 V[2];         // +0x04, +0x1c
    BYTE B34;                   // +0x34
    INT I38;                    // +0x38
    INT I3c;                    // +0x3c
    INT I40, I44;
    INT I48;                    // +0x48
    BYTE B4c, B4d;              // +0x4c
};
FArchive &operator<<(FArchive &Ar, UnnamedRecord_50 &R);
class UnnamedElement_70
{
public:
    virtual void V00();
    FName Name;                 // +0x04
    UnnamedRecord_c RecordA;    // +0x08
    UnnamedRecord_50 RecordB;   // +0x14
    QWORD Value64;              // +0x64
    INT Value6c;                // +0x6c
    UnnamedElement_70();
    ~UnnamedElement_70();

    friend FArchive &operator<<(FArchive &Ar, UnnamedElement_70 &E)
    {
        Ar << E.Name << E.RecordA << E.Value64 << E.Value6c;
        if (Ar.Ver() >= 0x74)
            Ar << E.RecordB;
        return Ar;
    }
};
struct UnnamedElement_a4
{
    BYTE Pad[0xa4];
    UnnamedElement_a4();
    ~UnnamedElement_a4();
};
FArchive &operator<<(FArchive &Ar, UnnamedElement_a4 &E);

struct FZoneSet { QWORD Bits; };
struct FZoneProperties
{
    UObject *ZoneActor;         // 0x00
    FLOAT LastRenderTime;       // 0x04
    QWORD Connectivity;         // 0x08
};
class FZoneArray : public TArray<FZoneProperties>
{
public:
    INT AddExact(INT Count);    // 0x207ec0 (array in ESI, count in EAX)
};

struct FUnnamedGlobal_c946cc
{
    BYTE Pad[0x80];
    INT Mode;                   // 0x80
};
extern FUnnamedGlobal_c946cc *GUnnamed_c946cc;
extern INT GUnnamed_c47f60;
extern INT GUnnamed_c47f64;

class UPrimitive : public UObject
{
public:
    FName Name_;                            // 0x20
    void *Class_;                           // 0x24
    FUnnamedPair_860d0 BoundingBox;         // 0x28
    FUnnamedVec4_86060 BoundingSphere;      // 0x40
    void Serialize(FArchive &Ar)
    {
        UObject::Serialize(Ar);
        Ar << BoundingBox << BoundingSphere;
    }
};

class UModel : public UPrimitive
{
public:
    UObject *Polys;                                     // 0x50
    TTransArray<FUnnamedRecord_107960> Nodes;           // 0x54
    TTransArray<UnnamedWord_109d00> Verts;              // 0x64
    TTransArray<FVector> Vectors;                       // 0x74
    TTransArray<FVector> Points;                        // 0x84
    TTransArray<UnnamedElement_2c> Surfs;               // 0x94
    TArray<FUnnamedPair_860d0> ArrayA4;                 // 0xa4
    TArray<FUnnamedBulk_c3280> ArrayB0;                 // 0xb0
    TArray<UnnamedElement_4> ArrayBC;                   // 0xbc
    TArray<UObject *> ArrayC8;                          // 0xc8
    TArray<UnnamedElement_38> ArrayD4;                  // 0xd4
    TArray<UnnamedElement_70> ArrayE0;                  // 0xe0
    TArray<UnnamedElement_a4> ArrayEC;                  // 0xec
    BYTE PadF8[0x104 - 0xf8];
    INT RootOutside;                                    // 0x104
    INT Linked;                                         // 0x108
    INT Pad10c;
    INT NumSharedSides;                                 // 0x110
    FZoneArray Zones;                                   // 0x114
    void Serialize(FArchive &Ar);
};

void UModel::Serialize(FArchive &Ar)
{
    UPrimitive::Serialize(Ar);
    INT NumZones = Zones.Num();
    Ar << Vectors << Points << Nodes << Surfs << Verts;
    Ar << NumSharedSides << NumZones;
    if (Ar.IsLoading() && NumZones)
        Zones.AddExact(NumZones);
    for (INT i = 0; i < NumZones; i++) {
        FZoneProperties &Zone = Zones(i);
        Ar << Zone.ZoneActor << Zone.Connectivity;
        if (Ar.Ver() <= 155) {
            QWORD Visibility;
            Ar << Visibility;
        }
        Ar << Zone.LastRenderTime;
    }
    Ar << Polys;
    if (Polys && !Ar.IsTrans())
        Ar.Preload(Polys);
    Ar << ArrayA4 << ArrayB0 << ArrayBC << ArrayC8;
    Ar << RootOutside << Linked;
    Ar << ArrayD4;
    if (Ar.Ver() < 161 || (GUnnamed_c946cc->Mode != 1 && GUnnamed_c946cc->Mode != 2 && GUnnamed_c946cc->Mode != 3))
        Ar << ArrayEC;
    Ar << ArrayE0;
    GUnnamed_c47f60 = 1;
    GUnnamed_c47f64 = 1;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
//
// Serializers from other objects, defined here only so the link gives them their
// retail conventions (copied from items 0314 and 0335).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
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
    return Ar;
}
FArchive &operator<<(FArchive &Ar, FUnnamedVec4_86060 &V)
{
    if (Ar.Ver() <= 61)
        return Ar << V.X << V.Y << V.Z;
    else
        return Ar << V.X << V.Y << V.Z << V.W;
}

FArchive &operator<<(FArchive &Ar, FUnnamedPair_860d0 &P)
{
    BYTE Flag = (P.A.X - P.B.X != 1.f);
    Ar << P.A << P.B << Flag;
    if (Ar.IsLoading() && !Flag) {
        P.B.X = 0.f;
        P.A.X = 1.f;
    }
    return Ar;
}

#pragma pack(pop)

void Escape(void *);
void ExtA(void *, int);
void Touch(void *);
extern const TCHAR TEXT_operator_TArray[];
extern const TCHAR TEXT_FArray[];

// 0x86bb0 (item 0318).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FVector> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayMax == 0)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayMax * sizeof(FVector), TEXT_operator_TArray);
        } else if (A.ArrayMax) {
            A.Realloc(sizeof(FVector));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FVector));
    return Ar;
}
// 0xc3280 (item w3 0137).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FUnnamedBulk_c3280> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        A.Realloc(sizeof(FUnnamedBulk_c3280));
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FUnnamedBulk_c3280));
    return Ar;
}
// 0xf85a0 (published item vd2 0112).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(UObject *), A.ArrayMax * sizeof(UObject *));
    if (Ar.ArIsLoading) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.FArray::Empty(sizeof(UObject *), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(UObject *)));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}
// 0x107560 (item w3 0308 / 0315 stand-in).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_2c &E)
{
    Ar << E.Object;
    Ar.Serialize(&E.Flags, 4);
    INT V = E.Pad18[0];
    Ar << AR_INDEX(V);
    E.Pad18[0] = V;
    return Ar;
}
// Element constructors, destructors and serializers (stand-ins, items w3 0314/0315).
__declspec(noinline) FUnnamedRecord_107960::FUnnamedRecord_107960() {}
__declspec(noinline) FUnnamedRecord_107960::~FUnnamedRecord_107960() {}
template <> __declspec(noinline) void TArray<FUnnamedRecord_107960>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedRecord_107960();
    FArray::Empty(sizeof(FUnnamedRecord_107960), Slack);
}
template <> __declspec(noinline) void TArray<UnnamedElement_2c>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_2c();
    FArray::Empty(sizeof(UnnamedElement_2c), Slack);
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_4 &E)
{
    INT V = E.A;
    Ar << AR_INDEX(V);
    E.A = (unsigned short)V;
    V = E.B;
    Ar << AR_INDEX(V);
    E.B = (short)V;
    Ar << AR_INDEX(V);
    if (Ar.Ver() <= 0x9a) {
        QWORD Dropped;
        Ar << Dropped;
    }
    return Ar;
}
__declspec(noinline) UnnamedElement_38::UnnamedElement_38() { Touch(Pad + 8); Touch(this); }
__declspec(noinline) UnnamedElement_38::~UnnamedElement_38() { Touch(this); Touch(Pad + 4); }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_38 &E) { Touch(&E); Touch(&E); Touch(&Ar); return Ar; }
template <> __declspec(noinline) void TArray<UnnamedElement_38>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_38();
    FArray::Empty(sizeof(UnnamedElement_38), Slack);
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_c &A)
{
    Ar.CountBytes(A.ArrayNum * 4, A.ArrayMax * 4);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) { A.ArrayMax = A.ArrayNum; Touch(A.Data); }
    Ar.Serialize(A.Data, A.ArrayNum * 4);
    return Ar;
}
__declspec(noinline) UnnamedRecord_50::UnnamedRecord_50() {}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_50 &R)
{
    Ar << R.V[0] << R.V[1];
    Ar.Serialize(&R.B34, 1);
    Ar << R.I38 << R.I3c << R.I48;
    R.B4c = CeilLogTwo_12050(R.I38);
    R.B4d = CeilLogTwo_12050(R.I3c);
    return Ar;
}
__declspec(noinline) UnnamedElement_70::UnnamedElement_70() {}
__declspec(noinline) UnnamedElement_70::~UnnamedElement_70() { Touch(&Name); Touch(&Name); Touch(this); }
template <> __declspec(noinline) void TArray<UnnamedElement_70>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_70();
    FArray::Empty(sizeof(UnnamedElement_70), Slack);
}
__declspec(noinline) UnnamedElement_a4::UnnamedElement_a4() { Touch(Pad + 8); Touch(this); }
__declspec(noinline) UnnamedElement_a4::~UnnamedElement_a4() { Touch(this); Touch(Pad + 4); }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedElement_a4 &E) { Touch(&E); Touch(&Ar); Touch(&E); Touch(&Ar); return Ar; }
template <> __declspec(noinline) void TArray<UnnamedElement_a4>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_a4();
    FArray::Empty(sizeof(UnnamedElement_a4), Slack);
}
// 0x207ec0 (array in ESI, count in EAX).
__declspec(noinline) INT FZoneArray::AddExact(INT Count)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    if (Data == 0)
        Data = ArrayNum * (INT)sizeof(FZoneProperties) > 0 ? GMalloc->Malloc(ArrayNum * sizeof(FZoneProperties), TEXT_operator_TArray) : 0;
    else
        Data = GMalloc->Realloc(Data, ArrayNum * sizeof(FZoneProperties), TEXT_FArray);
    return Index;
}
void Driver_107bd0(void *Mem) { Escape(&GMalloc); Escape(&GUnnamed_c946cc); Escape(new(Mem) UModel); }
// Stand-in body so the linker gives LoadLocalized its retail register convention (this in ESI).
__declspec(noinline) void UObject::LoadLocalized()
{
    ExtA(this, 1); ExtA(Outer, 2); ExtA(this, 3); ExtA(Outer, 4); ExtA(this, 5); ExtA(Outer, 6);
    ExtA(this, 7); ExtA(Outer, 8); ExtA(this, 9); ExtA(Outer, 10);
}
void Driver_107960(FArchive *Ar, FUnnamedRecord_107960 *R, INT N)
{
    for (INT i = 0; i < N; i++)
        *Ar << R[i];
}
void Driver_107e10(void *Mem) { Escape(new(Mem) UObject); }
void Driver_107e30(void *Mem) { Escape(&GMalloc); Escape(new(Mem) UnnamedClass_107e30); }
