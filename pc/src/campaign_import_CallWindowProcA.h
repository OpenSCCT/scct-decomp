// campaign_import_CallWindowProcA.h -- a function imported from USER32.dll.
// The retail import table names it CallWindowProcA.

#ifndef CAMPAIGN_IMPORT_CALLWINDOWPROCA_H
#define CAMPAIGN_IMPORT_CALLWINDOWPROCA_H

#include "campaign_import_HWND.h"
#include "campaign_import_WNDPROC.h"

extern "C" __declspec(dllimport) long __stdcall CallWindowProcA(WNDPROC Procedure, HWND Window,
                                                                unsigned int Message,
                                                                unsigned int WParam, long LParam);

#endif
