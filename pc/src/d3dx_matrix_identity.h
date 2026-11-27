#ifndef D3DX_MATRIX_IDENTITY_H
#define D3DX_MATRIX_IDENTITY_H

#include "d3dx_math_types.h"

// The public D3DX8 aligned matrix type uses the same 16 floats as D3DXMATRIX.
struct __declspec(align(16)) D3DXMATRIXA16 : public D3DXMATRIX {};

// The off-diagonal entries are shared by identity and scaling initializers.
static __forceinline void ZeroOffDiagonal(D3DXMATRIX *m)
{
    m->m[0][1] = m->m[0][2] = m->m[0][3] =
        m->m[1][0] = m->m[1][2] = m->m[1][3] =
        m->m[2][0] = m->m[2][1] = m->m[2][3] =
        m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
}

static __forceinline void MatrixIdentity(D3DXMATRIX *m)
{
    ZeroOffDiagonal(m);
    m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0f;
}

#endif
