// campaign_import_CloseHandle.h -- a function imported from KERNEL32.dll.
// The retail import table names it CloseHandle.

#ifndef CAMPAIGN_IMPORT_CLOSEHANDLE_H
#define CAMPAIGN_IMPORT_CLOSEHANDLE_H

#include "campaign_import_HANDLE.h"

extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE Object);

#endif
