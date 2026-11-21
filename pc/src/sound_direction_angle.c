#include "sound_math.h"
#include "sound_micro.h"

static __forceinline float angle_from_projection(float x, float y)
{
    float angle;
    if (x == 0) {
        if (y == 0) return 0;
        if (y > 0) return 0.25f;
        return 0.75f;
    }
    if (y == 0) {
        if (x > 0) return 0;
        return 0.5f;
    }
    angle = SND_fn_fFastAtan(y / x);
    if (angle < 0) {
        if (y > 0) angle += 0.5f;
        else angle += 1.0f;
    } else if (angle > 0) {
        if (y < 0) angle += 0.5f;
    } else if (y > 0)
        angle += 0.5f;
    return angle;
}

float __fastcall fn_fGetObjectAngleWithMicroNor(const SndVector *pos)
{
    tdstMicroDescription *pstMicro = gs_stMicrosSxd.pList.hFirstElementDyn;
    SndVector vect;
    float dx, dy, dz, x, y;
    if (!pstMicro)
        return 0.0f;
    vect.x = pos->x - pstMicro->pos.x;
    vect.y = pos->y - pstMicro->pos.y;
    vect.z = pos->z - pstMicro->pos.z;
    dz = vect.z / 65536.0f;
    dy = vect.y / 65536.0f;
    dx = vect.x / 65536.0f;
    x = dx * (pstMicro->dir_nor.x / 65536.0f)
        + (dy * (pstMicro->dir_nor.y / 65536.0f) + dz * (pstMicro->dir_nor.z / 65536.0f));
    y = dx * (pstMicro->dir_tan.x / 65536.0f)
        + (dy * (pstMicro->dir_tan.y / 65536.0f) + dz * (pstMicro->dir_tan.z / 65536.0f));
    return angle_from_projection(x, y);
}
