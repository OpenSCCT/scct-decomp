// campaign_import_CreateFileW.h -- a function imported from KERNEL32.dll.
// The retail import table names it CreateFileW.

#ifndef CAMPAIGN_IMPORT_CREATEFILEW_H
#define CAMPAIGN_IMPORT_CREATEFILEW_H

#include "campaign_import_HANDLE.h"

#define GENERIC_READ 0x80000000
#define FILE_SHARE_READ 0x00000001
#define OPEN_EXISTING 3
#define FILE_FLAG_NO_BUFFERING 0x20000000
#define FILE_FLAG_OVERLAPPED 0x40000000
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

struct _SECURITY_ATTRIBUTES;

extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileW(
    const unsigned short* FileName,
    unsigned long DesiredAccess,
    unsigned long ShareMode,
    _SECURITY_ATTRIBUTES* SecurityAttributes,
    unsigned long CreationDisposition,
    unsigned long FlagsAndAttributes,
    HANDLE TemplateFile);

#endif
