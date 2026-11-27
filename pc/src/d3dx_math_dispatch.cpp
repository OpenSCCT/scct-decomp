#include "d3dx_fast_table.h"

D3DXVECTOR4 * __stdcall c_D3DXVec2Transform(D3DXVECTOR4 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix);
D3DXVECTOR4 * __stdcall c_D3DXVec3Transform(D3DXVECTOR4 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);
D3DXVECTOR4 * __stdcall c_D3DXVec4Transform(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector, const D3DXMATRIX *matrix);
D3DXMATRIX * __stdcall c_D3DXMatrixMultiply(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right);
D3DXMATRIX * __stdcall c_D3DXMatrixMultiplyTranspose(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right);
D3DXVECTOR2 * __stdcall c_D3DXVec2TransformNormal(D3DXVECTOR2 *out, const D3DXVECTOR2 *normal, const D3DXMATRIX *matrix);
D3DXVECTOR3 * __stdcall c_D3DXVec3TransformNormal(D3DXVECTOR3 *out, const D3DXVECTOR3 *normal, const D3DXMATRIX *matrix);
D3DXVECTOR3 * __stdcall c_D3DXVec3Normalize(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector);
D3DXVECTOR4 * __stdcall c_D3DXVec4Normalize(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector);
D3DXVECTOR2 * __stdcall c_D3DXVec2TransformCoord(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix);
D3DXVECTOR3 * __stdcall c_D3DXVec3TransformCoord(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);
FLOAT __stdcall c_D3DXMatrixfDeterminant(const D3DXMATRIX *matrix);
D3DXPLANE * __stdcall c_D3DXPlaneFromPointNormal(D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal);
D3DXPLANE * __stdcall c_D3DXPlaneFromPoints(D3DXPLANE *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c);
D3DXVECTOR3 * __stdcall c_D3DXVec3Project(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world);
D3DXVECTOR3 * __stdcall c_D3DXVec3Unproject(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world);
D3DXVECTOR4 * __stdcall c_D3DXVec4Cross(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c);
D3DXVECTOR2 * __stdcall c_D3DXVec2Hermite(D3DXVECTOR2 *out, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *t1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *t2, FLOAT t);
D3DXMATRIX * __stdcall c_D3DXMatrixInverse(D3DXMATRIX *out, FLOAT *determinant, const D3DXMATRIX *matrix);
D3DXQUATERNION * __stdcall c_D3DXQuaternionMultiply(D3DXQUATERNION *out, const D3DXQUATERNION *left, const D3DXQUATERNION *right);
D3DXQUATERNION * __stdcall c_D3DXQuaternionNormalize(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
D3DXPLANE * __stdcall c_D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *plane);
D3DXVECTOR3 * __stdcall c_D3DXPlaneIntersectLine(D3DXVECTOR3 *out, const D3DXPLANE *plane, const D3DXVECTOR3 *start, const D3DXVECTOR3 *end);
void __stdcall c_D3DXQuaternionToAxisAngle(const D3DXQUATERNION *rotation, D3DXVECTOR3 *axis, FLOAT *angle);
D3DXQUATERNION * __stdcall c_D3DXQuaternionRotationMatrix(D3DXQUATERNION *out, const D3DXMATRIX *matrix);
D3DXQUATERNION * __stdcall c_D3DXQuaternionRotationYawPitchRoll(D3DXQUATERNION *out, FLOAT yaw, FLOAT pitch, FLOAT roll);
D3DXMATRIX * __stdcall c_D3DXMatrixTranslation(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z);
D3DXMATRIX * __stdcall c_D3DXMatrixShadow(D3DXMATRIX *out, const D3DXVECTOR4 *light, const D3DXPLANE *plane);
D3DXMATRIX * __stdcall c_D3DXMatrixReflect(D3DXMATRIX *out, const D3DXPLANE *plane);
D3DXQUATERNION * __stdcall c_D3DXQuaternionRotationAxis(D3DXQUATERNION *out, const D3DXVECTOR3 *axis, FLOAT angle);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationX(D3DXMATRIX *out, FLOAT angle);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationY(D3DXMATRIX *out, FLOAT angle);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationZ(D3DXMATRIX *out, FLOAT angle);
D3DXMATRIX * __stdcall c_D3DXMatrixScaling(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z);
D3DXPLANE * __stdcall c_D3DXPlaneTransform(D3DXPLANE *out, const D3DXPLANE *plane, const D3DXMATRIX *matrix);
D3DXQUATERNION * __stdcall c_D3DXQuaternionSlerp(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, FLOAT t);
D3DXQUATERNION * __stdcall c_D3DXQuaternionBaryCentric(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, FLOAT f, FLOAT g);
D3DXMATRIX * __stdcall c_D3DXMatrixTranspose(D3DXMATRIX *out, const D3DXMATRIX *matrix);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationQuaternion(D3DXMATRIX *out, const D3DXQUATERNION *rotation);
D3DXMATRIX * __stdcall c_D3DXMatrixTransformation(D3DXMATRIX *out, const D3DXVECTOR3 *scalingCenter, const D3DXQUATERNION *scalingRotation, const D3DXVECTOR3 *scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationYawPitchRoll(D3DXMATRIX *out, FLOAT yaw, FLOAT pitch, FLOAT roll);
D3DXMATRIX * __stdcall c_D3DXMatrixAffineTransformation(D3DXMATRIX *out, FLOAT scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation);
D3DXMATRIX * __stdcall c_D3DXMatrixRotationAxis(D3DXMATRIX *out, const D3DXVECTOR3 *axis, FLOAT angle);
D3DXQUATERNION * __stdcall c_D3DXQuaternionSquad(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, const D3DXQUATERNION *d, FLOAT t);
D3DXQUATERNION * __stdcall c_D3DXQuaternionInverse(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
void __stdcall c_D3DXQuaternionSquadSetup(D3DXQUATERNION *outA, D3DXQUATERNION *outB, D3DXQUATERNION *outC, const D3DXQUATERNION *q0, const D3DXQUATERNION *q1, const D3DXQUATERNION *q2, const D3DXQUATERNION *q3);
D3DXVECTOR2 * __stdcall c_D3DXVec2Normalize(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector);
D3DXVECTOR2 * __stdcall c_D3DXVec2CatmullRom(D3DXVECTOR2 *out, const D3DXVECTOR2 *p0, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *p3, FLOAT t);
D3DXVECTOR2 * __stdcall c_D3DXVec2BaryCentric(D3DXVECTOR2 *out, const D3DXVECTOR2 *a, const D3DXVECTOR2 *b, const D3DXVECTOR2 *c, FLOAT f, FLOAT g);
D3DXVECTOR3 * __stdcall c_D3DXVec3Hermite(D3DXVECTOR3 *out, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *t1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *t2, FLOAT t);
D3DXVECTOR3 * __stdcall c_D3DXVec3CatmullRom(D3DXVECTOR3 *out, const D3DXVECTOR3 *p0, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3, FLOAT t);
D3DXVECTOR3 * __stdcall c_D3DXVec3BaryCentric(D3DXVECTOR3 *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c, FLOAT f, FLOAT g);
D3DXVECTOR4 * __stdcall c_D3DXVec4Hermite(D3DXVECTOR4 *out, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *t1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *t2, FLOAT t);
D3DXVECTOR4 * __stdcall c_D3DXVec4CatmullRom(D3DXVECTOR4 *out, const D3DXVECTOR4 *p0, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *p3, FLOAT t);
D3DXVECTOR4 * __stdcall c_D3DXVec4BaryCentric(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c, FLOAT f, FLOAT g);

// The first call selects a CPU table and completes through the scalar routine.

D3DXVECTOR4 * __stdcall init_D3DXVec2Transform(D3DXVECTOR4 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2Transform(out, vector, matrix);
}

D3DXVECTOR4 * __stdcall init_D3DXVec3Transform(D3DXVECTOR4 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3Transform(out, vector, matrix);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4Transform(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4Transform(out, vector, matrix);
}

D3DXMATRIX * __stdcall init_D3DXMatrixMultiply(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixMultiply(out, left, right);
}

D3DXMATRIX * __stdcall init_D3DXMatrixMultiplyTranspose(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixMultiplyTranspose(out, left, right);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2TransformNormal(D3DXVECTOR2 *out, const D3DXVECTOR2 *normal, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2TransformNormal(out, normal, matrix);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3TransformNormal(D3DXVECTOR3 *out, const D3DXVECTOR3 *normal, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3TransformNormal(out, normal, matrix);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3Normalize(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3Normalize(out, vector);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4Normalize(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4Normalize(out, vector);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2TransformCoord(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2TransformCoord(out, vector, matrix);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3TransformCoord(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3TransformCoord(out, vector, matrix);
}

FLOAT __stdcall init_D3DXMatrixfDeterminant(const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixfDeterminant(matrix);
}

D3DXPLANE * __stdcall init_D3DXPlaneFromPointNormal(D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal)
{
    D3DXCpuOptimizations(1);
    return c_D3DXPlaneFromPointNormal(out, point, normal);
}

D3DXPLANE * __stdcall init_D3DXPlaneFromPoints(D3DXPLANE *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c)
{
    D3DXCpuOptimizations(1);
    return c_D3DXPlaneFromPoints(out, a, b, c);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3Project(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3Project(out, vector, viewport, projection, view, world);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3Unproject(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3Unproject(out, vector, viewport, projection, view, world);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4Cross(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4Cross(out, a, b, c);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2Hermite(D3DXVECTOR2 *out, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *t1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *t2, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2Hermite(out, p1, t1, p2, t2, t);
}

D3DXMATRIX * __stdcall init_D3DXMatrixInverse(D3DXMATRIX *out, FLOAT *determinant, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixInverse(out, determinant, matrix);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionMultiply(D3DXQUATERNION *out, const D3DXQUATERNION *left, const D3DXQUATERNION *right)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionMultiply(out, left, right);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionNormalize(D3DXQUATERNION *out, const D3DXQUATERNION *rotation)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionNormalize(out, rotation);
}

D3DXPLANE * __stdcall init_D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *plane)
{
    D3DXCpuOptimizations(1);
    return c_D3DXPlaneNormalize(out, plane);
}

D3DXVECTOR3 * __stdcall init_D3DXPlaneIntersectLine(D3DXVECTOR3 *out, const D3DXPLANE *plane, const D3DXVECTOR3 *start, const D3DXVECTOR3 *end)
{
    D3DXCpuOptimizations(1);
    return c_D3DXPlaneIntersectLine(out, plane, start, end);
}

void __stdcall init_D3DXQuaternionToAxisAngle(const D3DXQUATERNION *rotation, D3DXVECTOR3 *axis, FLOAT *angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionToAxisAngle(rotation, axis, angle);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionRotationMatrix(D3DXQUATERNION *out, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionRotationMatrix(out, matrix);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionRotationYawPitchRoll(D3DXQUATERNION *out, FLOAT yaw, FLOAT pitch, FLOAT roll)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionRotationYawPitchRoll(out, yaw, pitch, roll);
}

D3DXMATRIX * __stdcall init_D3DXMatrixTranslation(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixTranslation(out, x, y, z);
}

D3DXMATRIX * __stdcall init_D3DXMatrixShadow(D3DXMATRIX *out, const D3DXVECTOR4 *light, const D3DXPLANE *plane)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixShadow(out, light, plane);
}

D3DXMATRIX * __stdcall init_D3DXMatrixReflect(D3DXMATRIX *out, const D3DXPLANE *plane)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixReflect(out, plane);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionRotationAxis(D3DXQUATERNION *out, const D3DXVECTOR3 *axis, FLOAT angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionRotationAxis(out, axis, angle);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationX(D3DXMATRIX *out, FLOAT angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationX(out, angle);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationY(D3DXMATRIX *out, FLOAT angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationY(out, angle);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationZ(D3DXMATRIX *out, FLOAT angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationZ(out, angle);
}

D3DXMATRIX * __stdcall init_D3DXMatrixScaling(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixScaling(out, x, y, z);
}

D3DXPLANE * __stdcall init_D3DXPlaneTransform(D3DXPLANE *out, const D3DXPLANE *plane, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXPlaneTransform(out, plane, matrix);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionSlerp(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionSlerp(out, a, b, t);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionBaryCentric(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, FLOAT f, FLOAT g)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionBaryCentric(out, a, b, c, f, g);
}

D3DXMATRIX * __stdcall init_D3DXMatrixTranspose(D3DXMATRIX *out, const D3DXMATRIX *matrix)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixTranspose(out, matrix);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationQuaternion(D3DXMATRIX *out, const D3DXQUATERNION *rotation)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationQuaternion(out, rotation);
}

D3DXMATRIX * __stdcall init_D3DXMatrixTransformation(D3DXMATRIX *out, const D3DXVECTOR3 *scalingCenter, const D3DXQUATERNION *scalingRotation, const D3DXVECTOR3 *scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixTransformation(out, scalingCenter, scalingRotation, scaling, rotationCenter, rotation, translation);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationYawPitchRoll(D3DXMATRIX *out, FLOAT yaw, FLOAT pitch, FLOAT roll)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationYawPitchRoll(out, yaw, pitch, roll);
}

D3DXMATRIX * __stdcall init_D3DXMatrixAffineTransformation(D3DXMATRIX *out, FLOAT scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixAffineTransformation(out, scaling, rotationCenter, rotation, translation);
}

D3DXMATRIX * __stdcall init_D3DXMatrixRotationAxis(D3DXMATRIX *out, const D3DXVECTOR3 *axis, FLOAT angle)
{
    D3DXCpuOptimizations(1);
    return c_D3DXMatrixRotationAxis(out, axis, angle);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionSquad(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, const D3DXQUATERNION *d, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionSquad(out, a, b, c, d, t);
}

D3DXQUATERNION * __stdcall init_D3DXQuaternionInverse(D3DXQUATERNION *out, const D3DXQUATERNION *rotation)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionInverse(out, rotation);
}

void __stdcall init_D3DXQuaternionSquadSetup(D3DXQUATERNION *outA, D3DXQUATERNION *outB, D3DXQUATERNION *outC, const D3DXQUATERNION *q0, const D3DXQUATERNION *q1, const D3DXQUATERNION *q2, const D3DXQUATERNION *q3)
{
    D3DXCpuOptimizations(1);
    return c_D3DXQuaternionSquadSetup(outA, outB, outC, q0, q1, q2, q3);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2Normalize(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2Normalize(out, vector);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2CatmullRom(D3DXVECTOR2 *out, const D3DXVECTOR2 *p0, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *p3, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2CatmullRom(out, p0, p1, p2, p3, t);
}

D3DXVECTOR2 * __stdcall init_D3DXVec2BaryCentric(D3DXVECTOR2 *out, const D3DXVECTOR2 *a, const D3DXVECTOR2 *b, const D3DXVECTOR2 *c, FLOAT f, FLOAT g)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec2BaryCentric(out, a, b, c, f, g);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3Hermite(D3DXVECTOR3 *out, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *t1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *t2, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3Hermite(out, p1, t1, p2, t2, t);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3CatmullRom(D3DXVECTOR3 *out, const D3DXVECTOR3 *p0, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3CatmullRom(out, p0, p1, p2, p3, t);
}

D3DXVECTOR3 * __stdcall init_D3DXVec3BaryCentric(D3DXVECTOR3 *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c, FLOAT f, FLOAT g)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec3BaryCentric(out, a, b, c, f, g);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4Hermite(D3DXVECTOR4 *out, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *t1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *t2, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4Hermite(out, p1, t1, p2, t2, t);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4CatmullRom(D3DXVECTOR4 *out, const D3DXVECTOR4 *p0, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *p3, FLOAT t)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4CatmullRom(out, p0, p1, p2, p3, t);
}

D3DXVECTOR4 * __stdcall init_D3DXVec4BaryCentric(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c, FLOAT f, FLOAT g)
{
    D3DXCpuOptimizations(1);
    return c_D3DXVec4BaryCentric(out, a, b, c, f, g);
}

// Public entry points dispatch through the currently selected table.

extern "C" D3DXVECTOR4 * __stdcall D3DXVec2Transform(D3DXVECTOR4 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix)
{
    return g_D3DXFastTable.Vec2Transform(out, vector, matrix);
}

extern "C" D3DXMATRIX * __stdcall D3DXMatrixMultiply(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right)
{
    return g_D3DXFastTable.MatrixMultiply(out, left, right);
}

extern "C" D3DXVECTOR3 * __stdcall D3DXVec3Normalize(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector)
{
    return g_D3DXFastTable.Vec3Normalize(out, vector);
}

extern "C" D3DXVECTOR3 * __stdcall D3DXVec3TransformCoord(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix)
{
    return g_D3DXFastTable.Vec3TransformCoord(out, vector, matrix);
}

extern "C" D3DXMATRIX * __stdcall D3DXMatrixInverse(D3DXMATRIX *out, FLOAT *determinant, const D3DXMATRIX *matrix)
{
    return g_D3DXFastTable.MatrixInverse(out, determinant, matrix);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionMultiply(D3DXQUATERNION *out, const D3DXQUATERNION *left, const D3DXQUATERNION *right)
{
    return g_D3DXFastTable.QuaternionMultiply(out, left, right);
}

extern "C" D3DXPLANE * __stdcall D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *plane)
{
    return g_D3DXFastTable.PlaneNormalize(out, plane);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionRotationYawPitchRoll(D3DXQUATERNION *out, FLOAT yaw, FLOAT pitch, FLOAT roll)
{
    return g_D3DXFastTable.QuaternionRotationYawPitchRoll(out, yaw, pitch, roll);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionSlerp(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, FLOAT t)
{
    return g_D3DXFastTable.QuaternionSlerp(out, a, b, t);
}

extern "C" D3DXMATRIX * __stdcall D3DXMatrixTranspose(D3DXMATRIX *out, const D3DXMATRIX *matrix)
{
    return g_D3DXFastTable.MatrixTranspose(out, matrix);
}

extern "C" D3DXMATRIX * __stdcall D3DXMatrixRotationQuaternion(D3DXMATRIX *out, const D3DXQUATERNION *rotation)
{
    return g_D3DXFastTable.MatrixRotationQuaternion(out, rotation);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionInverse(D3DXQUATERNION *out, const D3DXQUATERNION *rotation)
{
    return g_D3DXFastTable.QuaternionInverse(out, rotation);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionLn(D3DXQUATERNION *out, const D3DXQUATERNION *rotation)
{
    return g_D3DXFastTable.QuaternionLn(out, rotation);
}

extern "C" D3DXQUATERNION * __stdcall D3DXQuaternionExp(D3DXQUATERNION *out, const D3DXQUATERNION *rotation)
{
    return g_D3DXFastTable.QuaternionExp(out, rotation);
}
