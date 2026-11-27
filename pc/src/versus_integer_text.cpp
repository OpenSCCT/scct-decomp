#include "versus_build.h"
#include "unreal_types.h"
#include "versus_app_memzero.h"

extern "C" __declspec(dllimport) TCHAR *__cdecl _itow(INT Value, TCHAR *Dest, INT Radix);

TCHAR *IntToString(INT Value)
{
    static TCHAR Buffer[20];
    appMemzero(Buffer, sizeof(Buffer));
    return _itow(Value, Buffer, 10);
}
