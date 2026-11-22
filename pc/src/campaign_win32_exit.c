#include "campaign_globals.h"

struct CriticalSection;
__declspec(dllimport) void __stdcall DeleteCriticalSection(struct CriticalSection *lock);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int period);

void destroy_engine_lock(void)
{
    DeleteCriticalSection(&engine_lock);
}

void end_timer_period(void)
{
    timeEndPeriod(timer_period);
}
