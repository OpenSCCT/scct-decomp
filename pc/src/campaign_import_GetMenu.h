// campaign_import_GetMenu.h -- a function imported from USER32.dll.
// The retail import table names it GetMenu.

#ifndef CAMPAIGN_IMPORT_GETMENU_H
#define CAMPAIGN_IMPORT_GETMENU_H

#include "campaign_import_HMENU.h"
#include "campaign_import_HWND.h"

extern "C" __declspec(dllimport) HMENU __stdcall GetMenu(HWND Window);

#endif
