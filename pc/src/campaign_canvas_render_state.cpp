// campaign_canvas_render_state.cpp -- ECanvas render commands consumed by the PC interpreter
#include "unreal_script.h"
#include "campaign_canvas.h"

class APlayerController;

// UECanvas::execDrawPlayerPortal
void UECanvas::execDrawPlayerPortal(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(APlayerController, Player);
    P_GET_INT_OPTX(ClearFlags, 0);
    P_FINISH;
}

// UECanvas::execSetRenderState
void UECanvas::execSetRenderState(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(State);
    P_GET_UBOOL(Value);
    P_FINISH;
}

// UECanvas::execSetRenderTarget
void UECanvas::execSetRenderTarget(FFrame &Stack, RESULT_DECL)
{
    EPortalTarget Handle = CBUFFER;
    Stack.Step(Stack.Object, &Handle);
    P_FINISH;
}
