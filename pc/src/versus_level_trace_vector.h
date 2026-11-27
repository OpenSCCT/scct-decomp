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
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Size() const;
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector &operator-=(const FVector &V) {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
    }
    FVector &operator*=(const FVector &V) {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
    }
    FLOAT GetAbsMax() const;
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;
};

#endif
