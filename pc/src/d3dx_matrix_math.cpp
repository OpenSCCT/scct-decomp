/* D3DX8 scalar comparison and matrix functions from d3dxmath.obj. */

#include <float.h>
#include <math.h>
#include "d3dx_math_types.h"

int WithinEpsilon(float a, float b)
{
    float difference = a - b;
    return -FLT_EPSILON <= difference && difference <= FLT_EPSILON;
}

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionRotationYawPitchRoll(
    D3DXQUATERNION *pOut,
    FLOAT yaw,
    FLOAT pitch,
    FLOAT roll);

extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationQuaternion(
    D3DXMATRIX *pOut,
    const D3DXQUATERNION *pQ);

/* D3DXMatrixTranspose */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranspose(
    D3DXMATRIX *pOut,
    const D3DXMATRIX *pM)
{
    FLOAT value;

    value = pM->m[0][1];
    pOut->m[0][1] = pM->m[1][0];
    pOut->m[1][0] = value;
    value = pM->m[0][2];
    pOut->m[0][2] = pM->m[2][0];
    pOut->m[2][0] = value;
    value = pM->m[0][3];
    pOut->m[0][3] = pM->m[3][0];
    pOut->m[3][0] = value;
    value = pM->m[1][2];
    pOut->m[1][2] = pM->m[2][1];
    pOut->m[2][1] = value;
    value = pM->m[1][3];
    pOut->m[1][3] = pM->m[3][1];
    pOut->m[3][1] = value;
    value = pM->m[2][3];
    pOut->m[2][3] = pM->m[3][2];
    pOut->m[3][2] = value;
    if (pOut != pM) {
        pOut->m[0][0] = pM->m[0][0];
        pOut->m[1][1] = pM->m[1][1];
        pOut->m[2][2] = pM->m[2][2];
        pOut->m[3][3] = pM->m[3][3];
    }
    return pOut;
}

/* D3DXMatrixScaling */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixScaling(
    D3DXMATRIX *pOut,
    FLOAT sx,
    FLOAT sy,
    FLOAT sz)
{
    pOut->m[3][2] = 0.0f;
    pOut->m[0][0] = sx;
    pOut->m[3][1] = 0.0f;
    pOut->m[1][1] = sy;
    pOut->m[3][0] = 0.0f;
    pOut->m[2][2] = sz;
    pOut->m[2][3] = 0.0f;
    pOut->m[2][1] = 0.0f;
    pOut->m[2][0] = 0.0f;
    pOut->m[1][3] = 0.0f;
    pOut->m[1][2] = 0.0f;
    pOut->m[1][0] = 0.0f;
    pOut->m[0][3] = 0.0f;
    pOut->m[0][2] = 0.0f;
    pOut->m[0][1] = 0.0f;
    pOut->m[3][3] = 1.0f;
    return pOut;
}

/* D3DXMatrixTranslation */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranslation(
    D3DXMATRIX *pOut,
    FLOAT x,
    FLOAT y,
    FLOAT z)
{
    pOut->m[2][3] = 0.0f;
    pOut->m[3][0] = x;
    pOut->m[2][1] = 0.0f;
    pOut->m[3][1] = y;
    pOut->m[2][0] = 0.0f;
    pOut->m[3][2] = z;
    pOut->m[1][3] = 0.0f;
    pOut->m[1][2] = 0.0f;
    pOut->m[1][0] = 0.0f;
    pOut->m[0][3] = 0.0f;
    pOut->m[0][2] = 0.0f;
    pOut->m[0][1] = 0.0f;
    pOut->m[3][3] = 1.0f;
    pOut->m[2][2] = 1.0f;
    pOut->m[1][1] = 1.0f;
    pOut->m[0][0] = 1.0f;
    return pOut;
}

/* D3DXMatrixRotationYawPitchRoll */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationYawPitchRoll(
    D3DXMATRIX *pOut,
    FLOAT yaw,
    FLOAT pitch,
    FLOAT roll)
{
    D3DXQUATERNION quaternion;

    D3DXQuaternionRotationYawPitchRoll(&quaternion, yaw, pitch, roll);
    D3DXMatrixRotationQuaternion(pOut, &quaternion);
    return pOut;
}

extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationQuaternion(D3DXMATRIX *out, const D3DXQUATERNION *q)
{
    float x2 = q->x * 2.0f;
    float y2 = q->y * 2.0f;
    float z2 = q->z * 2.0f;
    float wx = q->w * x2;
    float wy = q->w * y2;
    float wz = q->w * z2;
    float xx = q->x * x2;
    float xy = q->x * y2;
    float xz = q->x * z2;
    float yy = q->y * y2;
    float yz = q->y * z2;
    float zz = q->z * z2;

    out->m[0][0] = 1.0f - yy - zz;
    out->m[0][1] = xy + wz;
    out->m[0][2] = xz - wy;
    out->m[0][3] = 0.0f;
    out->m[1][0] = xy - wz;
    out->m[1][1] = 1.0f - xx - zz;
    out->m[1][2] = yz + wx;
    out->m[1][3] = 0.0f;
    out->m[2][0] = xz + wy;
    out->m[2][1] = yz - wx;
    out->m[2][2] = 1.0f - xx - yy;
    out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;
    out->m[3][1] = 0.0f;
    out->m[3][2] = 0.0f;
    out->m[3][3] = 1.0f;
    return out;
}

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionSlerp(
    D3DXQUATERNION *out, const D3DXQUATERNION *start,
    const D3DXQUATERNION *end, float t);

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionSquad(D3DXQUATERNION *out,
    const D3DXQUATERNION *q1, const D3DXQUATERNION *q2,
    const D3DXQUATERNION *q3, const D3DXQUATERNION *q4, float t)
{
    D3DXQUATERNION endpoints, controls;
    D3DXQuaternionSlerp(&endpoints, q1, q4, t);
    D3DXQuaternionSlerp(&controls, q2, q3, t);
    D3DXQuaternionSlerp(out, &endpoints, &controls, 2.0f * (t * (1.0f - t)));
    return out;
}

D3DXPLANE *__stdcall c_D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *plane)
{
    FLOAT lengthSq = plane->a * plane->a + plane->b * plane->b + plane->c * plane->c;
    if (WithinEpsilon(lengthSq, 1.0f)) {
        if (out != plane)
            *out = *plane;
    } else if (lengthSq > FLT_MIN) {
        FLOAT scale = 1.0f / static_cast<FLOAT>(sqrt(lengthSq));
        out->a = scale * plane->a;
        out->b = scale * plane->b;
        out->c = scale * plane->c;
        out->d = scale * plane->d;
    } else {
        out->a = 0.0f;
        out->b = 0.0f;
        out->c = 0.0f;
        out->d = 0.0f;
    }
    return out;
}
