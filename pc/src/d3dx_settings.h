#ifndef D3DX_SETTINGS_H
#define D3DX_SETTINGS_H

#include "windows_dispatch_types.h"

BOOL GetD3DRegValue(DWORD expectedType, LPSTR name, LPVOID data, DWORD size);
BOOL isMMXprocessor();

#endif
