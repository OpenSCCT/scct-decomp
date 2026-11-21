// Work item 0110: Versus RVA 0x1cf1f-0x1d2cb.
// Every function here comes from the LTCG link (register or stack-this
// conventions), so they are checked with try_ltcg.py.
// 0x1cf1f (catch funclet) and 0x1cf5d (tail of a larger function whose start is
// not in the index) are fragments of one bigger routine and are not written here.
// Build: try_ltcg.py --flags "/O2 /Ob1 /Gy" (add /GX for the 0x1d130 group).
// The helpers marked "defined only for its link convention" also match retail
// byte for byte (0xf6b0, 0x3b590, 0x1ff70, 0xa32b0, 0xa3320, 0xa3370).
// 0x1d1a0 is plain __stdcall in retail (callee pops, no LTCG register use).
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

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);                         // 0x109044e0
    void Remove(INT Index, INT Count, INT ElementSize);          // 0x109119c0
    INT Num() { return ArrayNum; }
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    INT RemoveItem(const T &Item);
    void Remove(INT Index, INT Count = 1);
    ~TArray();
};

// Out of line in retail: 0x109a3320 for TArray<FUnnamedEntry_14>.
template<class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// Out of line in retail: 0x109a32b0 for TArray<FUnnamedEntry_14> (this on the stack).
template<class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

// RVA 0x10a0bd60 in retail (this in EDI, item by reference on the stack).
template<class T> INT TArray<T>::RemoveItem(const T &Item)
{
    INT OriginalNum = ArrayNum;
    for (INT Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            FArray::Remove(Index--, 1, sizeof(T));
    return OriginalNum - ArrayNum;
}

// Global list at 0x10cc9ea4. Neutral name: no evidence for the original.
extern TArray<INT> GUnnamedList_10cc9ea4;

// RVA 0x1d1a0: append an entry to the list.
void __stdcall UnnamedListAdd_1d1a0(INT Item)
{
    GUnnamedList_10cc9ea4.AddItem(Item);
}

// RVA 0x1d1c0: remove every copy of an entry from the list (Item in EAX).
void UnnamedListRemove_1d1c0(INT Item)
{
    INT Local = Item;
    GUnnamedList_10cc9ea4.RemoveItem(Local);
}

// ---- 0x1d130: destructor of an unnamed class ----
// Neutral names throughout: no evidence for the originals.
class FString : public FArray
{
public:
    ~FString();                       // 0x109048b0
};

// 20-byte array element whose destructor (0x109a3370) frees the string at +4.
struct FUnnamedEntry_14
{
    INT A;
    FString S;
    INT B;
    ~FUnnamedEntry_14();
};
FUnnamedEntry_14::~FUnnamedEntry_14() {}

class UnnamedBuffer
{
public:
    void *Data;
    INT Num;
    ~UnnamedBuffer()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        Num = 0;
    }
};

class UnnamedClass_1d130
{
public:
    TArray<FUnnamedEntry_14> Entries;   // +0x00
    UnnamedBuffer Buffer;               // +0x0c
    ~UnnamedClass_1d130();
};

// RVA 0x1d130
UnnamedClass_1d130::~UnnamedClass_1d130()
{
}

// ---- 0x1d1e0: make a unique object name ----
enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };
class FName
{
public:
    FName(const TCHAR *Name, EFindName FindType);   // 0x1091ff70 (this in EBX, Name in EAX)
    INT Index;
};
struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[64];
};
extern TArray<FNameEntry *> FName_Names;         // 0x10cc9e5c, FName::Names
extern TArray<INT> FName_Available;              // 0x10cc9e68, FName::Available
extern FNameEntry *FName_NameHash[4096];         // 0x10c7d4d8, FName::NameHash
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern DWORD GCRCTable[256];                    // 0x10c78cd0
inline TCHAR appToUpper(TCHAR c)
{
    return (c < 'a' || c > 'z') ? c : c + 'A' - 'a';
}
// RVA 0x1090f6b0 in retail (Data in EAX); defined only for its link convention.
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data) {
        TCHAR Ch = appToUpper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
// RVA 0x1093b590 in retail (Name in EDI); defined only for its link convention.
FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(sizeof(FNameEntry) - (64 - wcslen(Name) - 1) * sizeof(TCHAR), L"FNameEntry");
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}
#define RF_Native 0x04000000

// RVA 0x1091ff70 in retail; defined here only so the link gives it its retail
// convention (this in EBX, Name in EAX, FindType on the stack).
FName::FName(const TCHAR *Name, EFindName FindType)
{
    if (!Name[0]) {
        Index = 0;
        return;
    }
    INT iHash = appStrihash(Name) & 4095;
    for (FNameEntry *Hash = FName_NameHash[iHash]; Hash; Hash = Hash->HashNext) {
        if (_wcsicmp(Name, Hash->Name) == 0) {
            Index = Hash->Index;
            if (FindType == FNAME_Intrinsic)
                FName_Names(Index)->Flags |= RF_Native;
            return;
        }
    }
    if (FindType == FNAME_Find) {
        Index = 0;
        return;
    }
    if (FName_Available.Num()) {
        Index = FName_Available(FName_Available.Num() - 1);
        FName_Available.FArray::Remove(FName_Available.Num() - 1, 1, sizeof(INT));
    } else {
        Index = FName_Names.Add(1, sizeof(FNameEntry *));
    }
    FName_Names(Index) = FName_NameHash[iHash] = AllocateNameEntry(Name, Index, 0, FName_NameHash[iHash]);
    if (FindType == FNAME_Intrinsic)
        FName_Names(Index)->Flags |= RF_Native;
}

class UObject
{
public:
    void *VfTable;
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *Linker;
    INT LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;          // +0x20
    const TCHAR *GetName() { return FName_Names(Name.Index)->Name; }
};
class UClass : public UObject {};

extern INT GUniqueNameCounter;                  // 0x10c92588
INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);   // 0x1090f4f0
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscat(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsncpy(TCHAR *, const TCHAR *, unsigned int);
inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT MaxLen)
{
    wcsncpy(Dest, Src, MaxLen);
    Dest[MaxLen - 1] = 0;
    return Dest;
}

// RVA 0x1d1e0 (Class in EAX, return slot in EDI).
FName MakeUniqueObjectName(UClass *Class)
{
    TCHAR NewBase[64], Result[64], Tail[64];
    wcscpy(NewBase, Class->GetName());
    TCHAR *End = NewBase + wcslen(NewBase);
    while (End > NewBase && End[-1] >= '0' && End[-1] <= '9')
        End--;
    *End = 0;
    appSprintf(Result, L"%i_", GUniqueNameCounter++);
    appStrncpy(Tail, NewBase, 63 - wcslen(Result));
    wcscat(Result, Tail);
    FName N(Result, FNAME_Add);
    return N;
}

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_1d1a0(INT Item) { Escape(&GUnnamedList_10cc9ea4); UnnamedListAdd_1d1a0(Item); }
void Driver_1d1c0(INT *P) { Escape(&GUnnamedList_10cc9ea4); UnnamedListRemove_1d1c0(P[0]); UnnamedListRemove_1d1c0(P[1]); }
void Driver_1d130(UnnamedClass_1d130 *P) { P->~UnnamedClass_1d130(); }
void Driver_1d1e0(UClass *C, FName *Out) { Escape(&GUniqueNameCounter); Escape(&FName_Names); *Out = MakeUniqueObjectName(C); }
