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
};

struct D3DXPLANE {
    FLOAT a, b, c, d;
};

#endif
