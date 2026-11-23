// campaign_import_SendMessageW.h -- a function imported from USER32.dll.
// The retail import table names it SendMessageW.

#ifndef CAMPAIGN_IMPORT_SENDMESSAGEW_H
#define CAMPAIGN_IMPORT_SENDMESSAGEW_H

#include "campaign_import_HWND.h"

extern "C" __declspec(dllimport) long __stdcall SendMessageW(HWND Window, unsigned int Message,
                                                             unsigned int WParam, long LParam);

#endif
