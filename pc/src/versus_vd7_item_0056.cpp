// Work item 0056: FURL::String, FURL::IsInternal, FURL::IsLocalInternal.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *D, const TCHAR *S) { return wcscpy(D, S); }
inline INT appStricmp(const TCHAR *S1, const TCHAR *S2) { return _wcsicmp(S1, S2); }

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T>
class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other);
    ~FString();

    const TCHAR *operator*() const { return ArrayNum ? &(*this)(0) : L""; }
    INT Len() const { return Num() ? Num() - 1 : 0; }

    FString &operator+=(const TCHAR *Str);
    FString &operator+=(const FString &Str) { return operator+=(*Str); }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
    UBOOL operator!=(const FString &Other) const;

    static FString __cdecl Printf(const TCHAR *Fmt, ...);
};

FString &FString::operator+=(const TCHAR *Str)
{
    if (*Str)
    {
        if (ArrayNum)
        {
            INT Index = ArrayNum - 1;
            Add(appStrlen(Str));
            appStrcpy(&(*this)(Index), Str);
        }
        else
        {
            Add(appStrlen(Str) + 1);
            appStrcpy(&(*this)(0), Str);
        }
    }
    return *this;
}

UBOOL FString::operator!=(const FString &Other) const
{
    return appStricmp(**this, *Other) != 0;
}

extern const TCHAR UrlColon1[];
extern const TCHAR UrlSlashes[];
extern const TCHAR UrlColon2[];
extern const TCHAR UrlFmtInt[];
extern const TCHAR UrlSlash[];
extern const TCHAR UrlQuestion[];
extern const TCHAR UrlHash[];

class FURL
{
public:
    FString Protocol;
    FString Host;
    INT Port;
    FString Map;
    TArray<FString> Op;
    FString Portal;

    static FString DefaultProtocol;
    static FString DefaultHost;
    static INT DefaultPort;

    FString String(UBOOL FullyQualified) const;
    UBOOL IsInternal() const;
    UBOOL IsLocalInternal() const;
};

// FURL::String (RVA 0x134050)
FString FURL::String(UBOOL FullyQualified) const
{
    FString Result;

    if (Protocol != DefaultProtocol || FullyQualified)
    {
        Result += *Protocol;
        Result += UrlColon1;
        if (Host != DefaultHost)
            Result += UrlSlashes;
    }

    if (Host != DefaultHost || Port != DefaultPort)
    {
        Result += *Host;
        if (Port != DefaultPort)
        {
            Result += UrlColon2;
            Result += *FString::Printf(UrlFmtInt, Port);
        }
        Result += UrlSlash;
    }

    if (Map.Num())
        Result += *Map;

    for (INT i = 0; i < Op.Num(); i++)
    {
        Result += UrlQuestion;
        Result += *Op(i);
    }

    if (Portal.Num())
    {
        Result += UrlHash;
        Result += *Portal;
    }

    return Result;
}

// FURL::IsInternal (RVA 0x1343a0)
UBOOL FURL::IsInternal() const
{
    return appStricmp(*Protocol, *DefaultProtocol) == 0;
}

// FURL::IsLocalInternal (RVA 0x1343f0)
UBOOL FURL::IsLocalInternal() const
{
    return IsInternal() && Host.Len() == 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void SinkStr(const FString &);
void SinkBool(UBOOL);

void Driver_134050(const FURL *U1, const FURL *U2, UBOOL FQ)
{
    Escape(&FURL::DefaultProtocol);
    Escape(&FURL::DefaultHost);
    Escape(&FURL::DefaultPort);
    SinkStr(U1->String(FQ));
    SinkStr(U2->String(0));
}

#pragma inline_depth(0)
void Driver_1343a0(const FURL *U1, const FURL *U2)
{
    Escape(&FURL::DefaultProtocol);
    SinkBool(U1->IsInternal());
    SinkBool(U2->IsInternal());
}

void Driver_1343f0(const FURL *U1)
{
    Escape(&FURL::DefaultProtocol);
    SinkBool(0);
    SinkBool(U1->IsLocalInternal());
    SinkBool(U1->IsLocalInternal());
}
#pragma inline_depth()
