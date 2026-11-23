// campaign_import_ReadFile.h -- a function imported from KERNEL32.dll.
// The retail import table names it ReadFile.

#ifndef CAMPAIGN_IMPORT_READFILE_H
#define CAMPAIGN_IMPORT_READFILE_H

#include "campaign_import_HANDLE.h"

extern "C" __declspec(dllimport)
int __stdcall ReadFile(
    HANDLE File,
    void* Buffer,
    unsigned long BytesToRead,
    unsigned long* BytesRead,
    struct _OVERLAPPED* Overlapped);

#endif
