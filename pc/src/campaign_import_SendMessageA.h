// campaign_import_SendMessageA.h -- a function imported from USER32.dll.
// The retail import table names it SendMessageA.

#ifndef CAMPAIGN_IMPORT_SENDMESSAGEA_H
#define CAMPAIGN_IMPORT_SENDMESSAGEA_H

#include "campaign_import_HWND.h"

extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND Window, unsigned int Message,
                                                             unsigned int WParam, long LParam);

#endif
