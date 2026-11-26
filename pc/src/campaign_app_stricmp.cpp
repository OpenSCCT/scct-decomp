// campaign_app_stricmp.cpp -- appStricmp forwards case-insensitive TCHAR ordering to _wcsicmp.
#include "unreal_types.h"

extern "C" int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);

// appStricmp
INT appStricmp(const TCHAR *A, const TCHAR *B)
{
    return _wcsicmp(A, B);
}
