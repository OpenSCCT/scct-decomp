// Work item w3 0024: Versus RVA 0x57a80 (724 bytes).
// Serialiser operator<<(FArchive&, T&) for an unidentified record, built with
// /GL + /LTCG: Ar arrives in ESI, the record in ECX, Ar is returned in EAX.
// Record and field names are neutral (UnnamedRecord_57a80): nine DWORDs, a
// 16-byte block at 0x24 and a TArray of 8-byte pairs at 0x34. The low word of
// the DWORD at +4 is a version; below 0x44 the old layout is read.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor" 0x10c10944
extern const TCHAR FArray_EmptyTag[];          // L"FArray::Empty" 0x10c10984
extern const TCHAR FArray_ReallocTag[];        // L"FArray" 0x10c10974

void *appMemcpy(void *Dest, const void *Src, INT Count); // 0x40a0

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);   // slot 1
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual INT Tell();                            // slot 10 (+0x28)
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Seek(INT InPos);                  // slot 15 (+0x3c)

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;  // 0x10
};

inline FArchive &operator<<(FArchive &Ar, INT &V)
{
    Ar.Serialize(&V, sizeof(V));
    return Ar;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);    // 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
    void Empty(INT ElementSize, INT Slack); // 0x4550
    void Realloc(INT ElementSize)
    {
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_EmptyTag);
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArray_ReallocTag);
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    ~TArray();
    void Remove(INT Index, INT Count) { FArray::Remove(Index, Count, sizeof(T)); }
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            FArray::Empty(sizeof(T), Other.ArrayNum);
            appMemcpy(Data, Other.Data, Other.ArrayNum * sizeof(T));
            ArrayNum = Other.ArrayNum;
        }
        return *this;
    }
    void ResetTo(INT Slack)
    {
        ArrayNum = 0;
        if (ArrayMax != Slack)
        {
            ArrayMax = Slack;
            Realloc(sizeof(T));
        }
    }
};

// 0xa7f6a0 for the pair array (retail keeps it out of line).
template <class T> __declspec(noinline) TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.Add(1, sizeof(T));
    return &Array(Index);
}

struct FUnnamedQuad_57a80
{
    INT X, Y, Z, W;
};

inline FArchive &operator<<(FArchive &Ar, FUnnamedQuad_57a80 &Q)
{
    return Ar << Q.X << Q.Y << Q.Z << Q.W;
}

struct FUnnamedPair_57a80
{
    INT A, B;
    FUnnamedPair_57a80(INT InA, INT InB) : A(InA), B(InB) {}
};

inline FArchive &operator<<(FArchive &Ar, FUnnamedPair_57a80 &P)
{
    return Ar << P.A << P.B;
}

struct UnnamedRecord_57a80
{
    INT Field00;
    INT Version;   // 0x04, low word compared with 0x44
    INT Field08;
    INT Field0C;
    INT Field10;
    INT Field14;
    INT Field18;
    INT Field1C;
    INT Field20;
    FUnnamedQuad_57a80 Block; // 0x24
    TArray<FUnnamedPair_57a80> Pairs; // 0x34
};

FArchive &operator<<(FArchive &Ar, UnnamedRecord_57a80 &R)
{
    Ar << R.Field00 << R.Version << R.Field08 << R.Field0C << R.Field10
       << R.Field14 << R.Field18 << R.Field1C << R.Field20;
    if ((R.Version & 0xffff) >= 0x44)
    {
        INT Num = R.Pairs.Num();
        Ar << R.Block;
        Ar << Num;
        if (Ar.ArIsLoading)
            R.Pairs = TArray<FUnnamedPair_57a80>(Num);
        for (INT i = 0; i < Num; i++)
            Ar << R.Pairs(i);
    }
    else
    {
        INT Count, Offset;
        Ar << Count << Offset;
        INT SavedPos = Ar.Tell();
        if (Count)
        {
            Ar.Seek(Offset);
            for (INT i = 0; i < Count; i++)
                Ar << R.Block;
        }
        Ar.Seek(SavedPos);
        if (Ar.ArIsLoading)
        {
            R.Pairs.ResetTo(1);
            new (R.Pairs) FUnnamedPair_57a80(R.Field14, R.Field0C);
        }
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_57a80(FArchive &Ar, UnnamedRecord_57a80 &R)
{
    Escape(&GMalloc);
    Ar << R;
}
