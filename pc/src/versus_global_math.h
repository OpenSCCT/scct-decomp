// versus_global_math.h -- coordinate systems and scale constants used by Versus Core
#ifndef VERSUS_GLOBAL_MATH_H
#define VERSUS_GLOBAL_MATH_H

#include "versus_level_trace_vector.h"

enum ESheerAxis {
    SHEER_None, SHEER_XY, SHEER_XZ, SHEER_YX, SHEER_YZ, SHEER_ZX, SHEER_ZY
};

struct FScale {
    FVector Scale;
    FLOAT SheerRate;
    BYTE SheerAxis;

    FScale(const FVector &InScale, FLOAT InSheerRate, ESheerAxis InSheerAxis)
        : Scale(InScale), SheerRate(InSheerRate), SheerAxis(InSheerAxis) {}
};

struct FRotator;

struct FCoords {
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;

    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}

    FCoords &operator*=(const FCoords &TransformCoords);
    FCoords &operator*=(const FVector &Point) {
        Origin -= Point;
        return *this;
    }
    FCoords operator*(const FVector &Point) const;
    FCoords &operator*=(const FScale &Scale);
    FCoords operator*(const FScale &Scale) const;
    FCoords operator/(const FRotator &Rotation) const;
};

struct FGlobalMath {
    FCoords UnitCoords;
    FScale UnitScale;
    FCoords ViewCoords;

    FGlobalMath();
};

extern FGlobalMath GMath;

#endif
