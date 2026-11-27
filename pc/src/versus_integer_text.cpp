#include "versus_build.h"
#include "versus_memory.h"

extern "C" __declspec(dllimport) TCHAR *__cdecl _itow(INT Value, TCHAR *Buffer, INT Radix);

// Descriptive name. Retail callers use the returned shared wide string.
TCHAR *FormatDecimalInteger(INT Value)
{
    static TCHAR Buffer[20];
    appMemzero(Buffer, sizeof(Buffer));
    return _itow(Value, Buffer, 10);
}
