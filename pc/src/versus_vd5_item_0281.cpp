// Work item 0281: Versus RVA 0xfe020-0xfe1b1 (UInput neighbourhood).
// 0xfe0c0 and 0xfe0f0 are plain thiscall code; 0xfe020 and the rest were
// compiled with /GL and linked with /LTCG (custom register conventions), so
// the retail callees they use are defined below only for their link
// convention (copied from the published FName unit versus_vd2_item_0110.cpp
// and neighbouring work).
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
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsstr(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcschr(const TCHAR *, TCHAR);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const TCHAR *);
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
inline TCHAR *appStrcpy(TCHAR *Dest, const TCHAR *Src) { return wcscpy(Dest, Src); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline void appMemmove(void *D, const void *S, INT C) { memmove(D, S, C); }

// ---- FName (retail 0x1091ff70: this in EBX, Name in EAX, FindType pushed) ----
enum EFindName { FNAME_Find, FNAME_Add, FNAME_Intrinsic };
class FName
{
public:
    FName() {}
    FName(const TCHAR *Name, EFindName FindType);
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(INT Other) const { return Index != Other; }
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
extern DWORD GCRCTable[256];                     // 0x10c78cd0
#define RF_Native 0x04000000
inline TCHAR appToUpper(TCHAR c)
{
    return (c < 'a' || c > 'z') ? c : c + 'A' - 'a';
}
// RVA 0x1090f6b0 in retail; defined only for its link convention.
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
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
// RVA 0x1093b590 in retail; defined only for its link convention.
__declspec(noinline) FNameEntry *AllocateNameEntry(const TCHAR *Name, DWORD Index, DWORD Flags, FNameEntry *HashNext)
{
    FNameEntry *NameEntry = (FNameEntry *)GMalloc->Malloc(sizeof(FNameEntry) - (64 - wcslen(Name) - 1) * sizeof(TCHAR), L"FNameEntry");
    NameEntry->Index = Index;
    NameEntry->Flags = Flags;
    NameEntry->HashNext = HashNext;
    wcscpy(NameEntry->Name, Name);
    return NameEntry;
}
// RVA 0x1091ff70 in retail; defined only for its link convention.
__declspec(noinline) FName::FName(const TCHAR *Name, EFindName FindType)
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

// UnMisc.cpp (retail 0x109126c0; LTCG: &Str in EAX, Result in EBX).
__declspec(noinline) UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseEscape)
{
    INT Len = 0;
    while (*Str == ' ' || *Str == 9)
        Str++;
    if (*Str == '"') {
        Str++;
        while (*Str && *Str != '"' && (Len + 1) < MaxLen) {
            TCHAR c = *Str++;
            if (c == '\\' && UseEscape) {
                c = *Str++;
                if (!c)
                    break;
            }
            if ((Len + 1) < MaxLen)
                Result[Len++] = c;
        }
        if (*Str == '"')
            Str++;
    } else {
        for (; *Str && *Str != ' ' && *Str != 9; Str++)
            if ((Len + 1) < MaxLen)
                Result[Len++] = *Str;
    }
    Result[Len] = 0;
    return Len != 0;
}

// Retail 0x10911960: strips a "(N)"-style marker out of Str and returns N
// (neutral name, owner unknown).
extern const TCHAR Text_NumberMarker[];
__declspec(noinline) INT ExtractNumberMarker_11960(TCHAR *Str)
{
    TCHAR *Marker = wcsstr(Str, Text_NumberMarker);
    INT Result = 0;
    if (Marker) {
        *Marker = 0;
        Marker += 2;
        TCHAR *Close = wcschr(Marker, ')');
        *Close = 0;
        Result = _wtoi(Marker);
        Close++;
        appMemmove(Marker - 2, Close, (appStrlen(Close) + 1) * sizeof(TCHAR));
    }
    return Result;
}

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(class UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(FName &N);
};

// FString from Unreal Engine 2 (only what the compile helpers below use).
extern TCHAR GEmptyString[];            // 0x10c10928, TEXT("") in writable data
class FString : public FArray
{
public:
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : GEmptyString; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};
extern TCHAR TagTArray[];               // 0x10c10974, TEXT("TArray") in writable data
template<class T> class TShrinkArray : public TArray<T>
{
public:
    void Shrink()
    {
        if (this->ArrayMax != this->ArrayNum) {
            this->ArrayMax = this->ArrayNum;
            this->Data = GMalloc->Realloc(this->Data, this->ArrayMax * sizeof(T), TagTArray);
        }
    }
};

// Retail walks a linked list of objects reachable from the viewport's actor.
struct FUnnamedNode_fd0c0
{
    char Pad00[0x2c];
    FUnnamedNode_fd0c0 *Next;           // +0x2c
    DWORD Flags;                        // +0x34
};
class AActor
{
public:
    char Pad00[0x24];
    FUnnamedNode_fd0c0 *FirstNode;      // +0x24 (neutral name)
};
class UViewport
{
public:
    char Pad00[0x30];
    AActor *Actor;                      // +0x30
};

// The base classes up to the vtable slots UInput overrides or calls.
class USubsystem
{
public:
    virtual void VSlot0(); virtual void VSlot1(); virtual void VSlot2(); virtual void VSlot3();
    virtual void VSlot4(); virtual void VSlot5(); virtual void VSlot6(); virtual void VSlot7();
    virtual void VSlot8(); virtual void VSlot9();
    virtual void Serialize(FArchive &Ar);       // slot 10, retail 0x10915f50
    virtual void VSlot11(); virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14();
    virtual void VSlot15(); virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18();
    virtual void VSlot19(); virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22();
    virtual void Init(UViewport *InViewport);   // slot 23
    virtual void VSlot24(); virtual void VSlot25(); virtual void VSlot26(); virtual void VSlot27();
    virtual void ResetInput();                  // slot 28
};

// One 16-byte alias slot: the alias name and its command text.
struct FInputAlias
{
    FName Alias;
    FString Command;
};

struct FInputCommand;                   // compiled command (opaque here)

class UInput : public USubsystem
{
public:
    char Pad04[0x28];                                       // UObject/USubsystem fields
    FInputAlias Aliases[20];                                // +0x2c
    FString Bindings[255];                                  // +0x16c, one per key
    UViewport *Viewport;                                    // +0xd60
    FName CurrentName;                                      // +0xd64 (neutral name)
    char PadD68[0xe74 - 0xd68];
    TShrinkArray<FInputCommand *> CompiledBindings[255];    // +0xe74
    TShrinkArray<FInputCommand *> CompiledAliases[20];      // +0x1a68
    UBOOL AliasesCompiled;                                  // +0x1b58

    UInput() {}
    UBOOL FindAliasIndex(FName Name, INT *Index);
    void Serialize(FArchive &Ar);
    void Init(UViewport *InViewport);
    UBOOL FindAlias(const TCHAR *Str, INT *Index);
    void BuildKeyMaps();                                    // retail 0x109fd0c0
    void CompileAliases();                                  // retail 0x109fd2f0
    void CompileBindings();                                 // retail 0x109fd3b0
    void CompileCommand(const TCHAR *Text, TShrinkArray<FInputCommand *> &Out, UBOOL IsBinding);  // retail 0x109fd500
};

// RVA 0xfe0c0
UBOOL UInput::FindAliasIndex(FName Name, INT *Index)
{
    if (Name.GetIndex() != 0) {
        for (DWORD i = 0; i < 20; i++) {
            if (Aliases[i].Alias.Index == Name.Index) {
                *Index = i;
                return 1;
            }
        }
    }
    return 0;
}

// RVA 0xfe0f0 (UInput vtable slot 10)
void UInput::Serialize(FArchive &Ar)
{
    USubsystem::Serialize(Ar);
    Ar << CurrentName;
}

// RVA 0xfe020 (LTCG: this on the stack, ret 0xc)
UBOOL UInput::FindAlias(const TCHAR *Str, INT *Index)
{
    TCHAR Copy[128];
    TCHAR Token[64];
    appStrcpy(Copy, Str);
    if (ParseToken(Str, Token, 64, 0)) {
        ExtractNumberMarker_11960(Token);
        FName Name(Token, FNAME_Add);
        return FindAliasIndex(Name, Index);
    }
    return 0;
}

// ---- TMap<FName,INT> lookups (two global maps built by retail 0xfd0c0) ----
inline DWORD GetTypeHash(const FName N) { return N.GetIndex(); }
template<class TK, class TV> class TMap
{
public:
    struct TPair
    {
        INT HashNext;
        TK Key;
        TV Value;
    };
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;
    // Retail 0x109fef20 (this in EDX, &Key in EAX); not inlined in retail.
    __declspec(noinline) TV FindRef(const TK &Key)
    {
        for (INT i = Hash[(GetTypeHash(Key) & (HashCount - 1))]; i != -1; ) {
            TPair &Pair = Pairs(i);
            if (Pair.Key == Key)
                return Pair.Value;
            i = Pair.HashNext;
        }
        return 0;
    }
};
extern TMap<FName, INT> *GUnnamedMap_c92400;     // 0x10c92400 (neutral name)
extern TMap<FName, INT> *GUnnamedMap_c92404;     // 0x10c92404 (neutral name)

// RVA 0xfe120
INT UnnamedLookupA_fe120(FName Key)
{
    if (Key != 0)
        return GUnnamedMap_c92400->FindRef(Key);
    return 0;
}

// RVA 0xfe140
INT UnnamedLookupB_fe140(FName Key)
{
    if (Key != 0)
        return GUnnamedMap_c92404->FindRef(Key);
    return 0;
}

// ---- UInput::Init and the helpers it calls ----
// Retail 0x10c92408: set once the key maps exist (a function-local static).
extern UBOOL UInput_Init_KeyMapsBuilt;
void AddKeyMapEntry(FUnnamedNode_fd0c0 *Node);    // stands in for retail 0x109feee0

// Retail 0x109fd0c0 (LTCG, this on the stack); simplified, defined only for
// its link convention.
__declspec(noinline) void UInput::BuildKeyMaps()
{
    if (!GUnnamedMap_c92400)
        GUnnamedMap_c92400 = (TMap<FName, INT> *)GMalloc->Malloc(sizeof(TMap<FName, INT>), TagTArray);
    if (!GUnnamedMap_c92404)
        GUnnamedMap_c92404 = (TMap<FName, INT> *)GMalloc->Malloc(sizeof(TMap<FName, INT>), TagTArray);
    for (FUnnamedNode_fd0c0 *Node = Viewport->Actor->FirstNode; Node; Node = Node->Next)
        if (Node->Flags & 4)
            AddKeyMapEntry(Node);
}

// Retail 0x109fd2f0 (LTCG, this on the stack).
__declspec(noinline) void UInput::CompileAliases()
{
    if (AliasesCompiled)
        return;
    for (INT i = 0; i < 20; i++) {
        if (Aliases[i].Alias != 0) {
            CompileCommand(*Aliases[i].Command, CompiledAliases[i], 0);
            Aliases[i].Command.Empty();
            CompiledAliases[i].Shrink();
        }
    }
    AliasesCompiled = 1;
}

// Retail 0x109fd3b0 (LTCG, this in EBX).
__declspec(noinline) void UInput::CompileBindings()
{
    for (INT i = 0; i < 255; i++) {
        if (Bindings[i].Len()) {
            CompileCommand(*Bindings[i], CompiledBindings[i], 1);
            CompiledBindings[i].Shrink();
        }
    }
}

// RVA 0xfe160 (UInput vtable slot 23)
void UInput::Init(UViewport *InViewport)
{
    Viewport = InViewport;
    if (InViewport && InViewport->Actor) {
        if (!UInput_Init_KeyMapsBuilt) {
            BuildKeyMaps();
            UInput_Init_KeyMapsBuilt = 1;
        }
        ResetInput();
        if (!AliasesCompiled)
            CompileAliases();
        CompileBindings();
    }
}

// ---- Scaffolding for the LTCG link, not part of the unit. ----
void Escape(void *);
UBOOL Driver_fe020(UInput *Input, const TCHAR *Str, INT *Index, TCHAR *Buf, INT Len, UBOOL Esc, EFindName Find)
{
    Escape(&FName_Names); Escape(&FName_Available); Escape(FName_NameHash); Escape(&GMalloc);
    Escape((void *)ParseToken(Str, Buf, Len, Esc));
    FName N(Buf, Find);
    Escape(&N);
    return Input->FindAlias(Str, Index);
}
void Driver_fe120(INT *Out, FName A, FName B)
{
    Escape(&GUnnamedMap_c92400); Escape(&GUnnamedMap_c92404);
    Escape((void *)UnnamedLookupA_fe120); Escape((void *)UnnamedLookupB_fe140);
    Out[0] = UnnamedLookupA_fe120(A);
    Out[1] = UnnamedLookupB_fe140(B);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_fe160(void *Mem, UViewport *V)
{
    Escape(&UInput_Init_KeyMapsBuilt); Escape(&GUnnamedMap_c92400); Escape(&GUnnamedMap_c92404); Escape(&GMalloc);
    UInput *Input = new(Mem) UInput;
    Escape(Input);
    Input->Init(V);
}
