// campaign_app_strcmp.cpp -- appStrcmp forwards case-sensitive TCHAR ordering to wcscmp.
#include "unreal_types.h"

extern "C" int __cdecl wcscmp(const unsigned short *left, const unsigned short *right);

// appStrcmp
INT appStrcmp(const TCHAR *A, const TCHAR *B)
{
    return wcscmp(A, B);
}
