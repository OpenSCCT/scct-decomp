#ifndef D3DX_QUATERNION_OPERATORS_H
#define D3DX_QUATERNION_OPERATORS_H

#include "d3dx_math_types.h"

extern "C" D3DXQUATERNION *__stdcall D3DXQuaternionMultiply(
    D3DXQUATERNION *out, const D3DXQUATERNION *first, const D3DXQUATERNION *second);

__forceinline D3DXQUATERNION D3DXQUATERNION::operator+(const D3DXQUATERNION &b) const
{
    return D3DXQUATERNION(x + b.x, y + b.y, z + b.z, w + b.w);
}

__forceinline D3DXQUATERNION D3DXQUATERNION::operator-(const D3DXQUATERNION &b) const
{
    return D3DXQUATERNION(x - b.x, y - b.y, z - b.z, w - b.w);
}

__forceinline D3DXQUATERNION D3DXQUATERNION::operator-() const
{
    return D3DXQUATERNION(-x, -y, -z, -w);
}

__forceinline D3DXQUATERNION D3DXQUATERNION::operator*(float s) const
{
    return D3DXQUATERNION(x * s, y * s, z * s, w * s);
}

__forceinline D3DXQUATERNION D3DXQUATERNION::operator*(const D3DXQUATERNION &b) const
{
    D3DXQUATERNION product;
    D3DXQuaternionMultiply(&product, this, &b);
    return product;
}

#endif
