// campaign_import_CallWindowProcW.h -- a function imported from USER32.dll.
// The retail import table names it CallWindowProcW.

#ifndef CAMPAIGN_IMPORT_CALLWINDOWPROCW_H
#define CAMPAIGN_IMPORT_CALLWINDOWPROCW_H

#include "campaign_import_HWND.h"
#include "campaign_import_WNDPROC.h"

extern "C" __declspec(dllimport) long __stdcall CallWindowProcW(WNDPROC Procedure, HWND Window,
                                                                unsigned int Message,
                                                                unsigned int WParam, long LParam);

#endif
