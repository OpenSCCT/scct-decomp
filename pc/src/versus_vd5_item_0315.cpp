// Work item w3 0315: Versus RVA 0x109b70-0x109e3d (LTCG object, VC7.0 /GL).
// Three instantiations of UE2's TArray<T> archive serializer
// (friend operator<<(FArchive&, TArray<T>&) in UnTemplate.h), all reached from
// one owner serializer at 0x107c00, plus a constructor:
//  0x109b70 operator<<(FArchive&, TArray<UnnamedElement_5c>&): array in EBX,
//           archive on the stack.
//  0x109c30 operator<<(FArchive&, TArray<UnnamedElement_2c>&): both on the stack.
//  0x109d00 operator<<(FArchive&, TArray<UnnamedWord_109d00>&): archive in EAX,
//           array in EBX.
//  0x109e10 UnnamedClass_109e10 constructor (vtable 0x10c03b80), this in EAX.
// Element and class names are neutral: nothing in the binary names them.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class UObject;
class FName { public: INT Index; };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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
    virtual FArchive &operator<<(FName &N);                 // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsError() { return ArIsError; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // 0x04
    INT ArNetVer;       // 0x08
    INT ArLicenseeVer;  // 0x0c
    UBOOL ArIsLoading;  // 0x10
    UBOOL ArIsSaving;   // 0x14
    UBOOL ArIsError;    // 0x18 (tested by the owner serializer after each array)
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);        // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);     // RVA 0x4550
    void Realloc(INT ElementSize);              // RVA 0x4600
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (sizeof(T) == 1) {
            // Serialize simple bytes which require no construction or destruction.
            Ar << AR_INDEX(A.ArrayNum);
            if (Ar.IsLoading()) {
                A.ArrayMax = A.ArrayNum;
                A.Realloc(sizeof(T));
            }
            Ar.Serialize(&A(0), A.Num());
        } else if (Ar.IsLoading()) {
            // Load array.
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(A) T;
        } else {
            // Save array.
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

// 0x5c-byte element (the record of item w3 0309): constructor 0x109e00
// (this in EAX) clears the array at +0x40; destructor 0xa8a40 (this in EAX);
// serializer 0x107960 (element in EAX, archive on the stack).
struct FUnnamedVec4_86060 { FLOAT X, Y, Z, W; };
FArchive &operator<<(FArchive &Ar, FUnnamedVec4_86060 &V);   // 0x86060, item 0314
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
inline FArchive &operator<<(FArchive &Ar, QWORD &Q) { Ar.Serialize(&Q, 8); return Ar; }
struct UnnamedElement_5c
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
    UnnamedElement_5c();
    ~UnnamedElement_5c();
    friend FArchive &operator<<(FArchive &Ar, UnnamedElement_5c &E);
};

// 0x2c-byte element (the record of item w3 0308): empty constructor; its
// destructor frees the shape at +0x20 (inlined into Empty, 0x109770);
// serializer 0x107560 (archive in EAX, element in EBX).
struct FUnnamedShape_1077c0;
FArchive &operator<<(FArchive &Ar, FUnnamedShape_1077c0 *S);   // 0x107760, item w3 0308
struct UnnamedElement_2c
{
    DWORD   Data[4];                // 0x00
    UObject *Object;                // 0x10
    DWORD   Flags;                  // 0x14
    unsigned short Index[4];        // 0x18
    FUnnamedShape_1077c0 *Shape;    // 0x20
    FLOAT   SizeA;                  // 0x24
    FLOAT   SizeB;                  // 0x28
    UnnamedElement_2c() {}
    ~UnnamedElement_2c() { if (Shape) GMalloc->Free(Shape); }
    friend FArchive &operator<<(FArchive &Ar, UnnamedElement_2c &E);
};

// 2-byte element: a signed word stored as a compact index, followed by a
// compact index that is always written as zero (a dropped field).
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

// RVA 0x109b70, 0x109c30, 0x109d00: the TArray<T> serializer above,
// instantiated by the owner serializer for the three element types.

// RVA 0x109e10: 0xa4-byte element of another serialized array (stride 0xa4
// at 0x109af0); two arrays at 0x8c and 0x98 are its only initialised members.
class UnnamedClass_109e10
{
public:
    virtual void Slot0();
    BYTE Pad4[0x88];
    TArray<INT> ListA;          // 0x8c
    TArray<INT> ListB;          // 0x98
    UnnamedClass_109e10();
};

__declspec(noinline) UnnamedClass_109e10::UnnamedClass_109e10() {}

// ---- Stand-ins for callees of other units, defined so the link gives them
// their retail register conventions. Not part of this unit's match. ----

// 0x109e00 (this in EAX).
__declspec(noinline) UnnamedElement_5c::UnnamedElement_5c() {}
// 0xa8a40 (this in EAX): destroys Records (TArray dtor 0x17bf30).
void Touch(void *);
__declspec(noinline) UnnamedElement_5c::~UnnamedElement_5c() {}
// 0x109730 (this in ESI).
template <> __declspec(noinline) void TArray<UnnamedElement_5c>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_5c();
    FArray::Empty(sizeof(UnnamedElement_5c), Slack);
}
// 0x109770 (this in ESI).
template <> __declspec(noinline) void TArray<UnnamedElement_2c>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElement_2c();
    FArray::Empty(sizeof(UnnamedElement_2c), Slack);
}
// 0x107960 (element in EAX, archive on the stack), from item w3 0309.
FArchive &operator<<(FArchive &Ar, UnnamedElement_5c &R)
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
// 0x107560 (archive in EAX, element in EBX), from item w3 0308.
struct FPlatformInfo_46cc
{
    BYTE Pad[0x80];
    INT  Platform;      // 0x80
};
extern FPlatformInfo_46cc *GPlatformInfo;
inline UBOOL IsConsolePlatform()
{
    return GPlatformInfo->Platform == 1 || GPlatformInfo->Platform == 2 || GPlatformInfo->Platform == 3;
}
extern const TCHAR Tag_10c109d8[];
inline FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
inline FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
FArchive &operator<<(FArchive &Ar, UnnamedElement_2c &R)
{
    Ar << R.Object;
    Ar << R.Flags;
    for (INT i = 0; i < 4; i++)
    {
        INT Value = R.Index[i];
        Ar << AR_INDEX(Value);
        R.Index[i] = Value;
    }
    if (Ar.Ver() < 0x65)
    {
        INT Dropped = -1;
        Ar << AR_INDEX(Dropped);
    }
    INT Dropped2 = -1;
    if (Ar.Ver() < 0xa5)
        Ar << AR_INDEX(Dropped2);
    if (Ar.Ver() < 0x4e)
    {
        INT DroppedA = 0, DroppedB = 0;
        Ar.Serialize(&DroppedA, 2);
        Ar.Serialize(&DroppedB, 2);
    }
    UObject *DroppedObject = 0;
    if (Ar.Ver() < 0xa5)
        Ar << DroppedObject;
    if (Ar.Ver() > 0x56)
        Ar << R.Data[0] << R.Data[1] << R.Data[2] << R.Data[3];
    if (Ar.Ver() >= 0x6a)
    {
        Ar << R.SizeA;
        if (Ar.Ver() >= 0xa8)
            Ar << R.SizeB;
        else
            R.SizeB = R.SizeA;
    }
    else if (Ar.IsLoading())
    {
        R.SizeA = R.SizeB = 32.f;
    }
    if (IsConsolePlatform() && !(R.Flags & 0xc000000))
    {
        if (Ar.IsLoading())
            R.Shape = 0;
    }
    else if (Ar.IsLoading())
    {
        R.Shape = (FUnnamedShape_1077c0 *)GMalloc->Malloc(0xe4, Tag_10c109d8);
        if (Ar.Ver() >= 0xa5)
            Ar << R.Shape;
    }
    else if (Ar.IsSaving())
    {
        Ar << R.Shape;
    }
    return Ar;
}
// 0x1ea40 (archive in ESI, index in EDI), item 0116.
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

#pragma pack(pop)

// Scaffolding for the link, not part of the unit: mirrors the owner
// serializer at 0x107c00 and the 0xa4-element loop at 0x109af0.
void Escape(void *);
struct FUnnamedOwner_107c00
{
    BYTE Pad[0x54];
    TArray<UnnamedElement_5c> A;        // 0x54
    BYTE Pad60[4];
    TArray<UnnamedWord_109d00> C;       // 0x64
    BYTE Pad70[0x94 - 0x70];
    TArray<UnnamedElement_2c> B;        // 0x94
};
void Driver_107c00(FArchive &Ar, FUnnamedOwner_107c00 *O)
{
    Escape(&GMalloc);
    Escape(&GPlatformInfo);
    Ar << O->A;
    if (Ar.IsError()) return;
    Ar << O->B;
    if (Ar.IsError()) return;
    Ar << O->C;
}
void Driver_109e10(TArray<UnnamedClass_109e10> *A, INT N)
{
    for (INT i = 0; i < N; i++)
        Escape(new(&(*A)(A->Add(1, sizeof(UnnamedClass_109e10)))) UnnamedClass_109e10);
}
