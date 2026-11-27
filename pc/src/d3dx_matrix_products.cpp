/* Scalar D3DX8 matrix products. */
#include "d3dx_math_types.h"

/* Dot a row of the left matrix with a column of the right matrix. */
static inline FLOAT MatrixProductEntry(
    const D3DXMATRIX *left, const D3DXMATRIX *right, int row, int column)
{
    return left->m[row][0] * right->m[0][column]
         + left->m[row][1] * right->m[1][column]
         + left->m[row][2] * right->m[2][column]
         + left->m[row][3] * right->m[3][column];
}

/* Preserve both operands when the caller requests an in-place product. */
D3DXMATRIX *__stdcall c_D3DXMatrixMultiply(
    D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right)
{
    D3DXMATRIX temporary;
    D3DXMATRIX *result = (out == left || out == right) ? &temporary : out;

    result->m[0][0] = MatrixProductEntry(left, right, 0, 0);
    result->m[0][1] = MatrixProductEntry(left, right, 0, 1);
    result->m[0][2] = MatrixProductEntry(left, right, 0, 2);
    result->m[0][3] = MatrixProductEntry(left, right, 0, 3);

    result->m[1][0] = MatrixProductEntry(left, right, 1, 0);
    result->m[1][1] = MatrixProductEntry(left, right, 1, 1);
    result->m[1][2] = MatrixProductEntry(left, right, 1, 2);
    result->m[1][3] = MatrixProductEntry(left, right, 1, 3);

    result->m[2][0] = MatrixProductEntry(left, right, 2, 0);
    result->m[2][1] = MatrixProductEntry(left, right, 2, 1);
    result->m[2][2] = MatrixProductEntry(left, right, 2, 2);
    result->m[2][3] = MatrixProductEntry(left, right, 2, 3);

    result->m[3][0] = MatrixProductEntry(left, right, 3, 0);
    result->m[3][1] = MatrixProductEntry(left, right, 3, 1);
    result->m[3][2] = MatrixProductEntry(left, right, 3, 2);
    result->m[3][3] = MatrixProductEntry(left, right, 3, 3);

    if (result != out) {
        *out = *result;
    }
    return out;
}

/* Write the transposed product directly, preserving aliased inputs. */
D3DXMATRIX *__stdcall c_D3DXMatrixMultiplyTranspose(
    D3DXMATRIX *out, const D3DXMATRIX *left, const D3DXMATRIX *right)
{
    D3DXMATRIX temporary;
    D3DXMATRIX *result = (out == left || out == right) ? &temporary : out;

    result->m[0][0] = MatrixProductEntry(left, right, 0, 0);
    result->m[0][1] = MatrixProductEntry(left, right, 1, 0);
    result->m[0][2] = MatrixProductEntry(left, right, 2, 0);
    result->m[0][3] = MatrixProductEntry(left, right, 3, 0);

    result->m[1][0] = MatrixProductEntry(left, right, 0, 1);
    result->m[1][1] = MatrixProductEntry(left, right, 1, 1);
    result->m[1][2] = MatrixProductEntry(left, right, 2, 1);
    result->m[1][3] = MatrixProductEntry(left, right, 3, 1);

    result->m[2][0] = MatrixProductEntry(left, right, 0, 2);
    result->m[2][1] = MatrixProductEntry(left, right, 1, 2);
    result->m[2][2] = MatrixProductEntry(left, right, 2, 2);
    result->m[2][3] = MatrixProductEntry(left, right, 3, 2);

    result->m[3][0] = MatrixProductEntry(left, right, 0, 3);
    result->m[3][1] = MatrixProductEntry(left, right, 1, 3);
    result->m[3][2] = MatrixProductEntry(left, right, 2, 3);
    result->m[3][3] = MatrixProductEntry(left, right, 3, 3);

    if (result != out) {
        *out = *result;
    }
    return out;
}
