// Work item 0169: Versus RVA 0xcd500-0xcd6f7.
// Unreal Engine 2 UnTemplate.h code instantiated for two unnamed element
// types, link-time optimised (/GL + /LTCG):
//   0xcd500 TArray<FUnnamedRecord_104>::~TArray (this on the stack, ret 4)
//   0xcd570 operator<<(FArchive&, TArray<UnnamedClass_cd6a0>&)
//   0xcd6a0 UnnamedClass_cd6a0::UnnamedClass_cd6a0 (this in ESI)
// Class names are neutral; the real names were not recovered.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;                     // 0x10c73bf0

inline void* operator new(unsigned int, void* Mem) { return Mem; }

class UObject;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(UObject* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(UObject*& Res);
    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving;
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    void ByteOrderSerialize(void* V, INT Length) { Serialize(V, Length); }
    friend FArchive& operator<<(FArchive& Ar, INT& I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
};

// UE2 FCompactIndex (UnArc.h); operator<< is RVA 0x1ea40 (Ar in ESI, index in EDI).
class FCompactIndex
{
public:
    INT Value;
    friend FArchive& operator<<(FArchive& Ar, FCompactIndex& I);
};
#define AR_INDEX(intref) (*(FCompactIndex*)&(intref))

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);              // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);  // RVA 0x119c0
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    T& operator()(INT i) { return ((T*)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    void Empty(INT Slack = 0);   // out of line in retail (0xcc430 for the class below, this in ESI)
    void CountBytes(FArchive& Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};

template<class T> inline void* operator new(unsigned int, TArray<T>& Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

template<class T> FArchive& operator<<(FArchive& Ar, TArray<T>& A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) T;
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// 0x104-byte trivially destructible record (contents not recovered).
struct FUnnamedRecord_104
{
    TCHAR Text[130];
};

// Element serialized through 0xcd780 (Ar in EAX, array in EBX); not recovered.
struct FUnnamedElement_cd780
{
    INT A, B;
    friend FArchive& operator<<(FArchive& Ar, FUnnamedElement_cd780& E) { return Ar << E.A << E.B; }
};

extern unsigned __int64 UnnamedClass_86620_NextId; // 0x10c96930

// Unnamed class, vtable 0x10c048bc (neutral name).
#pragma pack(push, 4)
class UnnamedClass_cd6a0
{
public:
    // Retail calls the constructor out of line (this in ESI); noinline
    // reproduces that.
    __declspec(noinline) UnnamedClass_cd6a0();
    ~UnnamedClass_cd6a0();  // 0xcd430, out of line (this in EAX)
    virtual void Slot0();

    TArray<FUnnamedElement_cd780> Items; // +04
    INT A;                               // +10
    unsigned __int64 Id;                 // +14
    INT B;                               // +1c

    friend FArchive& operator<<(FArchive& Ar, UnnamedClass_cd6a0& C)
    {
        return Ar << C.Items << C.A << C.B;
    }
};
#pragma pack(pop)

// Near match: retail stores the counter's high dword before Id's low dword;
// VC7.0 LTCG schedules those two stores the other way round (4 bytes).
UnnamedClass_cd6a0::UnnamedClass_cd6a0()
{
    Id = UnnamedClass_86620_NextId++ * 256 + 0xe1;
    A = 0;
    B = 0;
}

// Scaffolding for the link, not part of the unit. These callees live
// elsewhere in retail; they are written out only so the linker gives them
// retail's register conventions.
__declspec(noinline) UnnamedClass_cd6a0::~UnnamedClass_cd6a0()
{
}
template<class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}
FArchive& operator<<(FArchive& Ar, FCompactIndex& I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    unsigned char B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40)
    {
        V >>= 6;
        unsigned char B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80)
        {
            V >>= 7;
            unsigned char B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80)
            {
                V >>= 7;
                unsigned char B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80)
                {
                    V >>= 7;
                    unsigned char B4 = V;
                    Ar.Serialize(&B4, 1);
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
void Escape(void*);
void Driver_cd500(TArray<FUnnamedRecord_104>* A) { Escape(&GMalloc); A->~TArray(); }
void Driver_cd570(FArchive* Ar, TArray<UnnamedClass_cd6a0>* A)
{
    FArchive& (*Fn)(FArchive&, TArray<UnnamedClass_cd6a0>&) = &operator<<;
    Escape((void*)Fn);
    Escape(&(*Ar << *A));
}
