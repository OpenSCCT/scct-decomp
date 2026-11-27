#include "d3dx_math_types.h"

D3DXVECTOR4 *__stdcall c_D3DXVec3Transform(
    D3DXVECTOR4 *out, const D3DXVECTOR3 *v, const D3DXMATRIX *matrix)
{
    D3DXVECTOR4 result;
    result.x = v->x * matrix->m[0][0] + v->y * matrix->m[1][0]
             + v->z * matrix->m[2][0]
             + matrix->m[3][0];
    result.y = v->x * matrix->m[0][1] + v->y * matrix->m[1][1]
             + v->z * matrix->m[2][1]
             + matrix->m[3][1];
    result.z = v->x * matrix->m[0][2] + v->y * matrix->m[1][2]
             + v->z * matrix->m[2][2]
             + matrix->m[3][2];
    result.w = v->x * matrix->m[0][3] + v->y * matrix->m[1][3]
             + v->z * matrix->m[2][3]
             + matrix->m[3][3];
    *out = result;
    return out;
}

D3DXVECTOR3 *__stdcall c_D3DXVec3TransformNormal(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *v, const D3DXMATRIX *matrix)
{
    D3DXVECTOR3 result;
    result.x = v->x * matrix->m[0][0] + v->y * matrix->m[1][0]
             + v->z * matrix->m[2][0];
    result.y = v->x * matrix->m[0][1] + v->y * matrix->m[1][1]
             + v->z * matrix->m[2][1];
    result.z = v->x * matrix->m[0][2] + v->y * matrix->m[1][2]
             + v->z * matrix->m[2][2];
    *out = result;
    return out;
}

D3DXVECTOR4 *__stdcall c_D3DXVec4Transform(
    D3DXVECTOR4 *out, const D3DXVECTOR4 *v, const D3DXMATRIX *matrix)
{
    D3DXVECTOR4 result;
    result.x = v->x * matrix->m[0][0] + v->y * matrix->m[1][0]
             + v->z * matrix->m[2][0] + v->w * matrix->m[3][0];
    result.y = v->x * matrix->m[0][1] + v->y * matrix->m[1][1]
             + v->z * matrix->m[2][1] + v->w * matrix->m[3][1];
    result.z = v->x * matrix->m[0][2] + v->y * matrix->m[1][2]
             + v->z * matrix->m[2][2] + v->w * matrix->m[3][2];
    result.w = v->x * matrix->m[0][3] + v->y * matrix->m[1][3]
             + v->z * matrix->m[2][3] + v->w * matrix->m[3][3];
    *out = result;
    return out;
}

D3DXVECTOR4 *__stdcall c_D3DXVec2Transform(
    D3DXVECTOR4 *out, const D3DXVECTOR2 *v, const D3DXMATRIX *matrix)
{
    D3DXVECTOR4 result;
    result.x = v->x * matrix->m[0][0] + v->y * matrix->m[1][0]
             + matrix->m[3][0];
    result.y = v->x * matrix->m[0][1] + v->y * matrix->m[1][1]
             + matrix->m[3][1];
    result.z = v->x * matrix->m[0][2] + v->y * matrix->m[1][2]
             + matrix->m[3][2];
    result.w = v->x * matrix->m[0][3] + v->y * matrix->m[1][3]
             + matrix->m[3][3];
    *out = result;
    return out;
}

D3DXVECTOR2 *__stdcall c_D3DXVec2TransformNormal(
    D3DXVECTOR2 *out, const D3DXVECTOR2 *v, const D3DXMATRIX *matrix)
{
    D3DXVECTOR2 result;
    result.x = v->x * matrix->m[0][0] + v->y * matrix->m[1][0];
    result.y = v->x * matrix->m[0][1] + v->y * matrix->m[1][1];
    *out = result;
    return out;
}
