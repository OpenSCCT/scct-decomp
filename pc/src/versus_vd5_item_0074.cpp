// Work item 0074 (RVA 0xa8df0-0xa9054): TLazyArray<BYTE> and a TArray of an
// unnamed 0xa4-byte element, from an LTCG object (custom register conventions).
//  0xa8df0 TLazyArray<BYTE>::~TLazyArray (vtable 0x10c08b00; SavedAr->DetachLazyLoader).
//  0xa8e50 TLazyArray<BYTE>::Load (Tell / Seek / serialize / SavedPos *= -1).
//  0xa8ea0 operator<<(FArchive&, TArray<BYTE>&): archive in EAX, array in EBX.
//  0xa8f40 TArray<FUnnamedElement_a9000>::~TArray, this on the stack.
//  0xa8fb0 TArray<FUnnamedElement_a9000>::Remove, this on the stack, Index in EDI.
//  0xa9000 FUnnamedElement_a9000::~FUnnamedElement_a9000 (implicit), this on the stack.
// The 0xa4-byte element type is not named anywhere in the binary.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class UObject;
class FLazyLoader;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

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
    virtual void Virtual18();
    virtual void Virtual1c();
    virtual void Virtual20();
    virtual void Virtual24();
    virtual INT Tell();                                     // +0x28
    virtual void Virtual2c();
    virtual void Virtual30();
    virtual void Virtual34();
    virtual void Virtual38();
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40
    virtual void DetachLazyLoader(FLazyLoader *LazyLoader); // +0x44

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Realloc(INT ElementSize);                          // 0x4600
    void Remove(INT Index, INT Count, INT ElementSize);     // 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

// TArray<BYTE>::~TArray is out of line at 0xf250 (another object).

class FLazyLoader
{
public:
    FArchive *SavedAr;
    INT SavedPos;
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    TLazyArray() {}
    ~TLazyArray();
    void Load();
    void Unload();
};

extern const TCHAR OperatorShlTArray_Tag[];   // L"operator<<(TArray)"

// RVA 0xa8ea0.
FArchive &operator<<(FArchive &Ar, TArray<BYTE> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum, OperatorShlTArray_Tag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(1);
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum);
    return Ar;
}

// RVA 0xa8df0.
template <> TLazyArray<BYTE>::~TLazyArray()
{
    if (SavedAr)
        SavedAr->DetachLazyLoader(this);
}

// RVA 0xa8e50.
template <> void TLazyArray<BYTE>::Load()
{
    if (SavedPos > 0) {
        INT PushedPos = SavedAr->Tell();
        SavedAr->Seek(SavedPos);
        *SavedAr << (TArray<BYTE> &)*this;
        SavedPos *= -1;
        SavedAr->Seek(PushedPos);
    }
}

struct FUnnamedPartA_a9060 { INT V[3]; };
// Part element contents are unknown (their arrays only matter here).
struct FUnnamedPartB_a7bf30 { INT V; };
// TArray<FUnnamedPartA_a9060>::~TArray is at 0xa9060, TArray<FUnnamedPartB_a7bf30>::~TArray at 0xa7bf30.

// 0xa4-byte element; only the two trailing arrays need destruction.
struct FUnnamedElement_a9000
{
    BYTE Header[0x8c];
    TArray<FUnnamedPartA_a9060> A;     // +0x8c
    TArray<FUnnamedPartB_a7bf30> B;    // +0x98
};

// RVA 0xa8f40 (with Remove at 0xa8fb0 and the element destructor at 0xa9000).
template <> TArray<FUnnamedElement_a9000>::~TArray()
{
    Remove(0, ArrayNum);
}

// The part arrays' destructors (0xa9060, 0xa7bf30) are the same template body;
// defined here so the LTCG link gives them their retail this-on-stack form.
template <> TArray<FUnnamedPartA_a9060>::~TArray()
{
    Remove(0, ArrayNum);
}
template <> TArray<FUnnamedPartB_a7bf30>::~TArray()
{
    Remove(0, ArrayNum);
}

// Stand-in for the compact index serializer (RVA 0x1ea40, published in
// item 0116), defined so the LTCG link gives it its retail ESI/EDI form.
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

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// A local array of lazy arrays is destroyed through the EH vector destructor
// iterator, which takes the destructor's address, so it keeps its thiscall form.
void Driver_a8df0(TLazyArray<BYTE> *L)
{
    TLazyArray<BYTE> Local[2];
    Escape(Local);
}
FArchive &Driver_a8ea0(FArchive &Ar, char *Owner)
{
    Escape(&GMalloc);
    return Ar << *(TArray<BYTE> *)(Owner + 0x10);
}
void Driver_a8f40(TArray<FUnnamedElement_a9000> *A, TArray<FUnnamedElement_a9000> *B)
{
    A->~TArray();
    B->~TArray();
}
void Driver_a8fb0(TArray<FUnnamedElement_a9000> *A, INT i, INT n)
{
    A->Remove(i, n);
    A->Remove(i + 1, n);
}
