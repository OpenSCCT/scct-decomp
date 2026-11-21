// Work item 0117: Versus RVA 0x1ee10-0x1f0a4 (Core UnObj.cpp / UnTemplate.h
// neighbourhood). All six come from the LTCG link and take arguments in
// registers or `this` on the stack. Built with try_ltcg.py --flags
// "/O2 /Ob1 /Gy /GX".
// Matching: 0x1eeb0 FindItem, 0x1efa0 AddItem, 0x1efc0 copy constructor.
// Near: 0x1ee10 SetLanguage (retail keeps a call to the empty iterator
// destructor at 0x4a550 that the link removes here); 0x1ef20 and 0x1f040
// (retail keeps the constant 0 in a callee-saved register for the Remove
// index, the EH state and the FArray resets; here they are immediates, and
// 0x1ef20 is a plain thiscall in retail, which this link only gives it when
// the destructor is exported).
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
extern FMalloc *GMalloc;                 // 0x10c73bf0

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
void appMemcpy(void *Dest, const void *Src, INT Count);   // 0x40a0

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);                       // 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);        // 0x119c0
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other);
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    void Remove(INT Index, INT Count = 1);
    INT AddItem(const T &Item);
    UBOOL FindItem(const T &Item, INT &Index) const;
};

template<class T> TArray<T>::TArray(const TArray<T> &Other)
    : FArray(Other.ArrayNum, sizeof(T))
{
    appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
}

template<class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

template<class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template<class T> INT TArray<T>::AddItem(const T &Item)
{
    INT Index = Add(1);
    (*this)(Index) = Item;
    return Index;
}

template<class T> UBOOL TArray<T>::FindItem(const T &Item, INT &Index) const
{
    for (Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            return 1;
    return 0;
}

extern TCHAR FString_Empty[];            // 0x10c10928, L""

class FString : public TArray<TCHAR>
{
public:
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : FString_Empty; }
    UBOOL operator==(const FString &Other) const { return _wcsicmp(**this, *Other) == 0; }
};

// Element type of the array destroyed at 0x1f040 (0x2c bytes, destructor at
// 0x6200). Neutral name: no evidence for the original one.
struct FUnnamedRecord_2c
{
    INT Fields[11];
    ~FUnnamedRecord_2c();
};

class UObject
{
public:
    virtual void Slots00_4c_0(); virtual void S1(); virtual void S2(); virtual void S3();
    virtual void S4(); virtual void S5(); virtual void S6(); virtual void S7();
    virtual void S8(); virtual void S9(); virtual void S10(); virtual void S11();
    virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
    virtual void S16(); virtual void S17(); virtual void S18(); virtual void S19();
    virtual void LanguageChange();       // +0x50
    static void SetLanguage(const TCHAR *LangExt);
};

extern TArray<UObject *> GObjObjects;    // 0x10cc9e80
extern TCHAR GLanguage[];                // 0x10c6f868
extern TCHAR GTrue[];                    // 0x10c71ab8
extern TCHAR GFalse[];                   // 0x10c71ac8

// Iterator over every live object (no class filter in this build).
class FObjectIterator
{
public:
    FObjectIterator();
    ~FObjectIterator();                  // RVA 0x4a550 (folded empty `ret 4`)
    void operator++()
    {
        while (++Index < Objects->Num() && !(*Objects)(Index))
            ;
    }
    operator UBOOL() { return Index < Objects->Num(); }
    UObject *operator->() { return (*Objects)(Index); }
protected:
    TArray<UObject *> *Objects;
    INT Index;
};

// RVA 0x1f470 (published elsewhere; defined so the link gives it its convention).
FObjectIterator::FObjectIterator()
    : Objects(&GObjObjects), Index(-1)
{
    ++*this;
}

// Folded into the empty `ret 4` at 0x4a550.
__declspec(noinline) FObjectIterator::~FObjectIterator()
{
}

// RVA 0x1ee10: UObject::SetLanguage (LTCG: LangExt in EAX).
void UObject::SetLanguage(const TCHAR *LangExt)
{
    if (_wcsicmp(LangExt, GLanguage) != 0) {
        wcscpy(GLanguage, LangExt);
        wcscpy(GTrue, L"True");
        wcscpy(GFalse, L"False");
        for (FObjectIterator It; It; ++It)
            It->LanguageChange();
    }
}

// RVA 0x1eeb0: TArray<FString>::FindItem (LTCG: this in EDI, Item in EBX, Index in ESI).
template UBOOL TArray<FString>::FindItem(const FString &, INT &) const;
// RVA 0x1ef20: TArray<UObject*>::~TArray.
// RVA 0x1efa0: TArray<UObject*>::AddItem (LTCG: this in ESI).
// RVA 0x1efc0: TArray<UObject*> copy constructor (LTCG: this on stack, Other in EDI).
// RVA 0x1f040: TArray<FUnnamedRecord_2c>::~TArray (LTCG: this on stack).

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_1ee10(const TCHAR *L)
{
    Escape(&GLanguage); Escape(&GTrue); Escape(&GFalse); Escape(&GObjObjects);
    UObject::SetLanguage(L);
}
UBOOL Driver_1eeb0(const TArray<FString> *A, const FString *S, INT *I) { return A->FindItem(*S, *I); }
void Driver_1ef20(TArray<UObject *> *A)
{
    // Retail destroys such arrays from unwind handlers too, which takes the
    // destructor's address and keeps it a plain thiscall.
    Escape(&GMalloc);
    TArray<UObject *> Local;
    Escape(&Local);
    A->~TArray();
}
INT Driver_1efa0(TArray<UObject *> *A, UObject *const *O) { return A->AddItem(*O); }
void Driver_1efc0(void *Mem, const TArray<UObject *> *O) { Escape(&GMalloc); new (Mem) TArray<UObject *>(*O); }
void Driver_1f040(TArray<FUnnamedRecord_2c> *A, TArray<FUnnamedRecord_2c> *B, INT I, INT N)
{
    // Retail removes from such arrays in several places, so Remove stays out of line.
    Escape(&GMalloc);
    B->Remove(I, N);
    B->Remove(N, I);
    B->Remove(I);
    A->~TArray();
}
