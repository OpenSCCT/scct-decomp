#ifndef VERSUS_CANVAS_MATRIX_H
#define VERSUS_CANVAS_MATRIX_H

#include "unreal_math.h"

struct FPlane : public FVector
{
    FLOAT W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW);
};
struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);
    FMatrix operator*(const FMatrix& Other) const;             // retail 0x1097b110
    FPlane TransformFPlane(const FPlane& Plane) const;
    FVector TransformFVector(const FVector& Point) const
    {
        return TransformFPlane(FPlane(Point.X, Point.Y, Point.Z, 1.f));
    }
    FPlane TransformNormal(const FVector& Normal) const
    {
        return TransformFPlane(FPlane(Normal.X, Normal.Y, Normal.Z, 0.f));
    }
    FLOAT Determinant() const;
    FMatrix Inverse() const;                                   // retail 0x10953af0
};

// FMatrix::FMatrix
inline FMatrix::FMatrix(const FPlane& InX, const FPlane& InY,
                        const FPlane& InZ, const FPlane& InW)
{
    M[0][0] = InX.X;
    M[0][1] = InX.Y;
    M[0][2] = InX.Z;
    M[0][3] = InX.W;
    M[1][0] = InY.X;
    M[1][1] = InY.Y;
    M[1][2] = InY.Z;
    M[1][3] = InY.W;
    M[2][0] = InZ.X;
    M[2][1] = InZ.Y;
    M[2][2] = InZ.Z;
    M[2][3] = InZ.W;
    M[3][0] = InW.X;
    M[3][1] = InW.Y;
    M[3][2] = InW.Z;
    M[3][3] = InW.W;
}

extern FMatrix GIdentityMatrix;

// Retail 0x10981910 and 0x109819b0 (out of line in this build).
struct FScaleMatrix : public FMatrix
{
    FScaleMatrix(const FVector& Scale);
};
struct FTranslationMatrix : public FMatrix
{
    FTranslationMatrix(const FVector& Delta);
};


#endif
