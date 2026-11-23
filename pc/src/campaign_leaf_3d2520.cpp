// campaign_leaf_3d2520.cpp -- one function at file offset 0x3d2520, preferred VA 0x10cd2520. A
// constructor: it asks timeGetDevCaps for the timer's period range, clamps 1 into it, stores the
// period at 0x0 and passes it to timeBeginPeriod, stores timeGetTime at 0x4, and fills 0x8 with
// QueryPerformanceFrequency and 0x10 with QueryPerformanceCounter. The class, member and local
// names are invented; the imports are named by the retail import table, and the offsets and the
// bytes are the binary's.

#include "campaign_import_QueryPerformanceCounter.h"
#include "campaign_import_QueryPerformanceFrequency.h"
#include "campaign_import_timeBeginPeriod.h"
#include "campaign_import_timeGetDevCaps.h"
#include "campaign_import_timeGetTime.h"

class UnkType_10cd2520
{
public:
    UnkType_10cd2520();

    unsigned int unk_0;
    unsigned long unk_4;
    LARGE_INTEGER unk_8;
    LARGE_INTEGER unk_10;
};

// UnkType_10cd2520::UnkType_10cd2520
UnkType_10cd2520::UnkType_10cd2520()
{
    TIMECAPS Caps;
    unsigned int Period;

    timeGetDevCaps(&Caps, sizeof(Caps));
    Period = Caps.wPeriodMin;
    if ( Period < 1 )
    {
        Period = 1;
    }
    if ( Period > Caps.wPeriodMax )
    {
        Period = Caps.wPeriodMax;
    }
    unk_0 = Period;
    timeBeginPeriod(Period);
    unk_4 = timeGetTime();
    QueryPerformanceFrequency(&unk_8);
    QueryPerformanceCounter(&unk_10);
}
