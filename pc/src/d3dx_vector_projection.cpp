#include "d3dx_matrix_identity.h"
#include "d3d8_viewport.h"

extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(
    D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(
    D3DXMATRIX *out, FLOAT *determinant, const D3DXMATRIX *matrix);
extern "C" D3DXVECTOR3 *__stdcall D3DXVec3TransformCoord(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *vector, const D3DXMATRIX *matrix);

enum TransformBits {
    HasProjection = 1,
    HasView = 2,
    HasWorld = 4
};

static inline unsigned TransformMask(
    const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world)
{
    return ((world != 0) << 2) | ((view != 0) << 1) | (projection != 0);
}

/* Transform into clip space, then map to the viewport when supplied. */
D3DXVECTOR3 *__stdcall c_D3DXVec3Project(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *input, const D3DVIEWPORT8 *viewport,
    const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world)
{
    D3DXMATRIXA16 combined;
    const D3DXMATRIX *matrix = &combined;

    switch (TransformMask(projection, view, world)) {
    case 0:
        MatrixIdentity(&combined);
        break;
    case HasProjection:
        matrix = projection;
        break;
    case HasView:
        matrix = view;
        break;
    case HasView | HasProjection:
        D3DXMatrixMultiply(&combined, view, projection);
        break;
    case HasWorld:
        matrix = world;
        break;
    case HasWorld | HasProjection:
        D3DXMatrixMultiply(&combined, world, projection);
        break;
    case HasWorld | HasView:
        D3DXMatrixMultiply(&combined, world, view);
        break;
    case HasWorld | HasView | HasProjection:
        D3DXMatrixMultiply(&combined, world, view);
        D3DXMatrixMultiply(&combined, &combined, projection);
        break;
    }

    D3DXVec3TransformCoord(out, input, matrix);
    if (viewport) {
        out->x = (out->x + 1.0f) * viewport->Width * 0.5f + viewport->X;
        out->y = (1.0f - out->y) * viewport->Height * 0.5f + viewport->Y;
        out->z = out->z * (viewport->MaxZ - viewport->MinZ) + viewport->MinZ;
    }

    return out;
}

/* Undo the viewport mapping and transform back through the inverse matrix. */
D3DXVECTOR3 *__stdcall c_D3DXVec3Unproject(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *input, const D3DVIEWPORT8 *viewport,
    const D3DXMATRIX *projection, const D3DXMATRIX *view, const D3DXMATRIX *world)
{
    D3DXMATRIXA16 combined;

    switch (TransformMask(projection, view, world)) {
    case 0:
        MatrixIdentity(&combined);
        break;
    case HasProjection:
        D3DXMatrixInverse(&combined, 0, projection);
        break;
    case HasView:
        D3DXMatrixInverse(&combined, 0, view);
        break;
    case HasView | HasProjection:
        D3DXMatrixMultiply(&combined, view, projection);
        D3DXMatrixInverse(&combined, 0, &combined);
        break;
    case HasWorld:
        D3DXMatrixInverse(&combined, 0, world);
        break;
    case HasWorld | HasProjection:
        D3DXMatrixMultiply(&combined, world, projection);
        D3DXMatrixInverse(&combined, 0, &combined);
        break;
    case HasWorld | HasView:
        D3DXMatrixMultiply(&combined, world, view);
        D3DXMatrixInverse(&combined, 0, &combined);
        break;
    case HasWorld | HasView | HasProjection:
        D3DXMatrixMultiply(&combined, world, view);
        D3DXMatrixMultiply(&combined, &combined, projection);
        D3DXMatrixInverse(&combined, 0, &combined);
        break;
    }

    if (viewport) {
        out->x = (input->x - viewport->X) / viewport->Width * 2.0f - 1.0f;
        out->y = -((input->y - viewport->Y) / viewport->Height * 2.0f - 1.0f);
        out->z = (input->z - viewport->MinZ) / (viewport->MaxZ - viewport->MinZ);
        D3DXVec3TransformCoord(out, out, &combined);
    } else {
        D3DXVec3TransformCoord(out, input, &combined);
    }

    return out;
}
