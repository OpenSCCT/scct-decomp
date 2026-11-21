// Work item w3_0168 (RVA 0xcce40-0xcd422). Built with /GL and linked with
// /LTCG, so the functions take their arguments in registers chosen by the
// linker. Class and struct names that are not recovered are neutral names
// after their RVAs.
typedef unsigned short TCHAR;
typedef int INT;
typedef short SWORD;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);        // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;          // 0x10c73bf0

class FArrayBase
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize);   // 0x119c0
    ~FArrayBase()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

// Inner array member of 4-byte elements; destructor at RVA 0x17bf30 (not
// part of this item; defined for its register convention).
class UnnamedArray_17bf30 : public FArrayBase
{
public:
    __declspec(noinline) ~UnnamedArray_17bf30() { Remove(0, ArrayNum, 4); }
};

// 28-byte element with an out-of-line destructor (RVA 0xa4780).
class UnnamedElement_a4780
{
public:
    INT A;                        // 0x00
    UnnamedArray_17bf30 List;      // 0x04
    INT B, C, D;                  // 0x10
    __declspec(noinline) ~UnnamedElement_a4780();
};

// RVA 0xa4780 (not part of this item; defined for its register convention).
UnnamedElement_a4780::~UnnamedElement_a4780()
{
}

// RVA 0xcce40: TArray<UnnamedElement_a4780>::Empty.
template void TArray<UnnamedElement_a4780>::Empty(INT);

class UObject;
class FName;
class AActor;

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
    // Slot order past +0x1c inferred from use; names follow UE2.
    virtual void AttachLazyLoader(void *LazyArray);         // +0x20
    virtual void DetachLazyLoader(void *LazyArray);         // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Flush();                                   // +0x34
    virtual UBOOL Close();                                  // +0x38
    virtual void Seek(INT InPos);                           // +0x3c

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, sizeof(I));
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, SWORD &W)
    {
        Ar.Serialize(&W, sizeof(W));
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F)
    {
        Ar.Serialize(&F, sizeof(F));
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;              // 0x04
    INT ArNetVer;           // 0x08
    INT ArLicenseeVer;      // 0x0c
    UBOOL ArIsLoading;      // 0x10
    UBOOL ArIsSaving;       // 0x14
    UBOOL ArIsTrans;        // 0x18
};

// RVA 0x1ea40 (not part of this item; defined for its register convention).
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

class FArrayAdd : public FArray
{
public:
    INT Add(INT Count, INT ElementSize);                    // 0x44e0
};

template <class T> class TAddArray : public FArrayAdd
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

template <class T> inline void *operator new(unsigned int Size, TAddArray<T> &Array)
{
    INT Index = Array.Add(1, sizeof(T));
    return &Array(Index);
}

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

// 24-byte record of two vectors serialized by RVA 0x860d0.
struct UnnamedRecord_860d0
{
    FVector A;      // 0x00
    FVector B;      // 0x0c
    UnnamedRecord_860d0() { A.X = 1.f; B.X = 0.f; }
    friend FArchive &operator<<(FArchive &Ar, UnnamedRecord_860d0 &R);
};

// RVA 0x860d0 (not part of this item; defined for its register convention).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_860d0 &R)
{
    BYTE Flag = (R.A.X - R.B.X) != 1.f;
    Ar << R.A << R.B << Flag;
    if (Ar.IsLoading() && !Flag) {
        R.B.X = 0.f;
        R.A.X = 1.f;
    }
    return Ar;
}

// Records read from old packages are kept here (retail 0x10cbfd4c).
extern TAddArray<UnnamedRecord_860d0> GUnnamedRecords_cbfd4c;

struct UnnamedStruct_ccea0
{
    SWORD A, B, C, D;   // 0x00, compact indices
    INT E;              // 0x08
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_ccea0 &S);
};

// RVA 0xccea0.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_ccea0 &S)
{
    INT Temp;
    Temp = S.A; Ar << AR_INDEX(Temp); S.A = (SWORD)Temp;
    Temp = S.B; Ar << AR_INDEX(Temp); S.B = (SWORD)Temp;
    Temp = S.C; Ar << AR_INDEX(Temp); S.C = (SWORD)Temp;
    Temp = S.D; Ar << AR_INDEX(Temp); S.D = (SWORD)Temp;
    if (Ar.Ver() < 0x9d || Ar.Ver() == 0x9e)
        return Ar << *new(GUnnamedRecords_cbfd4c) UnnamedRecord_860d0;
    return Ar << S.E;
}

struct FPlane
{
    FLOAT X, Y, Z, W;
    friend FArchive &operator<<(FArchive &Ar, FPlane &P)
    {
        return Ar << P.X << P.Y << P.Z << P.W;
    }
};

struct UnnamedStruct_ccf80
{
    FPlane Plane;           // 0x00
    SWORD A, B, C, D;       // 0x10, compact indices
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_ccf80 &S);
};

// RVA 0xccf80.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_ccf80 &S)
{
    Ar << S.Plane;
    if (Ar.Ver() < 0x99) {
        // Older packages stored three more planes that are no longer used.
        FPlane Dummy;
        Ar << Dummy << Dummy << Dummy;
    }
    INT Temp;
    Temp = S.A; Ar << AR_INDEX(Temp); S.A = (SWORD)Temp;
    Temp = S.B; Ar << AR_INDEX(Temp); S.B = (SWORD)Temp;
    Temp = S.C; Ar << AR_INDEX(Temp); S.C = (SWORD)Temp;
    Temp = S.D; Ar << AR_INDEX(Temp); S.D = (SWORD)Temp;
    return Ar;
}

// Byte array serializer at RVA 0xa8ea0 (not part of this item; body
// approximated, defined so the linker gives it its register convention).
class FByteArray : public FArray
{
public:
    friend FArchive &operator<<(FArchive &Ar, FByteArray &A);
};

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FByteArray &A)
{
    Ar.CountBytes(A.ArrayNum, A.ArrayMax);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data && A.ArrayNum)
            A.Data = GMalloc->Malloc(A.ArrayNum, 0);
    }
    Ar.Serialize(A.Data, A.ArrayNum);
    return Ar;
}

// Global object read here (retail 0x10c946cc); type not recovered.
struct FUnnamedSettings_90b00
{
    char Pad0[0x80];
    INT Field80;                    // 0x80
};
extern FUnnamedSettings_90b00 *GUnnamedSettings_90b00;

inline UBOOL UnnamedSettingsActive()
{
    INT Mode = GUnnamedSettings_90b00->Field80;
    return Mode == 1 || Mode == 2 || Mode == 3;
}

class UObject
{
public:
    virtual ~UObject();
};

class AActor : public UObject
{
public:
    char Pad4[0x174 - 4];
    FLOAT Field174;                 // 0x174
    FLOAT Field178;                 // 0x178
    char Pad17c[0x2d2 - 0x17c];
    BYTE Field2d2;                  // 0x2d2
    char Pad2d3[0x2e8 - 0x2d3];
    DWORD Flags2e8;                 // 0x2e8
    DWORD Flags2ec;                 // 0x2ec
};

struct UnnamedStruct_cd0f0
{
    AActor *Actor;          // 0x00
    FByteArray Bytes;       // 0x04
    INT Value;              // 0x10
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_cd0f0 &S);
};

// RVA 0xcd0f0.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_cd0f0 &S)
{
    AActor *Saved = S.Actor;
    if (Ar.IsSaving() && UnnamedSettingsActive() && Saved
        && !(Saved->Flags2ec & 0x800000) && !(Saved->Flags2e8 & 0x20000)
        && Saved->Field2d2 != 0x16
        && (Saved->Field174 == 0.f || Saved->Field178 == 0.f))
        S.Actor = 0;
    Ar << *(UObject **)&S.Actor << S.Bytes << S.Value;
    if (Ar.IsSaving() && UnnamedSettingsActive())
        S.Actor = Saved;
    return Ar;
}

// 260-byte record serialized by RVA 0xcb070 (not part of this item; body
// stands in, defined so the linker gives it its register convention).
struct UnnamedRecord_cb070
{
    INT Values[65];
    friend FArchive &operator<<(FArchive &Ar, UnnamedRecord_cb070 &R);
};

__declspec(noinline) FArchive &operator<<(FArchive &Ar, UnnamedRecord_cb070 &R)
{
    for (INT i = 0; i < 65; i++)
        Ar << R.Values[i];
    return Ar;
}

class FRecordArray_cd440 : public TAddArray<UnnamedRecord_cb070>
{
public:
    friend FArchive &operator<<(FArchive &Ar, FRecordArray_cd440 &A);
};

// RVA 0xcd440 (not part of this item; TArray serializer, defined for its
// register convention).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FRecordArray_cd440 &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(UnnamedRecord_cb070), A.ArrayMax * sizeof(UnnamedRecord_cb070));
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(UnnamedRecord_cb070), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) UnnamedRecord_cb070;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Records written to a seek position kept by the owner; a positive offset
// means the records are still to be loaded. Name not recovered.
class UnnamedLazyRecords_cd3e0
{
public:
    void *Unknown0;                 // 0x00
    FArchive *SavedAr;              // 0x04
    INT SavedPos;                   // 0x08
    FRecordArray_cd440 Records;     // 0x0c
    __declspec(noinline) void Load();
};

// RVA 0xcd3e0.
void UnnamedLazyRecords_cd3e0::Load()
{
    if (SavedPos > 0) {
        INT PosSave = SavedAr->Tell();
        SavedAr->Seek(SavedPos);
        *SavedAr << Records;
        SavedPos = -SavedPos;
        SavedAr->Seek(PosSave);
    }
}

typedef unsigned __int64 QWORD;
typedef unsigned short _WORD;

// Render resources carry a cache id made from a running counter and a type
// byte (retail counter at 0x10c96930).
extern QWORD GCacheIDCounter;
inline QWORD MakeCacheID(BYTE Type)
{
    return (GCacheIDCounter++ << 8) + Type;
}

#pragma pack(push, 4)

// Array of 24-byte vertices. Destructor at RVA 0x1edf20 and serializer at
// RVA 0xcd820 (not part of this item; bodies stand in, defined so the linker
// gives them their register conventions).
struct FUnnamedVertex_cda60
{
    FLOAT V[6];
};
class FVertexArray_cda60 : public FArrayBase
{
public:
    __declspec(noinline) ~FVertexArray_cda60() { Remove(0, ArrayNum, sizeof(FUnnamedVertex_cda60)); }
    friend FArchive &operator<<(FArchive &Ar, FVertexArray_cda60 &A);
};
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FVertexArray_cda60 &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FUnnamedVertex_cda60), A.ArrayMax * sizeof(FUnnamedVertex_cda60));
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data && A.ArrayNum)
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(FUnnamedVertex_cda60), 0);
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FUnnamedVertex_cda60));
    return Ar;
}

// Array of 16-bit indices. The destructor (RVA 0xc4e0) lives outside the
// LTCG set; the serializer is at RVA 0x99710 (body stands in).
class FIndexArray : public FArray
{
public:
    ~FIndexArray();
    friend FArchive &operator<<(FArchive &Ar, FIndexArray &A);
};
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FIndexArray &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(_WORD), A.ArrayMax * sizeof(_WORD));
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data && A.ArrayNum)
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(_WORD), 0);
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(_WORD));
    return Ar;
}

// Vertex stream resource; constructor at RVA 0xcda60 (not part of this item).
class FUnnamedVertexStream_cda60
{
public:
    FVertexArray_cda60 Vertices;    // 0x04
    QWORD CacheId;                  // 0x10
    INT Revision;                   // 0x18
    __declspec(noinline) FUnnamedVertexStream_cda60()
    {
        Vertices.Data = 0; Vertices.ArrayNum = 0; Vertices.ArrayMax = 0;
        CacheId = MakeCacheID(0xe1);
        Revision = 0;
    }
    virtual void Unused0();
    friend FArchive &operator<<(FArchive &Ar, FUnnamedVertexStream_cda60 &S)
    {
        return Ar << S.Vertices << S.Revision;
    }
};

// Index buffer resource; constructor at RVA 0x1126e0 (not part of this item).
class FRawIndexBuffer
{
public:
    FIndexArray Indices;            // 0x04
    QWORD CacheId;                  // 0x10
    INT Revision;                   // 0x18
    __declspec(noinline) FRawIndexBuffer()
    {
        Indices.Data = 0; Indices.ArrayNum = 0; Indices.ArrayMax = 0;
        CacheId = MakeCacheID(0xe2);
        Revision = 0;
    }
    virtual void Unused0();
    friend FArchive &operator<<(FArchive &Ar, FRawIndexBuffer &I)
    {
        return Ar << I.Indices << I.Revision;
    }
};

#pragma pack(pop)

// Array of 32-byte records read by old packages. Destructor at RVA 0xcd990
// (body stands in); the serializer at RVA 0xcd570 is a plain cdecl function.
struct FUnnamedRecord_cd570
{
    INT V[8];
};
class FRecordArray_cd570 : public FArrayBase
{
public:
    FRecordArray_cd570() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    __declspec(noinline) ~FRecordArray_cd570() { Remove(0, ArrayNum, sizeof(FUnnamedRecord_cd570)); }
};
FArchive &operator<<(FArchive &Ar, FRecordArray_cd570 &A);

struct UnnamedStruct_cd1b0
{
    UObject *Object;        // 0x00
    INT Value;              // 0x04
    SWORD W8, WA, WC;       // 0x08
    SWORD WE, W10, W12;     // 0x0e
    friend FArchive &operator<<(FArchive &Ar, UnnamedStruct_cd1b0 &S);
};

// RVA 0xcd1b0.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_cd1b0 &S)
{
    if (Ar.Ver() < 0x5c) {
        if (Ar.Ver() >= 0x4a)
            Ar << S.Value;
        else if (Ar.IsLoading())
            S.Value = 0;
        Ar << S.Object;
        INT DummyInt;
        Ar << DummyInt;
        Ar << S.W12 << S.WE;
        SWORD DummyA, DummyB;
        Ar << DummyA << DummyB;
    } else if (Ar.Ver() < 0x70) {
        // Older packages carried render data that is now discarded.
        FUnnamedVertexStream_cda60 DummyVertices;
        FRawIndexBuffer DummyIndicesA, DummyIndicesB;
        FRecordArray_cd570 DummyRecords;
        INT DummyInt;
        Ar << S.Value << S.WE << S.W10;
        Ar << S.Object << DummyInt << DummyVertices << DummyIndicesA << DummyIndicesB;
        if (Ar.Ver() >= 0x6f)
            Ar << DummyRecords;
    } else {
        Ar << S.Value << S.W8 << S.WA << S.WC << S.WE << S.W10;
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_cce40(TArray<UnnamedElement_a4780> *A, INT Slack)
{
    Escape(&GMalloc);
    A->Empty(Slack);
}
void Driver_ccea0(FArchive *Ar, UnnamedStruct_ccea0 *S)
{
    Escape(&GUnnamedRecords_cbfd4c);
    Escape(&(*Ar << *S));
}
void Driver_ccf80(FArchive *Ar, UnnamedStruct_ccf80 *S)
{
    Escape(&(*Ar << *S));
}
void Driver_cd0f0(FArchive *Ar, UnnamedStruct_cd0f0 *S)
{
    Escape(&GUnnamedSettings_90b00);
    Escape(&(*Ar << *S));
}
// Retail callers outside the LTCG set keep 0xcd3e0 a plain thiscall; taking
// its address reproduces that.
void Driver_cd3e0(UnnamedLazyRecords_cd3e0 *L)
{
    void (UnnamedLazyRecords_cd3e0::*Fn)() = &UnnamedLazyRecords_cd3e0::Load;
    Escape(&Fn);
    L->Load();
}
void Driver_cd1b0(FArchive *Ar, UnnamedStruct_cd1b0 *S)
{
    Escape(&GCacheIDCounter);
    Escape(&(*Ar << *S));
}
