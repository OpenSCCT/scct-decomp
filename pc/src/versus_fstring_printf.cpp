#include "versus_build.h"
#include "versus_engine_stats.h"
#include <stdarg.h>

extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Buffer, unsigned int Count,
    const TCHAR *Format, va_list Args);

FString __cdecl FString::Printf(const TCHAR *Format, ...)
{
    TCHAR Buffer[4096];
    va_list Args;
    va_start(Args, Format);
    _vsnwprintf(Buffer, sizeof(Buffer) / sizeof(Buffer[0]), Format, Args);
    va_end(Args);
    return FString(Buffer);
}
