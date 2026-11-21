// Work item w3 0146: Versus RVA 0xc3b00-0xc3df5, built with /GL + /LTCG.
// Copy constructors and assignment operators for an unidentified record and
// the dynamic arrays it holds (UE2 UnTemplate.h TArray, SCCT flavour that
// appMemcpy's plain element types).
//   0xc3b00 UnnamedRecord_c3b00::operator=        (this in ESI, Other in EBX)
//   0xc3b80 UnnamedElem_c3b00::operator=          (this in EDI, Other on stack)
//   0xc3c30 TArray<UnnamedElem_c3b00>::operator=  (this in EAX, Other in EDI)
//   0xc3c90 UnnamedElem_c3b00 copy constructor    (this on stack, Other in EBX)
//   0xc3d00 TArray<FUnnamed8_c3b00>(const TArray&)  (this on stack, Other in EDI)
//   0xc3d80 TArray<FUnnamed6_c3b00>(const TArray&)  (this on stack, Other in EDI)
// Names are neutral: no vtable labels or strings identify the record.

typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor" 0x10c10944

void *appMemcpy(void *Dest, const void *Src, INT Count); // 0x40a0

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
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
    INT Add(INT Count, INT ElementSize);                // 0x44e0
    void Empty(INT ElementSize, INT Slack);             // 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
};

// Arrays of plain data: copied with appMemcpy.
template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other);
    ~TArray() { Remove(0, ArrayNum); }
    void Remove(INT Index, INT Count) { FArray::Remove(Index, Count, sizeof(T)); }
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
};

template <class T> __declspec(noinline) TArray<T>::TArray(const TArray &Other)
    : FArray(Other.ArrayNum, sizeof(T))
{
    appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
}

struct FUnnamed8_c3b00 { INT A, B; };
struct FUnnamed6_c3b00 { _WORD A, B, C; };

struct FVector { FLOAT X, Y, Z; };

// 0x28-byte element.
class UnnamedElem_c3b00
{
public:
    INT Header;
    TArray<FUnnamed8_c3b00> Pairs;   // 0x04
    TArray<FUnnamed6_c3b00> Triples; // 0x10
    TArray<_WORD> Words;             // 0x1c

    UnnamedElem_c3b00(const UnnamedElem_c3b00 &Other);
    ~UnnamedElem_c3b00() {}
    UnnamedElem_c3b00 &operator=(const UnnamedElem_c3b00 &Other);
};

__declspec(noinline) UnnamedElem_c3b00::UnnamedElem_c3b00(const UnnamedElem_c3b00 &Other)
    : Header(Other.Header), Pairs(Other.Pairs), Triples(Other.Triples), Words(Other.Words)
{
}

__declspec(noinline) UnnamedElem_c3b00 &UnnamedElem_c3b00::operator=(const UnnamedElem_c3b00 &Other)
{
    Header = Other.Header;
    Pairs = Other.Pairs;
    Triples = Other.Triples;
    Words = Other.Words;
    return *this;
}

// Array of elements with constructors and destructors.
class TElemArray_c3b00 : public FArray
{
public:
    UnnamedElem_c3b00 &operator()(INT i) { return ((UnnamedElem_c3b00 *)Data)[i]; }
    const UnnamedElem_c3b00 &operator()(INT i) const { return ((UnnamedElem_c3b00 *)Data)[i]; }
    void Empty(INT Slack); // 0xc2ff0
    TElemArray_c3b00 &operator=(const TElemArray_c3b00 &Other);
};

inline void *operator new(unsigned int Size, TElemArray_c3b00 &Array)
{
    INT Index = Array.Add(1, sizeof(UnnamedElem_c3b00));
    return &Array(Index);
}

__declspec(noinline) void TElemArray_c3b00::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~UnnamedElem_c3b00();
    FArray::Empty(sizeof(UnnamedElem_c3b00), Slack);
}

__declspec(noinline) TElemArray_c3b00 &TElemArray_c3b00::operator=(const TElemArray_c3b00 &Other)
{
    if (this != &Other)
    {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) UnnamedElem_c3b00(Other(i));
    }
    return *this;
}

class UnnamedRecord_c3b00
{
public:
    virtual void Slot0();
    FVector Location;              // 0x04
    INT Field10;                   // 0x10
    INT Field14;                   // 0x14
    INT Field18;                   // 0x18
    TArray<INT> Ints;              // 0x1c
    TElemArray_c3b00 Elems;        // 0x28
    UnnamedElem_c3b00 Elem;        // 0x34

    UnnamedRecord_c3b00 &operator=(const UnnamedRecord_c3b00 &Other);
};

__declspec(noinline) UnnamedRecord_c3b00 &UnnamedRecord_c3b00::operator=(const UnnamedRecord_c3b00 &Other)
{
    Location = Other.Location;
    Field10 = Other.Field10;
    Field14 = Other.Field14;
    Field18 = Other.Field18;
    Elem = Other.Elem;
    Ints = Other.Ints;
    Elems = Other.Elems;
    return *this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c3b00(UnnamedRecord_c3b00 &A, const UnnamedRecord_c3b00 &B)
{
    Escape(&GMalloc);
    A = B;
}
