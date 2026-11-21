// FOutputDevice::Logf, built with stack cookies like the retail object.
typedef int INT;
typedef unsigned int DWORD;
typedef int UBOOL;
typedef unsigned short TCHAR;
enum EName { NAME_Log = 0x2f8 };
enum { RF_Suppress = 0x00001000 };

struct FNameEntry {
    INT Index;
    DWORD Flags;
};

class FName {
public:
    static UBOOL Initialized;
    static FNameEntry **Names;
    static UBOOL SafeSuppressed(EName Index)
    {
        return Initialized && (Names[Index]->Flags & RF_Suppress);
    }
};

INT appGetVarArgs(TCHAR *Dest, INT Count, const TCHAR *&Fmt);
#define GET_VARARGS(Msg, Len, Fmt) appGetVarArgs(Msg, Len, Fmt)

class FString {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In);
    ~FString();
    static FString Printf(const TCHAR *Fmt, ...);
};

FString FString::Printf(const TCHAR *Fmt, ...)
{
    TCHAR TempStr[4096];
    GET_VARARGS(TempStr, 4096, Fmt);
    return FString(TempStr);
}

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    void Logf(EName Event, const TCHAR *Fmt, ...);
    void Logf(const TCHAR *Fmt, ...);
};

void FOutputDevice::Logf(EName Event, const TCHAR *Fmt, ...)
{
    if (!FName::SafeSuppressed(Event))
    {
        TCHAR TempStr[4096];
        GET_VARARGS(TempStr, 4096, Fmt);
        Serialize(TempStr, Event);
    }
}

void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!FName::SafeSuppressed(NAME_Log))
    {
        TCHAR TempStr[4096];
        GET_VARARGS(TempStr, 4096, Fmt);
        Serialize(TempStr, NAME_Log);
    }
}
