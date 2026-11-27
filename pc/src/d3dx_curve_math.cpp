/* d3dx_curve_math.cpp -- D3DX8 vector interpolation functions */
#include "d3dx_math_types.h"

D3DXVECTOR2 *__stdcall c_D3DXVec2Hermite(
    D3DXVECTOR2 *pOut,
    const D3DXVECTOR2 *pV1,
    const D3DXVECTOR2 *pT1,
    const D3DXVECTOR2 *pV2,
    const D3DXVECTOR2 *pT2,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float h1 = 2.0f * s3 - 3.0f * s2 + 1.0f;
    float h2 = s3 - 2.0f * s2 + s;
    float h3 = -2.0f * s3 + 3.0f * s2;
    float h4 = s3 - s2;

    pOut->x = h1 * pV1->x + h2 * pT1->x + h3 * pV2->x + h4 * pT2->x;
    pOut->y = h1 * pV1->y + h2 * pT1->y + h3 * pV2->y + h4 * pT2->y;
    return pOut;
}

D3DXVECTOR2 *__stdcall c_D3DXVec2CatmullRom(
    D3DXVECTOR2 *pOut,
    const D3DXVECTOR2 *pV1,
    const D3DXVECTOR2 *pV2,
    const D3DXVECTOR2 *pV3,
    const D3DXVECTOR2 *pV4,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float w1 = 2.0f * s2 - s3 - s;
    float w2 = 3.0f * s3 - 5.0f * s2 + 2.0f;
    float w3 = 4.0f * s2 - 3.0f * s3 + s;
    float w4 = s3 - s2;

    pOut->x = (w1 * pV1->x + w2 * pV2->x + w3 * pV3->x + w4 * pV4->x) * 0.5f;
    pOut->y = (w1 * pV1->y + w2 * pV2->y + w3 * pV3->y + w4 * pV4->y) * 0.5f;
    return pOut;
}

D3DXVECTOR2 *__stdcall c_D3DXVec2BaryCentric(
    D3DXVECTOR2 *pOut,
    const D3DXVECTOR2 *pV1,
    const D3DXVECTOR2 *pV2,
    const D3DXVECTOR2 *pV3,
    float f,
    float g)
{
    pOut->x = f * (pV2->x - pV1->x) + g * (pV3->x - pV1->x) + pV1->x;
    pOut->y = f * (pV2->y - pV1->y) + g * (pV3->y - pV1->y) + pV1->y;
    return pOut;
}

D3DXVECTOR3 *__stdcall c_D3DXVec3Hermite(
    D3DXVECTOR3 *pOut,
    const D3DXVECTOR3 *pV1,
    const D3DXVECTOR3 *pT1,
    const D3DXVECTOR3 *pV2,
    const D3DXVECTOR3 *pT2,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float h1 = 2.0f * s3 - 3.0f * s2 + 1.0f;
    float h2 = s3 - 2.0f * s2 + s;
    float h3 = -2.0f * s3 + 3.0f * s2;
    float h4 = s3 - s2;

    pOut->x = h1 * pV1->x + h2 * pT1->x + h3 * pV2->x + h4 * pT2->x;
    pOut->y = h1 * pV1->y + h2 * pT1->y + h3 * pV2->y + h4 * pT2->y;
    pOut->z = h1 * pV1->z + h2 * pT1->z + h3 * pV2->z + h4 * pT2->z;
    return pOut;
}

D3DXVECTOR3 *__stdcall c_D3DXVec3CatmullRom(
    D3DXVECTOR3 *pOut,
    const D3DXVECTOR3 *pV1,
    const D3DXVECTOR3 *pV2,
    const D3DXVECTOR3 *pV3,
    const D3DXVECTOR3 *pV4,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float w1 = 2.0f * s2 - s3 - s;
    float w2 = 3.0f * s3 - 5.0f * s2 + 2.0f;
    float w3 = 4.0f * s2 - 3.0f * s3 + s;
    float w4 = s3 - s2;

    pOut->x = (w1 * pV1->x + w2 * pV2->x + w3 * pV3->x + w4 * pV4->x) * 0.5f;
    pOut->y = (w1 * pV1->y + w2 * pV2->y + w3 * pV3->y + w4 * pV4->y) * 0.5f;
    pOut->z = (w1 * pV1->z + w2 * pV2->z + w3 * pV3->z + w4 * pV4->z) * 0.5f;
    return pOut;
}

D3DXVECTOR3 *__stdcall c_D3DXVec3BaryCentric(
    D3DXVECTOR3 *pOut,
    const D3DXVECTOR3 *pV1,
    const D3DXVECTOR3 *pV2,
    const D3DXVECTOR3 *pV3,
    float f,
    float g)
{
    pOut->x = f * (pV2->x - pV1->x) + g * (pV3->x - pV1->x) + pV1->x;
    pOut->y = f * (pV2->y - pV1->y) + g * (pV3->y - pV1->y) + pV1->y;
    pOut->z = f * (pV2->z - pV1->z) + g * (pV3->z - pV1->z) + pV1->z;
    return pOut;
}

D3DXVECTOR4 *__stdcall c_D3DXVec4Hermite(
    D3DXVECTOR4 *pOut,
    const D3DXVECTOR4 *pV1,
    const D3DXVECTOR4 *pT1,
    const D3DXVECTOR4 *pV2,
    const D3DXVECTOR4 *pT2,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float h1 = 2.0f * s3 - 3.0f * s2 + 1.0f;
    float h2 = s3 - 2.0f * s2 + s;
    float h3 = -2.0f * s3 + 3.0f * s2;
    float h4 = s3 - s2;

    pOut->x = h1 * pV1->x + h2 * pT1->x + h3 * pV2->x + h4 * pT2->x;
    pOut->y = h1 * pV1->y + h2 * pT1->y + h3 * pV2->y + h4 * pT2->y;
    pOut->z = h1 * pV1->z + h2 * pT1->z + h3 * pV2->z + h4 * pT2->z;
    pOut->w = h1 * pV1->w + h2 * pT1->w + h3 * pV2->w + h4 * pT2->w;
    return pOut;
}

D3DXVECTOR4 *__stdcall c_D3DXVec4CatmullRom(
    D3DXVECTOR4 *pOut,
    const D3DXVECTOR4 *pV1,
    const D3DXVECTOR4 *pV2,
    const D3DXVECTOR4 *pV3,
    const D3DXVECTOR4 *pV4,
    float s)
{
    float s2 = s * s;
    float s3 = s2 * s;
    float w1 = 2.0f * s2 - s3 - s;
    float w2 = 3.0f * s3 - 5.0f * s2 + 2.0f;
    float w3 = 4.0f * s2 - 3.0f * s3 + s;
    float w4 = s3 - s2;

    pOut->x = (w1 * pV1->x + w2 * pV2->x + w3 * pV3->x + w4 * pV4->x) * 0.5f;
    pOut->y = (w1 * pV1->y + w2 * pV2->y + w3 * pV3->y + w4 * pV4->y) * 0.5f;
    pOut->z = (w1 * pV1->z + w2 * pV2->z + w3 * pV3->z + w4 * pV4->z) * 0.5f;
    pOut->w = (w1 * pV1->w + w2 * pV2->w + w3 * pV3->w + w4 * pV4->w) * 0.5f;
    return pOut;
}

D3DXVECTOR4 *__stdcall c_D3DXVec4BaryCentric(
    D3DXVECTOR4 *pOut,
    const D3DXVECTOR4 *pV1,
    const D3DXVECTOR4 *pV2,
    const D3DXVECTOR4 *pV3,
    float f,
    float g)
{
    pOut->x = f * (pV2->x - pV1->x) + g * (pV3->x - pV1->x) + pV1->x;
    pOut->y = f * (pV2->y - pV1->y) + g * (pV3->y - pV1->y) + pV1->y;
    pOut->z = f * (pV2->z - pV1->z) + g * (pV3->z - pV1->z) + pV1->z;
    pOut->w = f * (pV2->w - pV1->w) + g * (pV3->w - pV1->w) + pV1->w;
    return pOut;
}

D3DXVECTOR4 *__stdcall c_D3DXVec4Cross(
    D3DXVECTOR4 *out, const D3DXVECTOR4 *a, const D3DXVECTOR4 *b, const D3DXVECTOR4 *c)
{
    D3DXVECTOR4 cross;
    cross.x = (c->w * b->z - c->z * b->w) * a->y
        - (c->w * b->y - c->y * b->w) * a->z
        + (c->z * b->y - c->y * b->z) * a->w;
    cross.y = (c->z * b->w - c->w * b->z) * a->x
        - (c->x * b->w - c->w * b->x) * a->z
        + (c->x * b->z - c->z * b->x) * a->w;
    cross.z = (c->w * b->y - c->y * b->w) * a->x
        - (c->w * b->x - c->x * b->w) * a->y
        + (c->y * b->x - c->x * b->y) * a->w;
    cross.w = (c->y * b->z - c->z * b->y) * a->x
        - (c->x * b->z - c->z * b->x) * a->y
        + (c->x * b->y - c->y * b->x) * a->z;
    *out = cross;
    return out;
}
