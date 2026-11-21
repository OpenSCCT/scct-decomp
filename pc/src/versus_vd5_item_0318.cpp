// Work item w3 0318 (RVA 0x10a350-0x10a625), built with /GL and linked with
// /LTCG. Names are neutral: the record types and classes are unidentified.
// - 0x10a480: operator<< for a 40-byte record (archive in ESI, record in EAX).
//   Versions before 171 stored the vector at 0x0c after the four dwords.
// - 0x10a3d0: operator<< for TArray of those records (archive in EAX, array in EBX).
// - 0x10a350: operator<< for a struct holding the array, a name and four dwords
//   (archive on the stack, struct in EAX); before version 107 the last dword
//   is reset to INDEX_NONE on load.
// - 0x10a550: constructor of a class (vtable 0x10c03b18) with a TArray and an
//   embedded object whose constructor is 0x10a5c0 (vtable 0x10c03ac8, two
//   24-byte elements and a 64-bit cache id drawn as counter * 256 + 0xE0).
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#define INDEX_NONE -1

class UObject;

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FName
{
public:
    INT Index;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(FName &N);                 // +0x18

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

// 40-byte record serialized at 0x10a480 (name unknown).
struct UnnamedStruct_10a480
{
    INT A;
    INT B;
    INT C;
    FVector V;      // 0x0c
    INT D;          // 0x18
    INT E;          // 0x1c
    INT F;          // 0x20
    INT G;          // 0x24
};

// RVA 0x10a480.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_10a480 &R)
{
    Ar << R.A << R.B << R.C;
    if (Ar.Ver() >= 171)
        Ar << R.V;
    Ar << R.D << R.E << R.F << R.G;
    if (Ar.Ver() < 171)
        Ar << R.V;
    return Ar;
}

// RVA 0x10a3d0.
FArchive &operator<<(FArchive &Ar, TArray<UnnamedStruct_10a480> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(UnnamedStruct_10a480), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((UnnamedStruct_10a480 *)A.Data)[A.Add(1, sizeof(UnnamedStruct_10a480))]) UnnamedStruct_10a480;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Struct serialized at 0x10a350 (name unknown).
struct UnnamedStruct_10a350
{
    INT Pad00;
    TArray<UnnamedStruct_10a480> Records;   // 0x04
    INT Pad10;
    INT Pad14;
    INT A;          // 0x18
    INT B;          // 0x1c
    FName Name;     // 0x20
    INT C;          // 0x24
    INT D;          // 0x28
};

// RVA 0x10a350.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_10a350 &S)
{
    Ar << S.Records << S.A;
    Ar << S.Name << S.B << S.C << S.D;
    if (Ar.Ver() < 107 && Ar.IsLoading())
        S.D = INDEX_NONE;
    return Ar;
}

// 24-byte element of UnnamedClass_10a5c0 (constructor 0x10a6b0, destructor 0x109a8df0).
struct UnnamedStruct_10a6b0
{
    UnnamedStruct_10a6b0();
    ~UnnamedStruct_10a6b0();
    BYTE Pad[0x18];
};

extern QWORD UnnamedClass_10a5c0_NextCacheId;   // 0x10c96930

// UE2 MakeCacheID shape, inlined: counter * 256 + type.
inline QWORD MakeCacheID_10a5c0(INT Type)
{
    QWORD Result = UnnamedClass_10a5c0_NextCacheId * 0x100 + Type;
    UnnamedClass_10a5c0_NextCacheId++;
    return Result;
}

#pragma pack(push, 4)
class UnnamedClass_10a5c0
{
public:
    UnnamedClass_10a5c0();
    virtual void Slot0();
    UnnamedStruct_10a6b0 Elements[2];   // 0x04
    BYTE Pad34[0x40 - 0x34];
    QWORD CacheId;                      // 0x40
    INT Revision;                       // 0x48
};
#pragma pack(pop)

// RVA 0x10a5c0.
UnnamedClass_10a5c0::UnnamedClass_10a5c0()
{
    CacheId = MakeCacheID_10a5c0(0xE0);
    Revision = 0;
}

class UnnamedClass_10a550
{
public:
    UnnamedClass_10a550();
    virtual void Slot0();
    INT Pad04;
    TArray<INT> Array;              // 0x08
    UnnamedClass_10a5c0 Inner;      // 0x14
};

// RVA 0x10a550.
UnnamedClass_10a550::UnnamedClass_10a550()
{
}

// ---- Not part of this item: callee defined so LTCG gives it its retail
// register convention (copied from item 0318, RVA 0x1ea40: archive in ESI, index in EDI).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
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

// ---- Scaffolding for the link, not part of the unit.
void Escape(void *);

void Driver_10a350(FArchive *Ar, UnnamedStruct_10a350 *S, UnnamedStruct_10a350 *S2, void *Mem)
{
    *Ar << *S;
    *Ar << *S2;
    Escape(new (Mem) UnnamedClass_10a550);
}
