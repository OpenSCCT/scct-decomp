// campaign_import_WNDPROC.h -- the Win32 window procedure type, as winuser.h declares it.

#ifndef CAMPAIGN_IMPORT_WNDPROC_H
#define CAMPAIGN_IMPORT_WNDPROC_H

#include "campaign_import_HWND.h"

typedef long (__stdcall* WNDPROC)(HWND, unsigned int, unsigned int, long);

#endif
