// campaign_import_QueryPerformanceCounter.h -- a function imported from KERNEL32.dll.
// The retail import table names it QueryPerformanceCounter.

#ifndef CAMPAIGN_IMPORT_QUERYPERFORMANCECOUNTER_H
#define CAMPAIGN_IMPORT_QUERYPERFORMANCECOUNTER_H

#include "campaign_import_LARGE_INTEGER.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* Count);

#endif
