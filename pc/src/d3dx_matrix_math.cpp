/* d3dx_matrix_math.cpp -- D3DX8 matrix functions */

typedef float FLOAT;

struct D3DXMATRIX {
    FLOAT m[4][4];
};

struct D3DXQUATERNION {
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT w;
};

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionRotationYawPitchRoll(
    D3DXQUATERNION *pOut,
    FLOAT yaw,
    FLOAT pitch,
    FLOAT roll);

extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationQuaternion(
    D3DXMATRIX *pOut,
    const D3DXQUATERNION *pQ);

/* D3DXMatrixTranspose */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranspose(
    D3DXMATRIX *pOut,
    const D3DXMATRIX *pM)
{
    FLOAT value;

    value = pM->m[0][1];
    pOut->m[0][1] = pM->m[1][0];
    pOut->m[1][0] = value;
    value = pM->m[0][2];
    pOut->m[0][2] = pM->m[2][0];
    pOut->m[2][0] = value;
    value = pM->m[0][3];
    pOut->m[0][3] = pM->m[3][0];
    pOut->m[3][0] = value;
    value = pM->m[1][2];
    pOut->m[1][2] = pM->m[2][1];
    pOut->m[2][1] = value;
    value = pM->m[1][3];
    pOut->m[1][3] = pM->m[3][1];
    pOut->m[3][1] = value;
    value = pM->m[2][3];
    pOut->m[2][3] = pM->m[3][2];
    pOut->m[3][2] = value;
    if (pOut != pM) {
        pOut->m[0][0] = pM->m[0][0];
        pOut->m[1][1] = pM->m[1][1];
        pOut->m[2][2] = pM->m[2][2];
        pOut->m[3][3] = pM->m[3][3];
    }
    return pOut;
}

/* D3DXMatrixScaling */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixScaling(
    D3DXMATRIX *pOut,
    FLOAT sx,
    FLOAT sy,
    FLOAT sz)
{
    pOut->m[3][2] = 0.0f;
    pOut->m[0][0] = sx;
    pOut->m[3][1] = 0.0f;
    pOut->m[1][1] = sy;
    pOut->m[3][0] = 0.0f;
    pOut->m[2][2] = sz;
    pOut->m[2][3] = 0.0f;
    pOut->m[2][1] = 0.0f;
    pOut->m[2][0] = 0.0f;
    pOut->m[1][3] = 0.0f;
    pOut->m[1][2] = 0.0f;
    pOut->m[1][0] = 0.0f;
    pOut->m[0][3] = 0.0f;
    pOut->m[0][2] = 0.0f;
    pOut->m[0][1] = 0.0f;
    pOut->m[3][3] = 1.0f;
    return pOut;
}

/* D3DXMatrixTranslation */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranslation(
    D3DXMATRIX *pOut,
    FLOAT x,
    FLOAT y,
    FLOAT z)
{
    pOut->m[2][3] = 0.0f;
    pOut->m[3][0] = x;
    pOut->m[2][1] = 0.0f;
    pOut->m[3][1] = y;
    pOut->m[2][0] = 0.0f;
    pOut->m[3][2] = z;
    pOut->m[1][3] = 0.0f;
    pOut->m[1][2] = 0.0f;
    pOut->m[1][0] = 0.0f;
    pOut->m[0][3] = 0.0f;
    pOut->m[0][2] = 0.0f;
    pOut->m[0][1] = 0.0f;
    pOut->m[3][3] = 1.0f;
    pOut->m[2][2] = 1.0f;
    pOut->m[1][1] = 1.0f;
    pOut->m[0][0] = 1.0f;
    return pOut;
}

/* D3DXMatrixRotationYawPitchRoll */
extern "C" D3DXMATRIX *__stdcall D3DXMatrixRotationYawPitchRoll(
    D3DXMATRIX *pOut,
    FLOAT yaw,
    FLOAT pitch,
    FLOAT roll)
{
    D3DXQUATERNION quaternion;

    D3DXQuaternionRotationYawPitchRoll(&quaternion, yaw, pitch, roll);
    D3DXMatrixRotationQuaternion(pOut, &quaternion);
    return pOut;
}
