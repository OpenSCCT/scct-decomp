// Work item 0118: Versus RVA 0x1f0b0-0x1f326 (Core container templates, LTCG code).
//   0x1f0b0 TArray<FRecord2C>::Empty   (this in ESI)
//   0x1f0f0 TArray<FRecord3C>::~TArray (this on the stack)
//   0x1f160 TArray<FRecord3C>::Empty   (this in ESI)
//   0x1f1a0 TArray<FRecord1C>::TArray(const TArray&) (this and Other on the stack)
//   0x1f260 TFieldIterator<UProperty>::TFieldIterator (this in ECX, InStruct in EAX)
//   0x1f290 TMultiMap<FString,FString>::MultiFind (this on the stack, Key in EBX, Values in EDI)
// FRecord2C / FRecord3C / FRecord1C are neutral names: element types recovered only from
// their sizes and destructors (0x6200 destroys three FStrings; 0x1f720 destroys five).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };
enum { CLASS_IsAUProperty = 0x8000 };

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern DWORD GCRCTable[256];
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

// RVA 0xf6b0 (Core UnMisc.cpp); defined so the link gives it its LTCG convention.
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        BYTE B = (BYTE)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (BYTE)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayMax == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
    }
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const FString &Other);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
};

inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

struct FRecord1C { INT V[7]; };
struct FRecord2C { FString A, B, C; INT D, E; ~FRecord2C(); };
struct FRecord3C { FString A, B, C, D, E; ~FRecord3C(); };

FRecord2C::~FRecord2C() {}   // RVA 0x6200, bound separately
FRecord3C::~FRecord3C() {}   // RVA 0x1f720, bound separately

template <class T> class TArray : public FArray
{
public:
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(Other(i));
    }
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count);
    void Empty(INT Slack);
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, Size);
    return &Array(Index);
}

template <class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

// UE2 TMultiMap<FString,FString> (FConfigSection): TPair is HashNext, Key, Value (0x1c bytes).
struct FStringPair
{
    INT HashNext;
    FString Key;
    FString Value;
};

class TMultiMap_FString
{
public:
    TArray<FStringPair> Pairs;
    INT *Hash;
    INT HashCount;
    void MultiFind(const FString &Key, TArray<FString> &Values);
};

void TMultiMap_FString::MultiFind(const FString &Key, TArray<FString> &Values)
{
    for (INT i = Hash[(GetTypeHash(Key) & (HashCount - 1))]; i != INDEX_NONE; )
    {
        FStringPair &Pair = Pairs(i);
        if (Pair.Key == Key)
            new (Values) FString(Pair.Value);
        i = Pair.HashNext;
    }
}

// Field iteration (UE2 UnClass.h), layouts as in item 0098.
class UClass;
class UStruct;
class UObject
{
public:
    virtual void Slot00();
    BYTE Pad04[0x24 - 0x04];
    UClass *Class;          // +0x24
};
class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};
class UStruct : public UField
{
public:
    UField *Children;       // +0x30
    UStruct *GetInheritanceSuper();
};
class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
};

class TFieldIterator_UProperty
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator_UProperty(UStruct *InStruct);
    void IterateToNext();
};

TFieldIterator_UProperty::TFieldIterator_UProperty(UStruct *InStruct)
    : Struct(InStruct), Field(InStruct ? InStruct->Children : 0)
{
    IterateToNext();
}

// RVA 0x1f850, bound separately (published with item 0098).
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1f0b0(TArray<FRecord2C> *A, INT Slack) { A->Empty(Slack); }
void Driver_1f0f0(TArray<FRecord3C> *A) { Escape(&GMalloc); A->~TArray<FRecord3C>(); }
void Driver_1f160(TArray<FRecord3C> *A, INT Slack) { A->Empty(Slack); A->Remove(1, Slack); }
void Driver_1f1a0(TArray<FRecord1C> *A, const TArray<FRecord1C> &B) { Escape(&GMalloc); new (A) TArray<FRecord1C>(B); }
void Driver_1f260(UStruct *S) { TFieldIterator_UProperty It(S); Escape(&It); }
void Driver_1f290(TMultiMap_FString *M, const FString &K, TArray<FString> &V) { M->MultiFind(K, V); }
