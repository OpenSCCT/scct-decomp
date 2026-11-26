// campaign_3c_crt_string_thunks.cpp -- wrappers for Campaign CRT string routines.
#include "unreal_containers.h"

extern "C" unsigned __cdecl wcslen(const TCHAR *text);
extern "C" const TCHAR *__cdecl wcsstr(const TCHAR *text, const TCHAR *pattern);
extern "C" TCHAR *__cdecl wcscat(TCHAR *destination, const TCHAR *source);
extern "C" int __cdecl _stricmp(const char *left, const char *right);
extern "C" TCHAR *__cdecl wcscpy(TCHAR *destination, const TCHAR *source);

// Unk_10ccadc0 wraps CRT wcslen.
INT Unk_10ccadc0(const TCHAR *text)
{
    return wcslen(text);
}

// appStrstr wraps CRT wcsstr.
const TCHAR *appStrstr(const TCHAR *text, const TCHAR *pattern)
{
    return wcsstr(text, pattern);
}

// Unk_10ccae10 wraps CRT wcscat.
TCHAR *Unk_10ccae10(TCHAR *destination, const TCHAR *source)
{
    return wcscat(destination, source);
}

// Unk_10ccae40 wraps CRT _stricmp.
INT Unk_10ccae40(const char *left, const char *right)
{
    return _stricmp(left, right);
}

// Unk_10ccae50 wraps CRT wcscpy.
TCHAR *Unk_10ccae50(TCHAR *destination, const TCHAR *source)
{
    return wcscpy(destination, source);
}
