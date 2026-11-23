// campaign_import_ReleaseMutex.h -- a function imported from KERNEL32.dll.
// The retail import table names it ReleaseMutex.

#ifndef CAMPAIGN_IMPORT_RELEASEMUTEX_H
#define CAMPAIGN_IMPORT_RELEASEMUTEX_H

#include "campaign_import_HANDLE.h"

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(HANDLE Mutex);

#endif
