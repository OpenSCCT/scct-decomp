#ifndef VERSUS_LEVEL_TRACE_VECTOR_H
#define VERSUS_LEVEL_TRACE_VECTOR_H

#include "versus_build.h"
#include "unreal_types.h"

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;
};

#endif
