#include "d3dx_math_types.h"
#include <float.h>

extern "C" D3DXPLANE *__stdcall D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *plane);

D3DXPLANE *__stdcall c_D3DXPlaneFromPointNormal(
    D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal)
{
    out->a = normal->x;
    out->b = normal->y;
    out->c = normal->z;
    out->d = -(point->x * normal->x + point->y * normal->y + point->z * normal->z);
    return out;
}

extern "C" D3DXVECTOR3 *__stdcall D3DXVec3Normalize(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *vector);

static inline D3DXVECTOR3 *D3DXVec3Subtract(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
    return out;
}

static inline D3DXVECTOR3 *D3DXVec3Cross(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b)
{
    D3DXVECTOR3 cross;
    cross.x = a->y * b->z - a->z * b->y;
    cross.y = a->z * b->x - a->x * b->z;
    cross.z = a->x * b->y - a->y * b->x;
    *out = cross;
    return out;
}

D3DXPLANE *__stdcall c_D3DXPlaneFromPoints(
    D3DXPLANE *out, const D3DXVECTOR3 *first,
    const D3DXVECTOR3 *second, const D3DXVECTOR3 *third)
{
    D3DXVECTOR3 edge1, edge2;
    D3DXVECTOR3 *normal = reinterpret_cast<D3DXVECTOR3 *>(out);
    D3DXVec3Subtract(&edge1, first, second);
    D3DXVec3Subtract(&edge2, first, third);
    D3DXVec3Cross(normal, &edge1, &edge2);
    D3DXVec3Normalize(normal, normal);

    FLOAT distance = normal->z * first->z;
    distance += normal->y * first->y;
    distance += normal->x * first->x;
    out->d = -distance;
    return out;
}

D3DXMATRIX *__stdcall c_D3DXMatrixReflect(D3DXMATRIX *out, const D3DXPLANE *plane)
{
    D3DXPLANE unit;
    D3DXPlaneNormalize(&unit, plane);
    FLOAT x = -2.0f * unit.a;
    FLOAT y = -2.0f * unit.b;
    FLOAT z = -2.0f * unit.c;

    out->m[0][0] = 1.0f + unit.a * x;
    out->m[0][1] = unit.a * y;
    out->m[0][2] = unit.a * z;
    out->m[0][3] = 0.0f;

    out->m[1][0] = unit.b * x;
    out->m[1][1] = 1.0f + unit.b * y;
    out->m[1][2] = unit.b * z;
    out->m[1][3] = 0.0f;

    out->m[2][0] = unit.c * x;
    out->m[2][1] = unit.c * y;
    out->m[2][2] = 1.0f + unit.c * z;
    out->m[2][3] = 0.0f;

    out->m[3][0] = unit.d * x;
    out->m[3][1] = unit.d * y;
    out->m[3][2] = unit.d * z;
    out->m[3][3] = 1.0f;
    return out;
}

D3DXVECTOR3 *__stdcall c_D3DXPlaneIntersectLine(
    D3DXVECTOR3 *out, const D3DXPLANE *plane, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b)
{
    FLOAT startDistance = plane->a * a->x + plane->b * a->y + plane->c * a->z;
    FLOAT endDistance = plane->a * b->x + plane->b * b->y + plane->c * b->z;
    FLOAT difference = startDistance - endDistance;
    if (!difference)
        return 0;
    FLOAT t = (startDistance + plane->d) / difference;
    if (!_finite(t))
        return 0;
    out->x = a->x + t * (b->x - a->x);
    out->y = a->y + t * (b->y - a->y);
    out->z = a->z + t * (b->z - a->z);
    return out;
}

D3DXMATRIX *__stdcall c_D3DXMatrixShadow(
    D3DXMATRIX *out, const D3DXVECTOR4 *light, const D3DXPLANE *plane)
{
    D3DXPLANE unit;
    D3DXPlaneNormalize(&unit, plane);

    FLOAT dot = unit.a * light->x + unit.b * light->y
              + unit.c * light->z + unit.d * light->w;
    D3DXPLANE negative = { -unit.a, -unit.b, -unit.c, -unit.d };

    out->m[0][0] = dot + negative.a * light->x;
    out->m[1][0] = negative.b * light->x;
    out->m[2][0] = negative.c * light->x;
    out->m[3][0] = negative.d * light->x;

    out->m[0][1] = negative.a * light->y;
    out->m[1][1] = dot + negative.b * light->y;
    out->m[2][1] = negative.c * light->y;
    out->m[3][1] = negative.d * light->y;

    out->m[0][2] = negative.a * light->z;
    out->m[1][2] = negative.b * light->z;
    out->m[2][2] = dot + negative.c * light->z;
    out->m[3][2] = negative.d * light->z;

    out->m[0][3] = negative.a * light->w;
    out->m[1][3] = negative.b * light->w;
    out->m[2][3] = negative.c * light->w;
    out->m[3][3] = dot + negative.d * light->w;
    return out;
}
