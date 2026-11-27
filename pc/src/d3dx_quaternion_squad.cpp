#include "d3dx_quaternion_operators.h"

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionInverse(D3DXQUATERNION *, const D3DXQUATERNION *);
extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionLn(D3DXQUATERNION *, const D3DXQUATERNION *);
extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionExp(D3DXQUATERNION *, const D3DXQUATERNION *);

static inline void QuaternionLog(D3DXQUATERNION *out, const D3DXQUATERNION &q)
{
    D3DXQuaternionLn(out, &q);
}

static __forceinline float QuaternionLengthSquared(const D3DXQUATERNION &q)
{
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

void __stdcall c_D3DXQuaternionSquadSetup(
    D3DXQUATERNION *a, D3DXQUATERNION *b, D3DXQUATERNION *c,
    const D3DXQUATERNION *q0, const D3DXQUATERNION *q1,
    const D3DXQUATERNION *q2, const D3DXQUATERNION *q3)
{
    D3DXQUATERNION t0 = *q0, t1 = *q1, t2 = *q2, t3 = *q3;

    // Choose signs so adjacent quaternions follow the shorter arc.
    if (QuaternionLengthSquared(t0 + t1) < QuaternionLengthSquared(t0 - t1))
        t0 = -t0;
    if (QuaternionLengthSquared(t1 + t2) < QuaternionLengthSquared(t1 - t2))
        t2 = -t2;
    if (QuaternionLengthSquared(t2 + t3) < QuaternionLengthSquared(t2 - t3))
        t3 = -t3;

    D3DXQUATERNION inverse, leftLog, rightLog, exponent;

    D3DXQuaternionInverse(&inverse, &t1);
    QuaternionLog(&leftLog, inverse * t0);
    QuaternionLog(&rightLog, inverse * t2);
    {
        D3DXQUATERNION tangent = (rightLog + leftLog) * -0.25f;
        D3DXQuaternionExp(&exponent, &tangent);
    }
    *a = t1 * exponent;

    D3DXQuaternionInverse(&inverse, &t2);
    QuaternionLog(&leftLog, inverse * t1);
    QuaternionLog(&rightLog, inverse * t3);
    {
        D3DXQUATERNION tangent = (rightLog + leftLog) * -0.25f;
        D3DXQuaternionExp(&exponent, &tangent);
    }
    *b = t2 * exponent;
    *c = t2;
}
