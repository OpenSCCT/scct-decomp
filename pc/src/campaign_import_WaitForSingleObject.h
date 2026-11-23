// campaign_import_WaitForSingleObject.h -- a function imported from KERNEL32.dll.
// The retail import table names it WaitForSingleObject.

#ifndef CAMPAIGN_IMPORT_WAITFORSINGLEOBJECT_H
#define CAMPAIGN_IMPORT_WAITFORSINGLEOBJECT_H

#include "campaign_import_HANDLE.h"

#define WAIT_OBJECT_0 0

extern "C" __declspec(dllimport)
unsigned long __stdcall WaitForSingleObject(HANDLE Handle, unsigned long Milliseconds);

#endif
