// campaign_import_QueryPerformanceFrequency.h -- a function imported from KERNEL32.dll.
// The retail import table names it QueryPerformanceFrequency.

#ifndef CAMPAIGN_IMPORT_QUERYPERFORMANCEFREQUENCY_H
#define CAMPAIGN_IMPORT_QUERYPERFORMANCEFREQUENCY_H

#include "campaign_import_LARGE_INTEGER.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(LARGE_INTEGER* Frequency);

#endif
