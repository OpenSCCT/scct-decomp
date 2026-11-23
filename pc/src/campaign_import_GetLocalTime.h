// campaign_import_GetLocalTime.h -- a function imported from KERNEL32.dll.
// The retail import table names it GetLocalTime.

#ifndef CAMPAIGN_IMPORT_GETLOCALTIME_H
#define CAMPAIGN_IMPORT_GETLOCALTIME_H

struct _SYSTEMTIME
{
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
};
typedef struct _SYSTEMTIME SYSTEMTIME;

extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME* Time);

#endif
