// Work item 0064 (LTCG retry): FConfigCacheIni, Versus RVA 0x10540 and 0x10770.
// 0x10540 is FConfigCacheIni::Find(const TCHAR* InFilename, UBOOL
// CreateIfNotFound) with SCCT's platform subdirectory lookup (PSX2\, XBOX\,
// _PC_\); 0x10770 is FConfigCacheIni::Flush(UBOOL Read, const TCHAR* Filename)
// (UE2 Core FConfigCache.h). FConfigCacheIni derives from FConfigCache
// (vtable at +0) and TMap<FString,FConfigFile> (at +4).
// The unit was built with /GL and linked with /LTCG, so the callees that live
// in the same unit got custom conventions; they are written out below (marked
// noinline) so the linker sees their callers and makes the same choices.
// Status: Flush (0x10770) matches with root ?Driver_10770@@YAXXZ, /O2 /Gy /GX.
// TMapBase::Find (0x146f0) and appStrihash (0xf6b0) also match as written.
// FConfigCacheIni::Find (0x10540) does not yet: the linker gives TMapBase::Set
// `this` on the stack instead of retail's EDI (value in EAX), which changes
// the register allocation of the whole function.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscat(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FFileManager
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual INT FileSize(const TCHAR *Filename);
};
extern FFileManager *GFileManager;

// Unnamed global at 0x10c946cc; field 0x68 selects the target platform
// (1 PSX2, 2 XBOX, 3 PC).
struct UnnamedPlatformInfo_c946cc
{
    char Pad[0x68];
    INT Platform;
};
extern UnnamedPlatformInfo_c946cc *GPlatformInfo;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In); // 0x46c0
    FString(const FString &Other); // 0x4640
    ~FString();               // 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
    UBOOL operator==(const TCHAR *Other) const { return _wcsicmp(**this, Other) == 0; }
    UBOOL operator==(const FString &Other) const { return _wcsicmp(**this, *Other) == 0; }
};

// 0xf6b0: UE2 appStrihash (case-insensitive CRC of a string).
extern DWORD GCRCTable[256];
inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}

// Out-of-unit helpers used by the bodies of the in-unit callees below.
void EmptySectionPairs(void *Pairs, INT Slack);
void CopySectionPair(void *Dest, const void *Src);
void ConstructPair(void *Dest, const TCHAR *Key, const void *Value);
void RehashSectionTable(void *Section);
UBOOL ConfigFileLoad(void *File, const FString &Name);
void ConfigFileSave(void *File, const FString &Name);
INT MapRemoveKey(void *Map, const FString &Key);

// TArray storage (UE2 FArray layout).
class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize); // 0x44e0
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// TMultiMap<FString,FString>::TPair (0x24 bytes; the value part at +0x10 is
// an SCCT type copied out of unit).
struct FSectionValue
{
    FSectionValue(const FSectionValue &Other); // 0x150a0
    ~FSectionValue();
    char Pad[0x14];
};
struct FSectionPair
{
    INT HashNext;
    FString Key;
    FSectionValue Value;
    __declspec(noinline) FSectionPair(const FSectionPair &Other) // 0x15250
        : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value)
    {
    }
    __declspec(noinline) ~FSectionPair() {} // 0x14e50
};
inline void *operator new(unsigned int, void *Mem) { return Mem; }

// TArray<FSectionPair>.
class FSectionPairs : public FArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize); // 0x4550 (Empty's storage reset)
    __declspec(noinline) void Empty(INT Slack) // 0x14bd0
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&((FSectionPair *)Data)[i])->~FSectionPair();
        Reset(sizeof(FSectionPair), Slack);
    }
    void Reset(INT ElementSize, INT Slack);
    __declspec(noinline) FSectionPairs &operator=(const FSectionPairs &Other) // 0x15190
    {
        if (this != &Other)
        {
            Empty(Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new ((FSectionPair *)Data + Add(1, sizeof(FSectionPair))) FSectionPair(((FSectionPair *)Other.Data)[i]);
        }
        return *this;
    }
};

// TMultiMap<FString,FString>: pair array, hash table, hash size.
class FConfigSection
{
public:
    __declspec(noinline) FConfigSection() : Hash(0), HashCount(8) { Rehash(); } // 0x14340
    __declspec(noinline) ~FConfigSection() // 0x103a0
    {
        if (Hash)
            GMalloc->Free(Hash);
        Hash = 0;
        HashCount = 0;
    }
    FConfigSection &operator=(const FConfigSection &Other)
    {
        Pairs = Other.Pairs;
        HashCount = Other.HashCount;
        Rehash();
        return *this;
    }
    __declspec(noinline) void Rehash() { RehashSectionTable(this); } // 0x14a30
    FSectionPairs Pairs;
    INT *Hash;
    INT HashCount;
};

class FConfigFile : public FConfigSection
{
public:
    UBOOL Dirty;
    UBOOL NoSave;
    UBOOL Quotes;
    FConfigFile() : Dirty(0), NoSave(0), Quotes(0) {}
    __declspec(noinline) UBOOL Read(const TCHAR *Filename) // 0xfb40
    {
        FString Name(Filename);
        return ConfigFileLoad(this, Name);
    }
    __declspec(noinline) void Write(const TCHAR *Filename) // 0x100e0
    {
        FString Name(Filename);
        ConfigFileSave(this, Name);
    }
};

struct TPair
{
    INT HashNext;
    FString Key;
    FConfigFile Value;
    __declspec(noinline) ~TPair() {} // 0x14ea0
};

class TMapBase
{
public:
    TPair *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT *Hash;
    INT HashCount;

    __declspec(noinline) FConfigFile *Find(const FString &Key) // 0x146f0
    {
        for (INT i = Hash[appStrihash(*Key) & (HashCount - 1)]; i != -1; i = Data[i].HashNext)
            if (Data[i].Key == Key)
                return &Data[i].Value;
        return 0;
    }
    __declspec(noinline) FConfigFile &Add(const TCHAR *Key, const FConfigFile &Value) // 0x14cc0
    {
        TPair *Pair = (TPair *)((FArray *)this)->Add(1, sizeof(TPair));
        Pair = &Data[(INT)Pair];
        if (Pair)
        {
            ConstructPair(Pair, Key, &Value);
        }
        INT iHash = appStrihash(*Pair->Key) & (HashCount - 1);
        Pair->HashNext = Hash[iHash];
        Hash[iHash] = ArrayNum - 1;
        if (HashCount * 2 + 8 < ArrayNum)
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair->Value;
    }
    __declspec(noinline) FConfigFile &Set(const TCHAR *Key, const FConfigFile &Value) // 0x14570
    {
        for (INT i = Hash[appStrihash(Key) & (HashCount - 1)]; i != -1; i = Data[i].HashNext)
            if (Data[i].Key == Key)
            {
                Data[i].Value = Value;
                return Data[i].Value;
            }
        return Add(Key, Value);
    }
    __declspec(noinline) void Rehash() // 0x14c10
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), 0);
        for (INT i = 0; i < HashCount; i++)
            NewHash[i] = -1;
        if (Hash)
            GMalloc->Free(Hash);
        Hash = NewHash;
    }
    __declspec(noinline) INT Remove(const TCHAR *Key) // 0x14610
    {
        FString K(Key);
        return MapRemoveKey(this, K);
    }
    __forceinline void Empty()
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&Data[i])->~TPair();
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
        HashCount = 8;
        Rehash();
    }

    class TIterator
    {
    public:
        TIterator(TMapBase &InMap) : Map(InMap), Index(0) {}
        operator UBOOL() const { return Index < Map.ArrayNum; }
        void operator++() { ++Index; }
        FString &Key() const { return Map.Data[Index].Key; }
        FConfigFile &Value() const { return Map.Data[Index].Value; }
    private:
        TMapBase &Map;
        INT Index;
    };
};

class FConfigCache
{
public:
    virtual void Dummy0();
};

class FConfigCacheIni : public FConfigCache, public TMapBase
{
public:
    FString SystemIni; // 0x18
    FString UserIni;   // 0x24
    FConfigFile *Find(const TCHAR *InFilename, UBOOL CreateIfNotFound);
    void Flush(UBOOL Read, const TCHAR *Filename);
};

FConfigFile *FConfigCacheIni::Find(const TCHAR *InFilename, UBOOL CreateIfNotFound)
{
    // If filename not specified, use default.
    TCHAR Filename[256];
    wcscpy(Filename, InFilename ? InFilename : *SystemIni);

    // Add .ini extension.
    INT Len = wcslen(Filename);
    if (Len < 5 || (Filename[Len - 4] != '.' && Filename[Len - 5] != '.'))
        wcscat(Filename, L".ini");

    // Automatically translate generic filenames.
    if (_wcsicmp(Filename, L"User.ini") == 0)
        wcscpy(Filename, *UserIni);
    else if (_wcsicmp(Filename, L"System.ini") == 0)
        wcscpy(Filename, *SystemIni);

    // Prefer the platform's own copy of the file when it exists.
    if (GPlatformInfo)
    {
        TCHAR PlatformFilename[256];
        switch (GPlatformInfo->Platform)
        {
        case 1: wcscpy(PlatformFilename, L"PSX2\\"); break;
        case 2: wcscpy(PlatformFilename, L"XBOX\\"); break;
        case 3: wcscpy(PlatformFilename, L"_PC_\\"); break;
        default: wcscpy(PlatformFilename, EmptyString); break;
        }
        wcscat(PlatformFilename, Filename);
        if (GFileManager->FileSize(PlatformFilename) >= 0)
            wcscpy(Filename, PlatformFilename);
    }

    // Get file.
    FConfigFile *Result = TMapBase::Find(FString(Filename));
    if (!Result && (CreateIfNotFound || GFileManager->FileSize(Filename) >= 0))
    {
        Result = &Set(Filename, FConfigFile());
        Result->Read(Filename);
    }
    return Result;
}

void FConfigCacheIni::Flush(UBOOL Read, const TCHAR *Filename)
{
    for (TIterator It(*(TMapBase *)this); It; ++It)
    {
        FString &Key = It.Key();
        if (!Filename || _wcsicmp(*Key, Filename) == 0)
        {
            FConfigFile &File = It.Value();
            File.Write(*Key);
        }
    }
    if (Read)
    {
        if (Filename)
            Remove(Filename);
        else
            Empty();
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Retail reaches Flush through the FConfigCache vtable, so its address is taken.
void EscapeFlush(void (FConfigCacheIni::*)(UBOOL, const TCHAR *));
void EscapeFind(FConfigFile *(FConfigCacheIni::*)(const TCHAR *, UBOOL));
void Driver_10540()
{
    Escape(&GMalloc);
    Escape(&GFileManager);
    Escape(&GPlatformInfo);
    EscapeFind(&FConfigCacheIni::Find);
}
void Driver_10770()
{
    Escape(&GMalloc);
    EscapeFlush(&FConfigCacheIni::Flush);
}
