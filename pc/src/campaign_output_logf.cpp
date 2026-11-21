// campaign_output_logf.cpp -- FString::Printf and FOutputDevice::Logf
//
// Built with stack cookies (/GS), like the retail object.
#include "unreal_script.h"
#include "unreal_containers.h"

// FString::Printf
FString FString::Printf(const TCHAR *Fmt, ...)
{
    TCHAR TempStr[4096];
    GET_VARARGS(TempStr, 4096, Fmt);
    return FString(TempStr);
}

// FOutputDevice::Logf
void FOutputDevice::Logf(EName Event, const TCHAR *Fmt, ...)
{
    if (!FName::SafeSuppressed(Event))
    {
        TCHAR TempStr[4096];
        GET_VARARGS(TempStr, 4096, Fmt);
        Serialize(TempStr, Event);
    }
}

// FOutputDevice::Logf
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!FName::SafeSuppressed(NAME_Log))
    {
        TCHAR TempStr[4096];
        GET_VARARGS(TempStr, 4096, Fmt);
        Serialize(TempStr, NAME_Log);
    }
}
