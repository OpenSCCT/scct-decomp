// campaign_leaf_332a50.cpp -- UECanvas::execViewportSizeY
#include "unreal_script.h"
#include "campaign_canvas.h"
#include "campaign_player.h"

// UECanvas::execViewportSizeY
void UECanvas::execViewportSizeY(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(INT *)Result = Viewport->SizeY;
}
