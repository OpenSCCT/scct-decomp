#include "d3dx_matrix_identity.h"

extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX *, const D3DXMATRIX *, const D3DXMATRIX *);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranspose(D3DXMATRIX *, const D3DXMATRIX *);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationQuaternion(D3DXMATRIX *, const D3DXQUATERNION *);

static __forceinline void ApplyRotation(
    D3DXMATRIX *out, D3DXMATRIX *rotationMatrix,
    const D3DXVECTOR3 *center, const D3DXQUATERNION *rotation)
{
    if (rotation) {
        D3DXMatrixRotationQuaternion(rotationMatrix, rotation);
        if (center) {
            out->m[3][0] -= center->x;
            out->m[3][1] -= center->y;
            out->m[3][2] -= center->z;
            D3DXMatrixMultiply(out, out, rotationMatrix);
            out->m[3][0] += center->x;
            out->m[3][1] += center->y;
            out->m[3][2] += center->z;
        } else {
            D3DXMatrixMultiply(out, out, rotationMatrix);
        }
    }
}

static inline void ApplyTranslation(D3DXMATRIX *out, const D3DXVECTOR3 *translation)
{
    if (translation) {
        out->m[3][0] += translation->x;
        out->m[3][1] += translation->y;
        out->m[3][2] += translation->z;
    }
}

D3DXMATRIX *__stdcall c_D3DXMatrixAffineTransformation(
    D3DXMATRIX *out, float scaling, const D3DXVECTOR3 *center,
    const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation)
{
    D3DXMATRIXA16 rotationMatrix;
    ZeroOffDiagonal(out);
    out->m[2][2] = out->m[1][1] = out->m[0][0] = scaling;
    out->m[3][3] = 1.0f;
    ApplyRotation(out, &rotationMatrix, center, rotation);
    ApplyTranslation(out, translation);
    return out;
}

D3DXMATRIX *__stdcall c_D3DXMatrixTransformation(
    D3DXMATRIX *out, const D3DXVECTOR3 *scalingCenter,
    const D3DXQUATERNION *scalingRotation, const D3DXVECTOR3 *scaling,
    const D3DXVECTOR3 *rotationCenter, const D3DXQUATERNION *rotation,
    const D3DXVECTOR3 *translation)
{
    D3DXMATRIXA16 scaleMatrix, rotationMatrix, inverseRotationMatrix;

    if (scaling) {
        if (scalingRotation) {
            ZeroOffDiagonal(&scaleMatrix);
            scaleMatrix.m[0][0] = scaling->x;
            scaleMatrix.m[1][1] = scaling->y;
            scaleMatrix.m[2][2] = scaling->z;
            scaleMatrix.m[3][3] = 1.0f;
            D3DXMatrixRotationQuaternion(&rotationMatrix, scalingRotation);
            if (scalingCenter) {
                const D3DXVECTOR3 &center = *scalingCenter;
                D3DXMatrixTranspose(&inverseRotationMatrix, &rotationMatrix);
                MatrixIdentity(out);
                out->m[3][0] = -center.x;
                out->m[3][1] = -center.y;
                out->m[3][2] = -center.z;
                D3DXMatrixMultiply(out, out, &inverseRotationMatrix);
                D3DXMatrixMultiply(out, out, &scaleMatrix);
                D3DXMatrixMultiply(out, out, &rotationMatrix);
                out->m[3][0] += center.x;
                out->m[3][1] += center.y;
                out->m[3][2] += center.z;
            } else {
                D3DXMatrixTranspose(out, &rotationMatrix);
                D3DXMatrixMultiply(out, out, &scaleMatrix);
                D3DXMatrixMultiply(out, out, &rotationMatrix);
            }
        } else {
            ZeroOffDiagonal(out);
            out->m[0][0] = scaling->x;
            out->m[1][1] = scaling->y;
            out->m[2][2] = scaling->z;
            out->m[3][3] = 1.0f;
        }
    } else {
        MatrixIdentity(out);
    }

    ApplyRotation(out, &rotationMatrix, rotationCenter, rotation);
    ApplyTranslation(out, translation);
    return out;
}
