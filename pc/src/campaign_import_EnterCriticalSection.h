// campaign_import_EnterCriticalSection.h -- the kernel32.dll import EnterCriticalSection.
#ifndef CAMPAIGN_IMPORT_ENTERCRITICALSECTION_H
#define CAMPAIGN_IMPORT_ENTERCRITICALSECTION_H

struct _RTL_CRITICAL_SECTION;

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
    _RTL_CRITICAL_SECTION* lpCriticalSection);

#endif
