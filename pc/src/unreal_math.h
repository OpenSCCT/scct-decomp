// unreal_math.h -- vectors, rotators and the math helpers the script natives use
#ifndef UNREAL_MATH_H
#define UNREAL_MATH_H

#include "unreal_types.h"

#define PI (3.1415926535897932)
#define MAXWORD 0xffff

// campaign_core_math.cpp, campaign_core_math_2.cpp
DOUBLE appSqrt(DOUBLE Value);
DOUBLE appAtan2(DOUBLE Y, DOUBLE X);
DOUBLE appExp(DOUBLE Value);
DOUBLE appLoge(DOUBLE Value);
DOUBLE appSin(DOUBLE Value);
DOUBLE appCos(DOUBLE Value);
DOUBLE appAsin(DOUBLE Value);
DOUBLE appTan(DOUBLE Value);
DOUBLE appAtan(DOUBLE Value);

struct FRotator;
struct FCoords;

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    // cross product
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    // dot product
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator/(FLOAT Scale) const
    {
        FLOAT RScale = 1.0f / Scale;
        return FVector(X * RScale, Y * RScale, Z * RScale);
    }
    FVector &operator*=(FLOAT Scale)
    {
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        return *this;
    }
    FVector &operator/=(FLOAT V)
    {
        FLOAT RV = 1.0f / V;
        X *= RV;
        Y *= RV;
        Z *= RV;
        return *this;
    }
    FLOAT Size() const { return (FLOAT)appSqrt(X * X + Y * Y + Z * Z); }
    UBOOL IsZero() const { return X == 0.0f && Y == 0.0f && Z == 0.0f; }
#ifndef SCCT_VERSUS
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
#else
    FVector RotateAngleAxis(const INT Angle, const FVector &Axis) const;
    FVector TransformVectorBy(const FCoords &Coords) const;
#endif
    FVector SafeNormal() const;
    FRotator Rotation();
};

inline FVector operator*(FLOAT Scale, const FVector &V)
{
    return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale);
}

extern FVector GDefaultVector;      // the zero vector natives use as a default argument

struct FColor {
    BYTE B, G, R, A;
};

// Angles in units of 1/65536 of a turn.
struct FRotator {
    INT Pitch, Yaw, Roll;

    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FVector Vector();
    FRotator operator*(FLOAT Scale) const
    {
        return FRotator((INT)(Pitch * Scale), (INT)(Yaw * Scale), (INT)(Roll * Scale));
    }
    FRotator operator/(FLOAT Scale) const
    {
        FLOAT RScale = 1.0f / Scale;
        return FRotator((INT)(Pitch * RScale), (INT)(Yaw * RScale), (INT)(Roll * RScale));
    }
    FRotator &operator/=(FLOAT Scale)
    {
        FLOAT RScale = 1.0f / Scale;
        Pitch = (INT)(Pitch * RScale);
        Yaw = (INT)(Yaw * RScale);
        Roll = (INT)(Roll * RScale);
        return *this;
    }
    // Maps an angle to -32768..32767.
    INT NormalizeAxis(INT Angle) const
    {
        Angle &= 0xFFFF;
        if (Angle > 32767)
            Angle -= 0x10000;
        return Angle;
    }
#ifndef SCCT_VERSUS
    UBOOL IsZero() const
    {
        return ((Pitch & 65535) == 0) && ((Yaw & 65535) == 0) && ((Roll & 65535) == 0);
    }
#endif
    __forceinline FRotator Normalize() const
    {
        return FRotator(NormalizeAxis(Pitch), NormalizeAxis(Yaw), NormalizeAxis(Roll));
    }
};

inline FRotator operator*(FLOAT Scale, const FRotator &R)
{
    return FRotator((INT)(R.Pitch * Scale), (INT)(R.Yaw * Scale), (INT)(R.Roll * Scale));
}

struct FCoords {
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;

    FCoords &operator/=(const FRotator &R);
#ifdef SCCT_VERSUS
    FCoords operator*(const FRotator &R) const; // Versus helper at RVA 0x40f40
    FCoords operator/(const FRotator &R) const; // Versus helper at RVA 0x411a0
#else
    FCoords operator/(const FRotator &R) const { return FCoords(*this) /= R; }
#endif
};

#ifdef SCCT_VERSUS
// UnMath.h helper used by Versus vector transformations.
void ASMTransformVector(const FCoords &Coords, const FVector &InVector, FVector &OutVector);

#endif

struct FGlobalMath {
    FCoords UnitCoords;
#ifdef SCCT_VERSUS
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
#endif
};

extern FGlobalMath GMath;

// FRotator::Vector: the unit vector the rotation points along
inline FVector FRotator::Vector()
{
    return (GMath.UnitCoords / *this).XAxis;
}

struct FQuat {
    FLOAT X, Y, Z, W;
};

FQuat FRotatorToQuat(const FRotator &Rot);
FRotator FQuatToRotator(const FQuat &Quat);
void AlignFQuatWith(FQuat &Quat, const FQuat &Other);
FQuat SlerpQuat(const FQuat &Quat1, const FQuat &Quat2, FLOAT Slerp);

// Clamp: X limited to the range Min..Max
template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

FLOAT PointToLineDistance(const FVector &Point, FVector &LineOrigin, FVector &LineDir);
FRotator InterpolateRotator(FLOAT Alpha, const FRotator &A, const FRotator &B);

// campaign_engine_helpers.cpp
FLOAT DampFloat(FLOAT Current, FLOAT Target, FLOAT Rate, FLOAT DeltaTime);
INT DampInt(INT Current, INT Target, FLOAT Rate, FLOAT DeltaTime);
FVector DampVec(const FVector &Current, const FVector &Target, FLOAT Rate, FLOAT DeltaTime);

// campaign_engine_helpers_2.cpp
INT InterpolateRotatorValue(FLOAT Rate, INT Current, INT Desired);

#endif // UNREAL_MATH_H
