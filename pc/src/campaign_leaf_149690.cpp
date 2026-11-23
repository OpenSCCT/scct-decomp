// campaign_leaf_149690.cpp -- UCanvas::execVideoStop
#include "unreal_script.h"
#include "campaign_canvas.h"

// UCanvas::execVideoStop
void UCanvas::execVideoStop(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    VideoStop(0);
}
