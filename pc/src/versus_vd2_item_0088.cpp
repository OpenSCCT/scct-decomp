// Work item 0088: FString helpers (Unreal Engine 2 UnString.h), RVA 0x15460-0x155a9.
// These functions come from an LTCG object (custom calling conventions).
// try_ltcg.py, /O2 /Ob1 /Gy: 0x15460 (FString::operator!=, this in EAX, ret 4)
// and 0x15590 (iterator operator++, this in EAX) match. 0x15490 (FString::Split,
// /GX) gets retail's callee conventions but not its register allocation or
// prologue order; it is a near miss. InStr, Left, Mid and the (INT, const TCHAR*)
// constructor are defined only so the link gives them retail's conventions.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsstr(const TCHAR *, const TCHAR *);
extern const TCHAR EmptyString[];   // L"" shared in retail

template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() {}
    FArray(INT InNum, INT ElementSize) : Data(0), ArrayNum(InNum), ArrayMax(InNum) { Realloc(ElementSize); }
    INT Num() const { return ArrayNum; }
    void Realloc(INT ElementSize);
};
TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max);

class FString : public FArray
{
public:
    FString(INT InCount, const TCHAR *InSrc);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
    INT Len() const { return Num() ? Num() - 1 : 0; }
    UBOOL operator!=(const TCHAR *Other) const;
    INT InStr(const TCHAR *SubStr, UBOOL Right) const;
    INT InStr(const FString &SubStr, UBOOL Right) const { return InStr(*SubStr, Right); }
    FString Left(INT Count) const;
    FString Mid(INT Start, INT Count = 0x7fffffff) const;
    UBOOL Split(const FString &InS, FString *LeftS, FString *RightS, UBOOL bRight) const;
};

// 0xf890 (another work item; defined so the link gives it retail's convention)
INT FString::InStr(const TCHAR *SubStr, UBOOL Right) const
{
    if (!Right)
    {
        const TCHAR *Tmp = wcsstr(**this, SubStr);
        return Tmp ? (INT)(Tmp - **this) : -1;
    }
    else
    {
        for (INT i = Len() - 1; i >= 0; i--)
        {
            INT j;
            for (j = 0; SubStr[j]; j++)
                if (((const TCHAR *)Data)[i + j] != SubStr[j])
                    break;
            if (!SubStr[j])
                return i;
        }
        return -1;
    }
}

// 0x4af0 (another work item)
FString::FString(INT InCount, const TCHAR *InSrc)
:   FArray(InCount ? InCount + 1 : 0, sizeof(TCHAR))
{
    if (ArrayNum)
        appStrncpy((TCHAR *)Data, InSrc, InCount + 1);
}

// 0xf7d0 (another work item)
FString FString::Left(INT Count) const
{
    return FString(Clamp(Count, 0, Len()), **this);
}

// 0xf820 (another work item)
FString FString::Mid(INT Start, INT Count) const
{
    DWORD End = Start + Count;
    Start = Clamp((DWORD)Start, (DWORD)0, (DWORD)Len());
    End = Clamp((DWORD)End, (DWORD)Start, (DWORD)Len());
    return FString(End - Start, **this + Start);
}

// 0x15460
UBOOL FString::operator!=(const TCHAR *Other) const
{
    return _wcsicmp(**this, Other) != 0;
}

// 0x15490
UBOOL FString::Split(const FString &InS, FString *LeftS, FString *RightS, UBOOL bRight) const
{
    INT InPos = InStr(InS, bRight);
    if (InPos < 0)
        return 0;
    if (LeftS)
        *LeftS = Left(InPos);
    if (RightS)
        *RightS = Mid(InPos + InS.Len());
    return 1;
}

// 0x15590: iterator over a TArray of pointers that skips null entries.
// Neutral name: no symbol evidence for the owning class.
class FPointerArray : public FArray
{
public:
    void *&operator()(INT i) const { return ((void **)Data)[i]; }
};

class UnnamedIterator_15590
{
public:
    FPointerArray *Array;
    INT Index;
    UnnamedIterator_15590 &operator++();
};

UnnamedIterator_15590 &UnnamedIterator_15590::operator++()
{
    while (++Index < Array->Num() && (*Array)(Index) == 0)
        ;
    return *this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_15460(const FString *S, const FString *S2, const TCHAR *T, const TCHAR *U) { Escape((void *)(*S != T)); Escape((void *)(*S2 != U)); Escape((void *)(*S != U)); }
typedef UBOOL (FString::*SplitFn)(const FString &, FString *, FString *, UBOOL) const;
void Driver_15490(const FString *S, const FString *In, FString *L, FString *R, UBOOL b)
{
    SplitFn P = &FString::Split;   // retail Split is called with a plain thiscall
    Escape(&P);
    Escape((void *)S->Split(*In, L, R, b));
}
void Driver_15590(UnnamedIterator_15590 *It) { ++*It; }
