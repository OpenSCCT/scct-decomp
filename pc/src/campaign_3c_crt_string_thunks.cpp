#include "unreal_containers.h"

extern "C" unsigned __cdecl wcslen(const TCHAR *text);
extern "C" const TCHAR *__cdecl wcsstr(const TCHAR *text, const TCHAR *pattern);
extern "C" TCHAR *__cdecl wcscat(TCHAR *destination, const TCHAR *source);
extern "C" int __cdecl _stricmp(const char *left, const char *right);
extern "C" TCHAR *__cdecl wcscpy(TCHAR *destination, const TCHAR *source);

INT Unk_10ccadc0(const TCHAR *text)
{
    return wcslen(text);
}

const TCHAR *appStrstr(const TCHAR *text, const TCHAR *pattern)
{
    return wcsstr(text, pattern);
}

TCHAR *Unk_10ccae10(TCHAR *destination, const TCHAR *source)
{
    return wcscat(destination, source);
}

INT Unk_10ccae40(const char *left, const char *right)
{
    return _stricmp(left, right);
}

TCHAR *Unk_10ccae50(TCHAR *destination, const TCHAR *source)
{
    return wcscpy(destination, source);
}
