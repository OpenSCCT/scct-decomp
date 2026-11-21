// versus_simple_natives.cpp -- Versus natives that read scalar parameters and call one method
//
// The called method is named after the native; its own name is not recorded.
#include "versus_build.h"
#include "unreal_script.h"
#include "versus_engine_classes.h"
#include "versus_sbase_classes.h"

// UCanvas::execRenderMotionTracking
void UCanvas::execRenderMotionTracking(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A0);
    P_GET_INT(A1);
    P_GET_INT(A2);
    P_FINISH;
    RenderMotionTracking(A0, A1, A2);
}

// ASWeaponDefense::execGetAccuracy
void ASWeaponDefense::execGetAccuracy(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT *)Result = GetAccuracy();
}

// ASGadget::execGetUniqueIDByClass
void ASGadget::execGetUniqueIDByClass(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(INT *)Result = GetUniqueIDByClass();
}

// ASBasePawn::execExecuteAction
void ASBasePawn::execExecuteAction(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A0);
    P_FINISH;
    ExecuteAction(A0);
}
