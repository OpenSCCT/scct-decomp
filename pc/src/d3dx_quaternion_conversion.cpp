#include "d3dx_math_types.h"
#include <float.h>
#include <math.h>

void __stdcall c_D3DXQuaternionToAxisAngle(
    const D3DXQUATERNION *q, D3DXVECTOR3 *axis, FLOAT *angle)
{
    FLOAT lengthSq = q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w;
    if (lengthSq > FLT_MIN) {
        if (axis) {
            FLOAT invLength = 1.0f / static_cast<FLOAT>(sqrt(lengthSq));
            axis->x = q->x * invLength;
            axis->y = q->y * invLength;
            axis->z = q->z * invLength;
        }
        if (angle)
            *angle = 2.0f * static_cast<FLOAT>(acos(q->w));
    } else {
        if (axis) {
            axis->x = 1.0f;
            axis->y = 0.0f;
            axis->z = 0.0f;
        }
        if (angle)
            *angle = 0.0f;
    }
}

D3DXQUATERNION *__stdcall c_D3DXQuaternionRotationMatrix(
    D3DXQUATERNION *out, const D3DXMATRIX *m)
{
    FLOAT trace = m->m[0][0] + m->m[1][1] + m->m[2][2];
    if (trace > 0.0f) {
        FLOAT root = 0.5f * static_cast<FLOAT>(sqrt(trace + 1.0f));
        out->w = root;
        FLOAT scale = 0.25f / root;
        out->x = (m->m[1][2] - m->m[2][1]) * scale;
        out->y = (m->m[2][0] - m->m[0][2]) * scale;
        out->z = (m->m[0][1] - m->m[1][0]) * scale;
    } else {
        int next[3] = { 1, 2, 0 };
        FLOAT diag[3] = {
            m->m[0][0] - m->m[1][1] - m->m[2][2],
            m->m[1][1] - m->m[0][0] - m->m[2][2],
            m->m[2][2] - (m->m[0][0] + m->m[1][1])
        };
        int i = (diag[0] >= diag[1]) ? 0 : 1;
        i = diag[i] >= diag[2] ? i : 2;
        int j = next[i], k = next[j];
        FLOAT root = 0.5f * static_cast<FLOAT>(sqrt(diag[i] + 1.0f));
        FLOAT *values = *out;
        values[i] = root;
        FLOAT scale = 0.25f / root;
        values[j] = (m->m[i][j] + m->m[j][i]) * scale;
        values[k] = (m->m[i][k] + m->m[k][i]) * scale;
        out->w = (m->m[j][k] - m->m[k][j]) * scale;
    }
    return out;
}
