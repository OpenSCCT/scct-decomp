// Work item 0062 (LTCG retry): Versus RVA 0xf820-0xfd4a. FString helpers and
// the INI text parser of FConfigFile. All link-time optimised (/GL + /LTCG).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr(const TCHAR*, const TCHAR*);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR*);

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;

    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR* In);                 // RVA 0x46c0
    FString(INT InCount, const TCHAR* InSrc); // RVA 0x4af0
    ~FString();                               // RVA 0x48b0
    INT Num() const { return ArrayNum; }
    INT Len() const { return Num() ? Num() - 1 : 0; }
    const TCHAR& operator()(INT i) const { return Data[i]; }
    const TCHAR* operator*() const { return Num() ? Data : EmptyString; }

    FString Mid(INT Start, INT Count) const;
    INT InStr(const TCHAR* SubStr, UBOOL Right) const;
};

// RVA 0xf820
FString FString::Mid(INT Start, INT Count) const
{
    DWORD End = Start + Count;
    Start = Clamp((DWORD)Start, (DWORD)0, (DWORD)Len());
    End = Clamp((DWORD)End, (DWORD)Start, (DWORD)Len());
    return FString(End - Start, **this + Start);
}

// RVA 0xf890
INT FString::InStr(const TCHAR* SubStr, UBOOL Right) const
{
    if (!Right)
    {
        TCHAR* Tmp = wcsstr(**this, SubStr);
        return Tmp ? (Tmp - **this) : -1;
    }
    else
    {
        for (INT i = Len() - 1; i >= 0; i--)
        {
            INT j;
            for (j = 0; SubStr[j]; j++)
                if ((*this)(i + j) != SubStr[j])
                    break;
            if (!SubStr[j])
                return i;
        }
        return -1;
    }
}

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);      // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);   // RVA 0x4550
    void Shrink(INT ElementSize);
};

class FFileManager;
extern FFileManager* GFileManager;            // 0x10c71ab4
UBOOL appLoadFileToString(FString& Result, const TCHAR* Filename, FFileManager* FileManager = GFileManager); // RVA 0x12b10
INT appParseConfigLine(TCHAR* Str);           // RVA 0x11960

// TArray<TPair> of FConfigSection (0x1c-byte pairs).
class FSectionPairArray : public FArray
{
public:
    FSectionPairArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~FSectionPairArray();                     // RVA 0x14980
};

// FConfigSection: TMultiMap<FString,FString> (pairs of 0x1c bytes).
class FConfigSection
{
public:
    FSectionPairArray Pairs;
    INT* Hash;
    INT HashCount;
    FConfigSection();
    ~FConfigSection();                        // RVA 0x9ab0d0
    void Rehash();                            // RVA 0x14850
    void Shrink();                            // RVA 0x14250
    FString& Add(const TCHAR* InKey, const TCHAR* InValue); // RVA 0x14900
};

// TMap<FString,FConfigSection> pair (0x24 bytes).
struct FConfigPair
{
    INT HashNext;
    FString Key;
    FConfigSection Value;
};

class FConfigPairArray : public FArray
{
public:
    void Empty(INT Slack);                    // RVA 0x14bd0
    static void DestructPair(FConfigPair* Pair); // RVA 0x14e50
};

class FConfigFile
{
public:
    FConfigPairArray Pairs;
    INT* Hash;
    INT HashCount;

    void Rehash();                            // RVA 0x14a30
    void Empty(INT Slack = 0)
    {
        Pairs.Empty(Slack);
        HashCount = 8;
        Rehash();
    }
    void Shrink();                            // RVA 0x14390
    FConfigSection* Find(const FString& Key);                            // RVA 0x14480
    FConfigSection& Set(const TCHAR* InKey, const FConfigSection& Value); // RVA 0x143f0

    void ProcessInputFileContents(FString& Contents);
    void Read(const TCHAR* Filename);
};

// RVA 0x14200. Not marked inline: the linker expands it into 0xf930 at /Ob2,
// while 0xfb40 calls it, which reproduces only when built with /Ob1.
FConfigSection::FConfigSection()
:   Hash(0), HashCount(8)
{
    Rehash();
}

extern const TCHAR ConfigEquals[];            // 0x10c74ab4, TEXT("=")

// RVA 0xf930
void FConfigFile::ProcessInputFileContents(FString& Contents)
{
    Empty();
    TCHAR* Ptr = (TCHAR*)*Contents;
    FConfigSection* CurrentSection = 0;
    UBOOL Done = 0;
    while (!Done)
    {
        while (*Ptr == '\r' || *Ptr == '\n')
            Ptr++;
        TCHAR* Start = Ptr;
        while (*Ptr && *Ptr != '\r' && *Ptr != '\n')
            Ptr++;
        if (*Ptr == 0)
            Done = 1;
        *Ptr++ = 0;
        if (*Start == '[' && Start[wcslen(Start) - 1] == ']')
        {
            Start++;
            Start[wcslen(Start) - 1] = 0;
            appParseConfigLine(Start);
            appParseConfigLine(Start);
            if (CurrentSection)
                CurrentSection->Shrink();
            CurrentSection = Find(Start);
            if (!CurrentSection)
            {
                FConfigSection NewSection;
                CurrentSection = &Set(Start, NewSection);
            }
        }
        else if (CurrentSection && *Start)
        {
            TCHAR* Value = wcsstr(Start, ConfigEquals);
            if (Value)
            {
                *Value++ = 0;
                appParseConfigLine(Start);
                appParseConfigLine(Start);
                if (*Value == '\"' && Value[wcslen(Value) - 1] == '\"')
                {
                    Value++;
                    Value[wcslen(Value) - 1] = 0;
                }
                CurrentSection->Add(Start, Value);
            }
        }
    }
    CurrentSection->Shrink();
    Shrink();
}

// RVA 0xfb40
void FConfigFile::Read(const TCHAR* Filename)
{
    Empty();
    FString Text;
    if (appLoadFileToString(Text, Filename))
    {
        TCHAR* Ptr = (TCHAR*)*Text;
        FConfigSection* CurrentSection = 0;
        UBOOL Done = 0;
        while (!Done)
        {
            while (*Ptr == '\r' || *Ptr == '\n')
                Ptr++;
            TCHAR* Start = Ptr;
            while (*Ptr && *Ptr != '\r' && *Ptr != '\n')
                Ptr++;
            if (*Ptr == 0)
                Done = 1;
            *Ptr++ = 0;
            if (*Start == '[' && Start[wcslen(Start) - 1] == ']')
            {
                Start++;
                Start[wcslen(Start) - 1] = 0;
                appParseConfigLine(Start);
                appParseConfigLine(Start);
                CurrentSection = Find(Start);
                if (!CurrentSection)
                {
                    FConfigSection NewSection;
                    CurrentSection = &Set(Start, NewSection);
                }
            }
            else if (CurrentSection && *Start)
            {
                TCHAR* Value = wcsstr(Start, ConfigEquals);
                if (Value)
                {
                    *Value++ = 0;
                    appParseConfigLine(Start);
                    appParseConfigLine(Start);
                    if (*Value == '\"' && Value[wcslen(Value) - 1] == '\"')
                    {
                        Value++;
                        Value[wcslen(Value) - 1] = 0;
                    }
                    CurrentSection->Add(Start, Value);
                }
            }
        }
    }
}

// Scaffolding for the link, not part of the unit. The bodies below stand in
// for callees in other units of the same LTCG module; they are defined only so
// the linker gives them retail's register conventions.
void Escape(void*);
void* Alloc(INT);
TCHAR* appStrncpy(TCHAR*, const TCHAR*, INT);
DWORD appStrihash(const TCHAR* Data);
extern "C" __declspec(dllimport) TCHAR* __cdecl wcschr(const TCHAR*, TCHAR);
extern "C" __declspec(dllimport) INT __cdecl _wtoi(const TCHAR*);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR*, const TCHAR*);
extern const TCHAR ConfigParseTag[];          // 0x10c71080
class FOutputDevice;
extern FOutputDevice* GNull;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual INT TotalSize();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19();
    virtual UBOOL Close();
};
class FFileManager
{
public:
    virtual void s0(); virtual void s1();
    virtual FArchive* CreateFileReader(const TCHAR* Filename, DWORD Flags, FOutputDevice* Error);
};
class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;
extern DWORD GCRCTable[256];                  // 0x10c78cd0
inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c - ('a' - 'A')); }
#pragma auto_inline(off)
DWORD appStrihash(const TCHAR* Data)          // RVA 0xf6b0
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        unsigned short B = Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = Ch >> 8;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
FString::FString(INT InCount, const TCHAR* InSrc)
{
    ArrayNum = ArrayMax = InCount ? InCount + 1 : 0;
    Data = (TCHAR*)Alloc(ArrayMax * 2);
    if (ArrayNum)
        appStrncpy(Data, InSrc, InCount + 1);
}
INT appParseConfigLine(TCHAR* Str)
{
    TCHAR* Tag = wcsstr(Str, ConfigParseTag);
    if (!Tag)
        return 0;
    *Tag = 0;
    Tag += 2;
    TCHAR* End = wcschr(Tag, ')');
    *End = 0;
    INT Result = _wtoi(Tag);
    End++;
    memmove(Tag - 2, End, wcslen(End) * 2 + 2);
    return Result;
}
UBOOL appLoadFileToString(FString& Result, const TCHAR* Filename, FFileManager* FileManager)
{
    FArchive* Reader = FileManager->CreateFileReader(Filename, 0, GNull);
    if (!Reader)
        return 0;
    INT Size = Reader->TotalSize();
    char* Ch = (char*)GMalloc->Malloc(Size + 2, L"");
    Reader->Serialize(Ch, Size);
    UBOOL Success = Reader->Close();
    delete Reader;
    Ch[Size] = 0;
    Ch[Size + 1] = 0;
    Result.ArrayNum = 0;
    if (Result.Data) { GMalloc->Free(Result.Data); Result.Data = 0; Result.ArrayMax = 0; }
    if (Size >= 2 && !(Size & 1) && (unsigned char)Ch[0] == 0xff && (unsigned char)Ch[1] == 0xfe)
    {
        Result.ArrayNum = Result.ArrayMax = Size / 2;
        Result.Data = (TCHAR*)GMalloc->Malloc(Size, L"");
        for (INT i = 0; i < Size / 2 - 1; i++)
            Result.Data[i] = ((TCHAR*)Ch)[i + 1];
    }
    else
    {
        Result.ArrayNum = Result.ArrayMax = Size + 1;
        Result.Data = (TCHAR*)GMalloc->Malloc(Size * 2 + 2, L"");
        for (INT i = 0; i < Size; i++)
            Result.Data[i] = (unsigned char)Ch[i];
        Result.Data[Size] = 0;
    }
    GMalloc->Free(Ch);
    return Success;
}
struct FSectionPair
{
    INT HashNext;
    FString Key;
    FString Value;
};
void FConfigSection::Rehash()
{
    INT* NewHash = (INT*)GMalloc->Malloc(HashCount * sizeof(INT), L"");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        FSectionPair& Pair = ((FSectionPair*)Pairs.Data)[i];
        INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
void FConfigFile::Rehash()
{
    INT* NewHash = (INT*)GMalloc->Malloc(HashCount * sizeof(INT), L"");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        FConfigPair& Pair = ((FConfigPair*)Pairs.Data)[i];
        INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
FConfigSection::~FConfigSection()
{
    if (Hash)
        GMalloc->Free(Hash);
    Hash = 0;
    HashCount = 0;
}
void FConfigPairArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        DestructPair(&((FConfigPair*)Data)[i]);
    FArray::Empty(sizeof(FConfigPair), Slack);
}
void FConfigPairArray::DestructPair(FConfigPair* Pair)
{
    Pair->Value.~FConfigSection();
    Pair->Key.~FString();
}
void FConfigSection::Shrink()
{
    Pairs.Shrink(0x1c);
    while (HashCount > Pairs.ArrayNum * 2 + 8)
        HashCount /= 2;
    Rehash();
}
void FConfigFile::Shrink()
{
    Pairs.Shrink(sizeof(FConfigPair));
    while (HashCount > Pairs.ArrayNum * 2 + 8)
        HashCount /= 2;
    Rehash();
}
FString& FConfigSection::Add(const TCHAR* InKey, const TCHAR* InValue)
{
    INT i = Pairs.Add(1, 0x1c);
    FString* P = (FString*)((char*)Pairs.Data + i * 0x1c + 4);
    INT h = appStrihash(InKey) & (HashCount - 1);
    Escape((void*)InValue);
    *(INT*)P = Hash[h];
    Hash[h] = Pairs.ArrayNum - 1;
    if (HashCount * 2 + 8 < Pairs.ArrayNum) { HashCount *= 2; Rehash(); }
    return P[1];
}
FConfigSection* FConfigFile::Find(const FString& Key)
{
    for (INT i = Hash[appStrihash(*Key) & (HashCount - 1)]; i != -1; i = ((FConfigPair*)Pairs.Data)[i].HashNext)
        if (_wcsicmp(*((FConfigPair*)Pairs.Data)[i].Key, *Key) == 0)
            return &((FConfigPair*)Pairs.Data)[i].Value;
    return 0;
}
FConfigSection& FConfigFile::Set(const TCHAR* InKey, const FConfigSection& Value)
{
    for (INT i = Hash[appStrihash(InKey) & (HashCount - 1)]; i != -1; i = ((FConfigPair*)Pairs.Data)[i].HashNext)
        if (_wcsicmp(*((FConfigPair*)Pairs.Data)[i].Key, InKey) == 0)
        {
            FConfigSection& S = ((FConfigPair*)Pairs.Data)[i].Value;
            S.HashCount = Value.HashCount;
            S.Rehash();
            return S;
        }
    Escape((void*)&Value);
    return ((FConfigPair*)Pairs.Data)[0].Value;
}
#pragma auto_inline(on)
FString Driver_f820(const FString* S, INT Start, INT Count)
{
    return S->Mid(Start, Count);
}
INT Driver_f890(const FString* S, const TCHAR* Sub, UBOOL Right)
{
    return S->InStr(Sub, Right);
}
void Driver_f930(FConfigFile* Config, FString* Contents)
{
    Config->ProcessInputFileContents(*Contents);
}
void Driver_fb40(FConfigFile* Config, const TCHAR* Filename)
{
    Escape(&GFileManager);
    Config->Read(Filename);
}
