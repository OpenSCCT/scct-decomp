// campaign_leaf_17e5d0.cpp -- AVolume::execEncompasses
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_native_classes.h"

// AVolume::execEncompasses: whether Other's location is inside the volume
void AVolume::execEncompasses(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Other);
    P_FINISH;
    *(DWORD *)Result = Encompasses(Other->Location);
}
