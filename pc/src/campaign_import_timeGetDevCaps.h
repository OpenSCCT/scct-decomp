// campaign_import_timeGetDevCaps.h -- a function imported from WINMM.dll.
// The retail import table names it timeGetDevCaps.

#ifndef CAMPAIGN_IMPORT_TIMEGETDEVCAPS_H
#define CAMPAIGN_IMPORT_TIMEGETDEVCAPS_H

struct timecaps_tag
{
    unsigned int wPeriodMin;
    unsigned int wPeriodMax;
};
typedef struct timecaps_tag TIMECAPS;

extern "C" __declspec(dllimport)
unsigned int __stdcall timeGetDevCaps(TIMECAPS* Caps, unsigned int Size);

#endif
