// campaign_import_LeaveCriticalSection.h -- the kernel32.dll import LeaveCriticalSection.
#ifndef CAMPAIGN_IMPORT_LEAVECRITICALSECTION_H
#define CAMPAIGN_IMPORT_LEAVECRITICALSECTION_H

struct _RTL_CRITICAL_SECTION;

extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    _RTL_CRITICAL_SECTION* lpCriticalSection);

#endif
