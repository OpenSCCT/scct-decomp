#include "d3dx_math_types.h"

/* The last two rows supply the six 2-by-2 minors for expansion along the first row. */
FLOAT __stdcall c_D3DXMatrixfDeterminant(const D3DXMATRIX *matrix)
{
    const FLOAT &m11 = matrix->m[0][0], &m21 = matrix->m[1][0],
                &m31 = matrix->m[2][0], &m41 = matrix->m[3][0];
    const FLOAT &m12 = matrix->m[0][1], &m22 = matrix->m[1][1],
                &m32 = matrix->m[2][1], &m42 = matrix->m[3][1];
    const FLOAT &m13 = matrix->m[0][2], &m23 = matrix->m[1][2],
                &m33 = matrix->m[2][2], &m43 = matrix->m[3][2];
    const FLOAT &m14 = matrix->m[0][3], &m24 = matrix->m[1][3],
                &m34 = matrix->m[2][3], &m44 = matrix->m[3][3];

    const FLOAT minor34 = m33 * m44 - m34 * m43;
    const FLOAT minor24 = m32 * m44 - m34 * m42;
    const FLOAT minor23 = m32 * m43 - m33 * m42;
    const FLOAT minor14 = m31 * m44 - m34 * m41;
    const FLOAT minor13 = m31 * m43 - m33 * m41;
    const FLOAT minor12 = m31 * m42 - m32 * m41;

    return m11 * (m22 * minor34 - m23 * minor24 + m24 * minor23)
         - m12 * (m21 * minor34 - m23 * minor14 + m24 * minor13)
         + m13 * (m21 * minor24 - m22 * minor14 + m24 * minor12)
         - m14 * (m21 * minor23 - m22 * minor13 + m23 * minor12);
}
