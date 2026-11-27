#include "versus_pawn_action_events.h"

struct ASPlayerController_eventGetObjectivesLeft_Parms {
    INT ReturnValue;
};

INT ASPlayerController::eventGetObjectivesLeft()
{
    ASPlayerController_eventGetObjectivesLeft_Parms Parms;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunctionChecked(NAME_GetObjectivesLeft, 0), &Parms, 0);
    return Parms.ReturnValue;
}
