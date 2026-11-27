#include "versus_pawn_action_events.h"

FVector FVector::RotateAngleAxis(const INT Angle, const FVector &Axis) const
{
    FLOAT S, C;
    GMath.SinCos(Angle, &S, &C);

    const FLOAT XS = Axis.X * S;
    const FLOAT YS = Axis.Y * S;
    const FLOAT ZS = Axis.Z * S;

    const FLOAT OMC = 1.f - C;

    const FLOAT XY = (Axis.Y * Axis.X) * OMC;
    const FLOAT YZ = (Axis.Z * Axis.Y) * OMC;
    const FLOAT ZX = (Axis.Z * Axis.X) * OMC;

    return FVector(
        ((Axis.X * Axis.X) * OMC + C) * X + (XY - ZS) * Y + (ZX + YS) * Z,
        (XY + ZS) * X + ((Axis.Y * Axis.Y) * OMC + C) * Y + (YZ - XS) * Z,
        (ZX - YS) * X + (YZ + XS) * Y + ((Axis.Z * Axis.Z) * OMC + C) * Z);
}

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

inline void FFrame::Step(UObject *Context, void *const Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

void UObject::execTurnAroundAxis(FFrame &Stack, void *const Result)
{
    FVector V;
    Stack.Step(Stack.Object, &V);
    FVector Axis;
    Stack.Step(Stack.Object, &Axis);
    FLOAT Angle = 0.f;
    Stack.Step(Stack.Object, &Angle);
    Stack.Code++;
    *(FVector *)Result = V.RotateAngleAxis((INT)Angle, Axis);
}
