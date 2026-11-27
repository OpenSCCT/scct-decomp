#ifndef VERSUS_PLANE_H
#define VERSUS_PLANE_H

struct FPlane : public FVector
{
    FLOAT W;

    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW);
    FPlane(const FVector &A, const FVector &B, const FVector &C);
    FPlane(const FVector &Base, const FVector &Normal)
    {
        FLOAT Distance = Base | Normal;
        X = Normal.X;
        Y = Normal.Y;
        Z = Normal.Z;
        W = Distance;
    }
    UBOOL StraddlesBox_51dc0(const FVector *Corners) const;
    FLOAT PlaneDot(const FVector &Point) const
    {
        return X * Point.X + Y * Point.Y + Z * Point.Z - W;
    }
    FPlane operator*(FLOAT Scale) const
    {
        return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
    }
};

#endif
