// campaign_leaf_332a10.cpp -- UECanvas::execViewportSizeX
#include "unreal_script.h"
#include "campaign_canvas.h"
#include "campaign_player.h"

// UECanvas::execViewportSizeX
void UECanvas::execViewportSizeX(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(INT *)Result = Viewport->SizeX;
}
