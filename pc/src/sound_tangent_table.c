#include "sound_math.h"

float __cdecl SND_fn_fFastAtan(float tangent)
{
    float magnitude = tangent < 0 ? -tangent : tangent;
    int low = 0;
    int high = 90;
    int index = 0;
    if (magnitude <= gs_TanAngle[0].tangent) {
        index = 0;
    } else if (magnitude >= gs_TanAngle[90].tangent) {
        index = 90;
    } else {
        int last;
        do {
            last = index;
            index = (high + low) / 2;
            if (magnitude > gs_TanAngle[index].tangent)
                low = index;
            else
                high = index;
        } while (last != index);
        if (!index && magnitude > 0.0)
            index = 1;
    }
    if (tangent < 0)
        return -gs_TanAngle[index].angle;
    return gs_TanAngle[index].angle;
}
