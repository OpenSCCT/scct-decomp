// Work item 0079: Versus RVA 0x140e0-0x1433c.
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef unsigned long DWORD;

// Neutral names: subsystem objects reached through globals; only the
// vtable slots used here are known.
class UnnamedSubsystem_c946c0
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Exit();                       // +0x3c
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50();
    virtual void Destroy(INT Flags);           // +0x54 (scalar deleting destructor)
};
class UnnamedService_c71ab4
{
public:
    virtual void Slot00();
    virtual void Shutdown();                   // +0x04
};
extern UnnamedSubsystem_c946c0 *GUnnamedSubsystem_c946c0;
extern UnnamedService_c71ab4 *GUnnamedService_c71ab4;
void UnnamedExit_13dc0();
void UnnamedExit_3b3b0();

// RVA 0x140e0
void UnnamedShutdown_140e0()
{
    UnnamedExit_13dc0();
    if (GUnnamedSubsystem_c946c0) {
        GUnnamedSubsystem_c946c0->Exit();
        if (GUnnamedSubsystem_c946c0)
            GUnnamedSubsystem_c946c0->Destroy(1);
        GUnnamedSubsystem_c946c0 = 0;
    }
    GUnnamedService_c71ab4->Shutdown();
    UnnamedExit_3b3b0();
}

// Rotating static string buffers (appStaticString1024 style).
extern TCHAR GStaticStrings[256][1024];
extern DWORD GStaticStringIndex;

inline TCHAR *appStaticString1024()
{
    TCHAR *Result = GStaticStrings[GStaticStringIndex++ & 0xff];
    Result[0] = 0;
    return Result;
}

// RVA 0x14120: TCHAR -> ANSI, non-Latin-1 characters become 0x7f.
ANSICHAR *appToAnsi(const TCHAR *Str, ANSICHAR *ACh)
{
    if (!Str)
        return 0;
    ANSICHAR *UserBuffer = ACh;
    if (!ACh)
        ACh = (ANSICHAR *)appStaticString1024();
    INT i;
    for (i = 0; (UserBuffer || i < 1023) && Str[i]; i++)
        ACh[i] = (ANSICHAR)(Str[i] < 0x100 ? Str[i] : 0x7f);
    ACh[i] = 0;
    return ACh;
}

// RVA 0x141a0: ANSI -> TCHAR (LTCG: Str in ESI, UCh in EAX).
TCHAR *appFromAnsi(const ANSICHAR *Str, TCHAR *UCh)
{
    if (!Str)
        return 0;
    TCHAR *UserBuffer = UCh;
    if (!UCh)
        UCh = appStaticString1024();
    INT i;
    for (i = 0; (UserBuffer || i < 1023) && Str[i]; i++)
        UCh[i] = (unsigned char)Str[i];
    UCh[i] = 0;
    return UCh;
}

// ---- TMap<FString,FString> ----
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
DWORD appStrihash(const TCHAR *Data);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Num() const { return ArrayNum; }
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
        }
    }
};

class FString : public FArray
{
public:
    const TCHAR *operator*() const { return Num() ? (const TCHAR *)Data : L""; }
};

struct TPair
{
    INT HashNext;
    FString Key;
    FString Value;
};

class FStringMap
{
public:
    FArray Pairs;      // TArray<TPair>
    INT *Hash;
    INT HashCount;

    FStringMap();
    void Rehash();
    void Shrink();
    FString *Find(const FString &Key);
    TPair *PairData() const { return (TPair *)Pairs.Data; }
};

// RVA 0x14200
FStringMap::FStringMap()
    : Hash(0), HashCount(8)
{
    Rehash();
}

// RVA 0x14250
void FStringMap::Shrink()
{
    Pairs.Shrink(sizeof(TPair));
    while (HashCount > Pairs.Num() * 2 + 8)
        HashCount /= 2;
    Rehash();
}

// RVA 0x142b0
FString *FStringMap::Find(const FString &Key)
{
    for (INT i = Hash[appStrihash(*Key) & (HashCount - 1)]; i != -1; i = PairData()[i].HashNext) {
        const FString &PairKey = PairData()[i].Key;
        if (_wcsicmp(*PairKey, *Key) == 0)
            return &PairData()[i].Value;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit: retail 0xf6b0
// (appStrihash) and 0x14850 (Rehash) are defined here, unverified, only so
// the LTCG linker gives them their retail register conventions.
extern DWORD GCRCTable[256];
TCHAR appToUpper(TCHAR c);
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data) {
        TCHAR Ch = appToUpper(*Data++);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ (Ch & 0xff)) & 0xff];
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ (Ch >> 8)) & 0xff];
    }
    return Hash;
}
void FStringMap::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++) {
        TPair &Pair = PairData()[i];
        INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}

void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_141a0(const ANSICHAR *S, TCHAR *U) { Escape(&GStaticStringIndex); Escape(appFromAnsi(S, U)); }
void Driver_14200(void *Mem) { Escape(new(Mem) FStringMap); }
void Driver_14250(FStringMap *M) { Escape(&GMalloc); M->Shrink(); }
void Driver_142b0(FStringMap *M, const FString *K) { Escape(M->Find(*K)); }
void Driver_14120(const TCHAR *S, ANSICHAR *A) { Escape(&GStaticStringIndex); Escape((void *)&appToAnsi); Escape(appToAnsi(S, A)); }
