#ifndef D3DX_FAST_TABLE_H
#define D3DX_FAST_TABLE_H

#include "d3dx_math_types.h"
#include "d3d8_viewport.h"

struct D3DXFASTTABLE {
    D3DXVECTOR4 * (__stdcall *Vec2Transform)(D3DXVECTOR4 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix);
    D3DXVECTOR4 * (__stdcall *Vec3Transform)(D3DXVECTOR4 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);
    D3DXVECTOR4 * (__stdcall *Vec4Transform)(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector, const D3DXMATRIX *matrix);
    D3DXMATRIX * (__stdcall *MatrixMultiply)(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right);
    D3DXMATRIX * (__stdcall *MatrixMultiplyTranspose)(D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right);
    D3DXVECTOR2 * (__stdcall *Vec2TransformNormal)(D3DXVECTOR2 *out, const D3DXVECTOR2 *normal, const D3DXMATRIX *matrix);
    D3DXVECTOR3 * (__stdcall *Vec3TransformNormal)(D3DXVECTOR3 *out, const D3DXVECTOR3 *normal, const D3DXMATRIX *matrix);
    D3DXVECTOR3 * (__stdcall *Vec3Normalize)(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector);
    D3DXVECTOR4 * (__stdcall *Vec4Normalize)(D3DXVECTOR4 *out, const D3DXVECTOR4 *vector);
    D3DXVECTOR2 * (__stdcall *Vec2TransformCoord)(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector, const D3DXMATRIX *matrix);
    D3DXVECTOR3 * (__stdcall *Vec3TransformCoord)(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);
    FLOAT (__stdcall *MatrixfDeterminant)(const D3DXMATRIX *matrix);
    D3DXPLANE * (__stdcall *PlaneFromPointNormal)(D3DXPLANE *out, const D3DXVECTOR3 *point, const D3DXVECTOR3 *normal);
    D3DXPLANE * (__stdcall *PlaneFromPoints)(D3DXPLANE *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c);
    D3DXVECTOR3 * (__stdcall *Vec3Project)(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world);
    D3DXVECTOR3 * (__stdcall *Vec3Unproject)(D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DVIEWPORT8 *viewport, const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world);
    D3DXVECTOR4 * (__stdcall *Vec4Cross)(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c);
    D3DXVECTOR2 * (__stdcall *Vec2Hermite)(D3DXVECTOR2 *out, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *t1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *t2, FLOAT t);
    D3DXMATRIX * (__stdcall *MatrixInverse)(D3DXMATRIX *out, FLOAT *determinant, const D3DXMATRIX *matrix);
    D3DXQUATERNION * (__stdcall *QuaternionMultiply)(D3DXQUATERNION *out, const D3DXQUATERNION *left, const D3DXQUATERNION *right);
    D3DXQUATERNION * (__stdcall *QuaternionNormalize)(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
    D3DXPLANE * (__stdcall *PlaneNormalize)(D3DXPLANE *out, const D3DXPLANE *plane);
    D3DXVECTOR3 * (__stdcall *PlaneIntersectLine)(D3DXVECTOR3 *out, const D3DXPLANE *plane, const D3DXVECTOR3 *start, const D3DXVECTOR3 *end);
    void (__stdcall *QuaternionToAxisAngle)(const D3DXQUATERNION *rotation, D3DXVECTOR3 *axis, FLOAT *angle);
    D3DXQUATERNION * (__stdcall *QuaternionRotationMatrix)(D3DXQUATERNION *out, const D3DXMATRIX *matrix);
    D3DXQUATERNION * (__stdcall *QuaternionRotationYawPitchRoll)(D3DXQUATERNION *out, FLOAT yaw, FLOAT pitch, FLOAT roll);
    D3DXMATRIX * (__stdcall *MatrixTranslation)(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z);
    D3DXMATRIX * (__stdcall *MatrixShadow)(D3DXMATRIX *out, const D3DXVECTOR4 *light, const D3DXPLANE *plane);
    D3DXMATRIX * (__stdcall *MatrixReflect)(D3DXMATRIX *out, const D3DXPLANE *plane);
    D3DXQUATERNION * (__stdcall *QuaternionRotationAxis)(D3DXQUATERNION *out, const D3DXVECTOR3 *axis, FLOAT angle);
    D3DXMATRIX * (__stdcall *MatrixRotationX)(D3DXMATRIX *out, FLOAT angle);
    D3DXMATRIX * (__stdcall *MatrixRotationY)(D3DXMATRIX *out, FLOAT angle);
    D3DXMATRIX * (__stdcall *MatrixRotationZ)(D3DXMATRIX *out, FLOAT angle);
    D3DXMATRIX * (__stdcall *MatrixScaling)(D3DXMATRIX *out, FLOAT x, FLOAT y, FLOAT z);
    D3DXPLANE * (__stdcall *PlaneTransform)(D3DXPLANE *out, const D3DXPLANE *plane, const D3DXMATRIX *matrix);
    D3DXQUATERNION * (__stdcall *QuaternionSlerp)(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, FLOAT t);
    D3DXQUATERNION * (__stdcall *QuaternionBaryCentric)(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, FLOAT f, FLOAT g);
    D3DXMATRIX * (__stdcall *MatrixTranspose)(D3DXMATRIX *out, const D3DXMATRIX *matrix);
    D3DXMATRIX * (__stdcall *MatrixRotationQuaternion)(D3DXMATRIX *out, const D3DXQUATERNION *rotation);
    D3DXMATRIX * (__stdcall *MatrixTransformation)(D3DXMATRIX *out, const D3DXVECTOR3 *scalingCenter, const D3DXQUATERNION *scalingRotation, const D3DXVECTOR3 *scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation);
    D3DXMATRIX * (__stdcall *MatrixRotationYawPitchRoll)(D3DXMATRIX *out, FLOAT yaw, FLOAT pitch, FLOAT roll);
    D3DXMATRIX * (__stdcall *MatrixAffineTransformation)(D3DXMATRIX *out, FLOAT scaling, const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation);
    D3DXMATRIX * (__stdcall *MatrixRotationAxis)(D3DXMATRIX *out, const D3DXVECTOR3 *axis, FLOAT angle);
    D3DXQUATERNION * (__stdcall *QuaternionSquad)(D3DXQUATERNION *out, const D3DXQUATERNION *a, const D3DXQUATERNION *b, const D3DXQUATERNION *c, const D3DXQUATERNION *d, FLOAT t);
    D3DXQUATERNION * (__stdcall *QuaternionInverse)(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
    void (__stdcall *QuaternionSquadSetup)(D3DXQUATERNION *outA, D3DXQUATERNION *outB, D3DXQUATERNION *outC, const D3DXQUATERNION *q0, const D3DXQUATERNION *q1, const D3DXQUATERNION *q2, const D3DXQUATERNION *q3);
    D3DXVECTOR2 * (__stdcall *Vec2Normalize)(D3DXVECTOR2 *out, const D3DXVECTOR2 *vector);
    D3DXVECTOR2 * (__stdcall *Vec2CatmullRom)(D3DXVECTOR2 *out, const D3DXVECTOR2 *p0, const D3DXVECTOR2 *p1, const D3DXVECTOR2 *p2, const D3DXVECTOR2 *p3, FLOAT t);
    D3DXVECTOR2 * (__stdcall *Vec2BaryCentric)(D3DXVECTOR2 *out, const D3DXVECTOR2 *a, const D3DXVECTOR2 *b, const D3DXVECTOR2 *c, FLOAT f, FLOAT g);
    D3DXVECTOR3 * (__stdcall *Vec3Hermite)(D3DXVECTOR3 *out, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *t1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *t2, FLOAT t);
    D3DXVECTOR3 * (__stdcall *Vec3CatmullRom)(D3DXVECTOR3 *out, const D3DXVECTOR3 *p0, const D3DXVECTOR3 *p1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3, FLOAT t);
    D3DXVECTOR3 * (__stdcall *Vec3BaryCentric)(D3DXVECTOR3 *out, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b, const D3DXVECTOR3 *c, FLOAT f, FLOAT g);
    D3DXVECTOR4 * (__stdcall *Vec4Hermite)(D3DXVECTOR4 *out, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *t1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *t2, FLOAT t);
    D3DXVECTOR4 * (__stdcall *Vec4CatmullRom)(D3DXVECTOR4 *out, const D3DXVECTOR4 *p0, const D3DXVECTOR4 *p1, const D3DXVECTOR4 *p2, const D3DXVECTOR4 *p3, FLOAT t);
    D3DXVECTOR4 * (__stdcall *Vec4BaryCentric)(D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c, FLOAT f, FLOAT g);
    D3DXQUATERNION * (__stdcall *QuaternionLn)(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
    D3DXQUATERNION * (__stdcall *QuaternionExp)(D3DXQUATERNION *out, const D3DXQUATERNION *rotation);
};

extern D3DXFASTTABLE g_D3DXFastTable;
// The selector returns the optimization state kept by the library.
enum _D3DX_CPU_OPTIMIZATION {
    D3DX_NO_OPTIMIZATION = 0,
    D3DX_3DNOW_OPTIMIZATION = 1,
    D3DX_SSE2_OPTIMIZATION = 2,
    D3DX_SSE_OPTIMIZATION = 3,
    D3DX_OPTIMIZATION_UNSELECTED = 0xffff
};

typedef _D3DX_CPU_OPTIMIZATION D3DX_CPU_OPTIMIZATION;
extern "C" D3DX_CPU_OPTIMIZATION __stdcall D3DXCpuOptimizations(BOOL enable);

#endif
