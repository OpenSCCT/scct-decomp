// Work item 0055: Versus RVA 0x1331f0-0x13355b (Engine UnURL.cpp, FURL).
// 0x1331f0: FURL::StaticInit()
// 0x133390: FURL::StaticExit()
// 0x133420: operator<<(FArchive &, FURL &)
// 0x133490: FURL::FURL(const TCHAR *)

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FConfigCache {
public:
    virtual UBOOL GetBool(const TCHAR *Section, INT Unknown, const TCHAR *Key,
                          UBOOL &Value, const TCHAR *Filename = 0) = 0;
    virtual UBOOL GetInt(const TCHAR *Section, INT Unknown, const TCHAR *Key,
                         INT &Value, const TCHAR *Filename = 0) = 0;
    virtual UBOOL GetFloat(const TCHAR *Section, INT Unknown, const TCHAR *Key,
                           float &Value, const TCHAR *Filename = 0) = 0;
    virtual const TCHAR *GetStr(const TCHAR *Section, INT Unknown, const TCHAR *Key,
                                const TCHAR *Filename = 0) = 0;
};
extern FConfigCache *GConfig;

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(void *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;

    UBOOL IsLoading() const { return ArIsLoading; }
    FArchive &ByteOrderSerialize(void *V, INT Length)
    {
        Serialize(V, Length);
        return *this;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.ByteOrderSerialize(&I, sizeof(I));
        return Ar;
    }
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
};

template <class T> class TArray : public FArray {
public:
    TArray() : FArray() {}
    ~TArray();
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;

    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const TCHAR *Other);
};

FArchive &operator<<(FArchive &Ar, FString &S);
FArchive &operator<<(FArchive &Ar, TArray<FString> &A);

// String literals retail keeps in writable .data (distinct unpooled copies).
extern const TCHAR TEXT_URL_Protocol[];
extern const TCHAR TEXT_Protocol[];
extern const TCHAR TEXT_URL_ProtocolDescription[];
extern const TCHAR TEXT_ProtocolDescription[];
extern const TCHAR TEXT_URL_Name[];
extern const TCHAR TEXT_Name[];
extern const TCHAR TEXT_URL_Map[];
extern const TCHAR TEXT_Map[];
extern const TCHAR TEXT_URL_LocalMap[];
extern const TCHAR TEXT_LocalMap[];
extern const TCHAR TEXT_URL_Host[];
extern const TCHAR TEXT_Host[];
extern const TCHAR TEXT_URL_Portal[];
extern const TCHAR TEXT_Portal[];
extern const TCHAR TEXT_URL_MapExt[];
extern const TCHAR TEXT_MapExt[];
extern const TCHAR TEXT_URL_SaveExt[];
extern const TCHAR TEXT_SaveExt[];
extern const TCHAR TEXT_URL_Port[];
extern const TCHAR TEXT_Port[];

extern const TCHAR TEXT_Empty_DefaultProtocol[];
extern const TCHAR TEXT_Empty_DefaultProtocolDescription[];
extern const TCHAR TEXT_Empty_DefaultName[];
extern const TCHAR TEXT_Empty_DefaultMap[];
extern const TCHAR TEXT_Empty_DefaultLocalMap[];
extern const TCHAR TEXT_Empty_DefaultHost[];
extern const TCHAR TEXT_Empty_DefaultPortal[];
extern const TCHAR TEXT_Empty_DefaultMapExt[];
extern const TCHAR TEXT_Empty_DefaultSaveExt[];

class FURL {
public:
    FString Protocol;
    FString Host;
    INT Port;
    FString Map;
    TArray<FString> Op;
    FString Portal;
    INT Valid;

    static FString DefaultProtocol;
    static FString DefaultProtocolDescription;
    static FString DefaultName;
    static FString DefaultMap;
    static FString DefaultLocalMap;
    static FString DefaultHost;
    static FString DefaultPortal;
    static FString DefaultMapExt;
    static FString DefaultSaveExt;
    static INT DefaultPort;

    FURL(const TCHAR *LocalFilename = 0);
    static void StaticInit();
    static void StaticExit();
    friend FArchive &operator<<(FArchive &Ar, FURL &U);
};

// 0x1331f0: FURL::StaticInit
void FURL::StaticInit()
{
    const TCHAR *S;
    if ((S = GConfig->GetStr(TEXT_URL_Protocol, 0, TEXT_Protocol, 0)) != 0)
        DefaultProtocol = S;
    if ((S = GConfig->GetStr(TEXT_URL_ProtocolDescription, 0, TEXT_ProtocolDescription, 0)) != 0)
        DefaultProtocolDescription = S;
    if ((S = GConfig->GetStr(TEXT_URL_Name, 0, TEXT_Name, 0)) != 0)
        DefaultName = S;
    if ((S = GConfig->GetStr(TEXT_URL_Map, 0, TEXT_Map, 0)) != 0)
        DefaultMap = S;
    if ((S = GConfig->GetStr(TEXT_URL_LocalMap, 0, TEXT_LocalMap, 0)) != 0)
        DefaultLocalMap = S;
    if ((S = GConfig->GetStr(TEXT_URL_Host, 0, TEXT_Host, 0)) != 0)
        DefaultHost = S;
    if ((S = GConfig->GetStr(TEXT_URL_Portal, 0, TEXT_Portal, 0)) != 0)
        DefaultPortal = S;
    if ((S = GConfig->GetStr(TEXT_URL_MapExt, 0, TEXT_MapExt, 0)) != 0)
        DefaultMapExt = S;
    if ((S = GConfig->GetStr(TEXT_URL_SaveExt, 0, TEXT_SaveExt, 0)) != 0)
        DefaultSaveExt = S;
    GConfig->GetInt(TEXT_URL_Port, 0, TEXT_Port, DefaultPort, 0);
}

// 0x133390: FURL::StaticExit
void FURL::StaticExit()
{
    DefaultProtocol = TEXT_Empty_DefaultProtocol;
    DefaultProtocolDescription = TEXT_Empty_DefaultProtocolDescription;
    DefaultName = TEXT_Empty_DefaultName;
    DefaultMap = TEXT_Empty_DefaultMap;
    DefaultLocalMap = TEXT_Empty_DefaultLocalMap;
    DefaultHost = TEXT_Empty_DefaultHost;
    DefaultPortal = TEXT_Empty_DefaultPortal;
    DefaultMapExt = TEXT_Empty_DefaultMapExt;
    DefaultSaveExt = TEXT_Empty_DefaultSaveExt;
}

// 0x133420: operator<<(FArchive &, FURL &)
FArchive &operator<<(FArchive &Ar, FURL &U)
{
    Ar << U.Protocol << U.Host << U.Map << U.Portal << U.Op << U.Port << U.Valid;
    return Ar;
}

// 0x133490: FURL::FURL(const TCHAR *)
FURL::FURL(const TCHAR *LocalFilename)
    : Protocol(DefaultProtocol)
    , Host(DefaultHost)
    , Port(DefaultPort)
    , Map(LocalFilename ? FString(LocalFilename) : DefaultMap)
    , Op()
    , Portal(DefaultPortal)
    , Valid(1)
{
}

// ---------------------------------------------------------------------------
// Scaffolding for LTCG links, not part of the unit.
// ---------------------------------------------------------------------------

// Exact retail body of FString::operator=(const TCHAR *) (versus_ltcg1_item_9001.cpp).
__declspec(noinline) FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

class FCompactIndex {
public:
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

// 0x1ea40 (body approximated, not a match; defined so LINK /LTCG assigns its convention).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Original < 0 ? -Original : Original;
    BYTE B0 = (BYTE)(((Original >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        BYTE B1 = (BYTE)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
        Ar.Serialize(&B1, 1);
        I.Value = B1 & 0x7f;
    }
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}

// Out of line in Core (RVA 0x11b80); defined so LINK /LTCG assigns its convention
// (Ar in EAX, S in EBX).
void FString_Empty(FString &S, INT Slack);
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FString &S)
{
    Ar.CountBytes(S.ArrayNum * sizeof(TCHAR), S.ArrayMax * sizeof(TCHAR));
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        FString_Empty(S, NewNum);
        S.ArrayNum = NewNum;
        Ar.Serialize(S.Data, NewNum * sizeof(TCHAR));
    } else {
        Ar << AR_INDEX(S.ArrayNum);
        Ar.Serialize(S.Data, S.ArrayNum * sizeof(TCHAR));
    }
    return Ar;
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

void Driver_1331f0(FString *S, const TCHAR *T)
{
    Escape(&GConfig);
    Escape(&GMalloc);
    Escape((void *)&FURL::StaticInit);
    *S = T;
    FURL::StaticInit();
}

void Driver_133390(FString *S, const TCHAR *T)
{
    Escape(&GMalloc);
    Escape((void *)&FURL::StaticExit);
    *S = T;
    FURL::StaticExit();
}

void Driver_133420(FArchive *Ar, FURL *U, FString *S)
{
    *Ar << *S;
    Escape(&(*Ar << *U));
}

void Driver_133490(void *Mem1, void *Mem2, const TCHAR *Filename)
{
    Escape(&FURL::DefaultProtocol);
    Escape(&FURL::DefaultHost);
    Escape(&FURL::DefaultPort);
    Escape(&FURL::DefaultMap);
    Escape(&FURL::DefaultPortal);
    FURL *A = new(Mem1) FURL(0);
    FURL *B = new(Mem2) FURL(Filename);
    Escape(A);
    Escape(B);
}
