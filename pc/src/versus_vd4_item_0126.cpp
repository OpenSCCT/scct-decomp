// Work item 0126: FNameEntry serialisation, AllocateNameEntry, FSArray::Add.
// LTCG unit (Core, UnName.cpp / UnTemplate.h).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *wcscpy(TCHAR *, const TCHAR *);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR Tag_NameEntry[];   // L"NameEntry"
extern const TCHAR Tag_FSArray[];     // L"FSArray"
extern const TCHAR Tag_FSArray_Add[]; // L"FSArray::Add"
extern const TCHAR EmptyString[];     // L""

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    INT Ver() { return ArVer; }
    FArchive &operator<<(BYTE &B) { Serialize(&B, 1); return *this; }
    FArchive &operator<<(TCHAR &W) { Serialize(&W, 2); return *this; }
    FArchive &operator<<(DWORD &D) { Serialize(&D, 4); return *this; }
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In);
    ~FString();
    FString(INT InCount, const TCHAR *InSrc);
    FString Left(INT Count) const;
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
};
FArchive &operator<<(FArchive &Ar, FString &S);

enum { NAME_SIZE = 64 };

struct FNameEntry {
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[NAME_SIZE];
};

inline TCHAR FromAnsi(BYTE In) { return (BYTE)In; }

// RVA 0x3b4a0
FArchive &operator<<(FArchive &Ar, FNameEntry &E)
{
    if (Ar.Ver() < 64) {
        INT i;
        for (i = 0; ; i++) {
            BYTE B;
            Ar << B;
            E.Name[i] = FromAnsi(B);
            if (!B)
                break;
        }
        E.Name[i] = 0;
    } else {
        FString Str(E.Name);
        Ar << Str;
        wcscpy(E.Name, *Str.Left(NAME_SIZE - 1));
    }
    return Ar << E.Flags;
}

// RVA 0x3b590
FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(
        sizeof(FNameEntry) - (NAME_SIZE - wcslen(Name) - 1) * sizeof(TCHAR), Tag_NameEntry);
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}

// RVA 0x3b5e0
class FSArray {
public:
    void *Data;
    INT ArrayNum;
    INT Add(INT Count, INT ElementSize);
    INT AddZeroed(INT ElementSize, INT n);
};

INT FSArray::Add(INT Count, INT ElementSize)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    if (Data == 0)
        Data = ArrayNum * ElementSize > 0 ? GMalloc->Malloc(ArrayNum * ElementSize, Tag_FSArray_Add) : 0;
    else
        Data = GMalloc->Realloc(Data, ArrayNum * ElementSize, Tag_FSArray);
    return Index;
}

// Scaffolding for the link, not part of the unit: the FString callees get
// bodies (unverified) so the LTCG linker gives them their retail register
// conventions, and drivers call the functions the way retail callers do.
void Escape(void *);
void Use(void *);
void Use(INT);
// 0x11b80 (another work item; adapted from item_0139): Ar in EAX, S in EBX.
void FString_SerializeIndex(FArchive &Ar, INT &Count);
void FString_Empty(FString &S, INT Slack);
FArchive &operator<<(FArchive &Ar, FString &S)
{
    if (Ar.ArIsLoading)
    {
        INT SaveNum;
        FString_SerializeIndex(Ar, SaveNum);
        UBOOL LoadUCS2Char = SaveNum < 0;
        if (LoadUCS2Char)
            SaveNum = -SaveNum;
        FString_Empty(S, SaveNum);
        S.ArrayNum = SaveNum;
        if (LoadUCS2Char)
        {
            for (INT i = 0; i < SaveNum; i++)
                Ar << S.Data[i];
        }
        else
        {
            for (INT i = 0; i < SaveNum; i++)
            {
                BYTE ACh;
                Ar << ACh;
                S.Data[i] = ACh;
            }
        }
        if (S.ArrayNum == 1)
            FString_Empty(S, 0);
    }
    else
    {
        INT SaveNum = -S.ArrayNum;
        FString_SerializeIndex(Ar, SaveNum);
        for (INT i = 0; i < S.ArrayNum; i++)
            Ar << S.Data[i];
    }
    return Ar;
}
template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}
// 0x4af0 (another work item, from item_0088): this in ESI, InCount in EAX.
TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max);
void FArray_Realloc(FString *A, INT ElementSize);
FString::FString(INT InCount, const TCHAR *InSrc)
{
    Data = 0;
    ArrayNum = ArrayMax = InCount ? InCount + 1 : 0;
    FArray_Realloc(this, sizeof(TCHAR));
    if (ArrayNum)
        appStrncpy(Data, InSrc, InCount + 1);
}
// 0xf7d0 (another work item, from item_0088): this in ECX, result in EAX, Count in EDX.
FString FString::Left(INT Count) const
{
    return FString(Clamp(Count, 0, Len()), **this);
}
struct Linker_3b4a0 {
    char Pad[0xa4];
    FArchive Ar;
};
extern FNameEntry **GNames;
void Driver_3b4a0(Linker_3b4a0 *L, INT *Index, INT Num, FString &S)
{
    Escape(&GMalloc);
    Escape(&GNames);
    FArchive &Ar = L->Ar;
    for (INT i = 0; i < Num; i++)
        Ar << *GNames[Index[i]];
    Ar << S;
    Use((void *)&S.Left(3));
    Use(&Ar);
}
void Driver_3b590(const TCHAR *N, DWORD I, DWORD F, FNameEntry *H, const TCHAR *N2)
{
    Escape(&GMalloc);
    Use(AllocateNameEntry(N, I, F, H));
    Use(AllocateNameEntry(N2, I, F, H));
}
extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memset)
INT FSArray::AddZeroed(INT ElementSize, INT n)
{
    INT Index = Add(n, ElementSize);
    memset((BYTE *)Data + Index * ElementSize, 0, n * ElementSize);
    return Index;
}
void Driver_3b5e0(FSArray *A, INT S, INT N, FSArray *B)
{
    Escape(&GMalloc);
    Use(A->AddZeroed(S, N));
    Use(B->AddZeroed(N, S));
}
