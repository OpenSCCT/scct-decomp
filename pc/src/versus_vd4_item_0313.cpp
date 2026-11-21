// Work item 0313 (RVA 0x85d90-0x85e6d): two TArray template instances (UE2
// UnTemplate.h), both LTCG code.
//   0x85d90 TArray<UnnamedElement_85d90>::Empty(INT Slack): `this` in ESI,
//           ret 4. The element is 0x5c bytes with an out-of-line destructor
//           (0x861a0, takes `this` on the stack); its real type is unknown.
//   0x85dd0 operator<<(FArchive&, TArray<INT>&): archive in EAX, array in
//           EBX. Elements are 4-byte values serialized with Ar.Serialize(&V,4)
//           (FArchive slot 1); the compact-index serializer is 0x1ea40
//           (archive in ESI, index in EDI).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class UObject;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, 4);
        return Ar;
    }
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
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    __declspec(noinline) void Empty(INT Slack)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }

};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, Size);
    return &Array(Index);
}

template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.FArray::Empty(sizeof(T), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) T;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0x1ea40 (Core UnCorSc.cpp); defined so the link gives it its LTCG
// convention (archive in ESI, index in EDI).
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

// Neutral names: a 0x5c-byte element whose destructor (0x861a0, `this` on
// the stack, exception frame) destroys a member at +0x44 (destructor 0x90c4e0)
// and then a member at +0x1c (destructor 0xaee510).
struct UnnamedMember1c_85d90
{
    BYTE Body[0x28];
    ~UnnamedMember1c_85d90();
};

struct UnnamedMember44_85d90
{
    BYTE Body[0x18];
    ~UnnamedMember44_85d90();
};

struct UnnamedElement_85d90
{
    BYTE Header[0x1c];
    UnnamedMember1c_85d90 A;
    UnnamedMember44_85d90 B;
    __declspec(noinline) ~UnnamedElement_85d90();
};

// RVA 0x861a0 (work item 0315; defined here only so the link gives it its
// stack-this LTCG convention, not verified in this item).
UnnamedElement_85d90::~UnnamedElement_85d90()
{
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_85d90(TArray<UnnamedElement_85d90> *A, INT Slack) { A->Empty(Slack); A->Empty(0); A->Empty(Slack + 1); }
FArchive &Driver_85dd0(FArchive &Ar, TArray<INT> &A) { return Ar << A; }
