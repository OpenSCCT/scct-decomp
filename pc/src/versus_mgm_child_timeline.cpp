#include "versus_mgm.h"
#include "versus_mgm_content.h"

void MgmChild::SetTime(FLOAT Seconds, INT MillisecondsPerFrame, BYTE Update)
{
    EvaluateTime(Seconds, MillisecondsPerFrame, Update);
    Content->SetTime(Seconds);
}

void MgmChild::Tick(FLOAT Seconds, FLOAT DeltaSeconds, INT MillisecondsPerFrame, BYTE Update)
{
    EvaluateTime(Seconds, MillisecondsPerFrame, Update);
    Content->Tick(Seconds, DeltaSeconds);
}
