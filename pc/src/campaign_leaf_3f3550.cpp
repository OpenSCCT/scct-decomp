// campaign_leaf_3f3550.cpp -- UObject::execRotRand
#include "unreal_script.h"
#include "unreal_math.h"

INT Unk_10ccac00();

// UObject::execRotRand: a random rotator, rolled only when bRoll is set
void UObject::execRotRand(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bRoll);
    P_FINISH;
    FRotator RRot;
    RRot.Yaw = (2 * Unk_10ccac00()) % 65535;
    RRot.Pitch = (2 * Unk_10ccac00()) % 65535;
    INT Random = Unk_10ccac00();
    if (bRoll)
        RRot.Roll = (2 * Random) % 65535;
    else
        RRot.Roll = 0;
    *(FRotator *)Result = RRot;
}
