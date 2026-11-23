// campaign_import_IsWindow.h -- a function imported from USER32.dll.
// The retail import table names it IsWindow.

#ifndef CAMPAIGN_IMPORT_ISWINDOW_H
#define CAMPAIGN_IMPORT_ISWINDOW_H

#include "campaign_import_HWND.h"

extern "C" __declspec(dllimport) int __stdcall IsWindow(HWND Window);

#endif
