// RVA 0x51dc0: plane vs. eight box corners. Returns 1 when the corners lie on
// both sides of the plane, 0 when they are all on one side.
// Names are neutral guesses (FPlane/FVector layout from Unreal Engine 2).
// Compiled with VC7.0 /GL and linked /LTCG (this in ECX, corners in EDX).
typedef float FLOAT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

struct FVector
{
    FLOAT X, Y, Z;
};

struct FPlane : public FVector
{
    FLOAT W;
    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
    UBOOL StraddlesBox_51dc0(const FVector *Corners) const;
};

UBOOL FPlane::StraddlesBox_51dc0(const FVector *Corners) const
{
    if (PlaneDot(Corners[0]) < 0.f)
    {
        if (PlaneDot(Corners[1]) > 0.f) return 1;
        if (PlaneDot(Corners[2]) > 0.f) return 1;
        if (PlaneDot(Corners[3]) > 0.f) return 1;
        if (PlaneDot(Corners[4]) > 0.f) return 1;
        if (PlaneDot(Corners[5]) > 0.f) return 1;
        if (PlaneDot(Corners[6]) > 0.f) return 1;
        if (PlaneDot(Corners[7]) > 0.f) return 1;
    }
    else
    {
        if (PlaneDot(Corners[1]) < 0.f) return 1;
        if (PlaneDot(Corners[2]) < 0.f) return 1;
        if (PlaneDot(Corners[3]) < 0.f) return 1;
        if (PlaneDot(Corners[4]) < 0.f) return 1;
        if (PlaneDot(Corners[5]) < 0.f) return 1;
        if (PlaneDot(Corners[6]) < 0.f) return 1;
        if (PlaneDot(Corners[7]) < 0.f) return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
void Driver_51dc0(const FPlane *Plane, const FVector *Corners, UBOOL *Out)
{
    *Out = Plane->StraddlesBox_51dc0(Corners);
}
