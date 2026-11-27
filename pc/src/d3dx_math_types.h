#ifndef D3DX_MATH_TYPES_H
#define D3DX_MATH_TYPES_H

typedef float FLOAT;

struct D3DXVECTOR2 {
    float x;
    float y;
};

struct D3DXVECTOR3 {
    float x;
    float y;
    float z;
};

struct D3DXVECTOR4 {
    float x;
    float y;
    float z;
    float w;
};

struct D3DXMATRIX {
    FLOAT m[4][4];
};

struct D3DXQUATERNION {
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT w;

    D3DXQUATERNION() {}
    D3DXQUATERNION(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
        : x(x), y(y), z(z), w(w) {}

    operator FLOAT *() { return &x; }
    operator const FLOAT *() const { return &x; }

    D3DXQUATERNION operator-() const;
    D3DXQUATERNION operator+(const D3DXQUATERNION &q) const;
    D3DXQUATERNION operator-(const D3DXQUATERNION &q) const;
    D3DXQUATERNION operator*(const D3DXQUATERNION &q) const;
    D3DXQUATERNION operator*(FLOAT scale) const;
};

struct D3DXPLANE {
    FLOAT a, b, c, d;
};

#endif
