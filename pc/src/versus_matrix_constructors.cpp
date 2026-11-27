// versus_matrix_constructors.cpp -- homogeneous scale and translation matrices
#include "versus_build.h"
#include "versus_canvas_matrix.h"

// FScaleMatrix::FScaleMatrix
FScaleMatrix::FScaleMatrix(const FVector& Scale)
    : FMatrix(FPlane(Scale.X, 0, 0, 0),
              FPlane(0, Scale.Y, 0, 0),
              FPlane(0, 0, Scale.Z, 0),
              FPlane(0, 0, 0, 1))
{
}

// FTranslationMatrix::FTranslationMatrix
FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
    : FMatrix(FPlane(1, 0, 0, 0),
              FPlane(0, 1, 0, 0),
              FPlane(0, 0, 1, 0),
              FPlane(Delta.X, Delta.Y, Delta.Z, 1))
{
}
