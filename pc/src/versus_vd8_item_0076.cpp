// w4_item_0076.cpp -- Versus work item 0076 (RVA 0x142480)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef DWORD UBOOL;

struct FVector {
    FLOAT X, Y, Z;
};

struct FPlane : public FVector {
    FLOAT W;

    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

inline FLOAT FBoxPushOut(const FVector &Normal, const FVector &Size)
{
    FLOAT X = Normal.X * Size.X;
    FLOAT Y = Normal.Y * Size.Y;
    FLOAT Z = Normal.Z * Size.Z;
    *(DWORD *)&X &= 0x7FFFFFFF;
    *(DWORD *)&Y &= 0x7FFFFFFF;
    *(DWORD *)&Z &= 0x7FFFFFFF;
    return X + Y + Z;
}

// Neutral name for the collision clip state at RVA 0x142480 (no symbol in retail).
struct FCollisionClip_142480 {
    BYTE unk_0[0x4c];
    FVector Extent;         // 0x4c
    BYTE unk_58[0x8];
    FVector HitNormal;      // 0x60
    BYTE unk_6c[0x18];
    FLOAT T0;               // 0x84
    FLOAT T1;               // 0x88
    BYTE unk_8c[0x544];
    FVector End;            // 0x5d0
    FVector Start;          // 0x5dc
    BYTE unk_5e8[0x8];
    INT HitItem;            // 0x5f0

    UBOOL Clip(const FPlane &Plane, INT Item);
};

// FCollisionClip_142480::Clip (RVA 0x142480)
UBOOL FCollisionClip_142480::Clip(const FPlane &Plane, INT Item)
{
    FLOAT PushOut = FBoxPushOut(Plane, Extent);
    FLOAT StartDist = Plane.PlaneDot(Start);
    FLOAT EndDist = Plane.PlaneDot(End);
    FLOAT Diff = StartDist - EndDist;

    INT Side = 0;
    if (Diff < -0.001f) {
        Side = -1;
    } else if (Diff > 0.001f) {
        Side = 1;
    } else {
        if (StartDist > PushOut && EndDist > PushOut)
            return 0;
    }

    if (Side != 0) {
        FLOAT Num = StartDist - PushOut;
        if (StartDist > EndDist && Num >= -PushOut && Num < 0.0f) {
            Num = 0.0f;
        }

        FLOAT Time = Num / Diff;
        if (Side == -1) {
            if (Time < T1) {
                T1 = Time;
            }
        } else {
            if (Time > T0) {
                T0 = Time;
                HitNormal = Plane;
                HitItem = Item;
            }
        }
    }

    if (T0 < T1)
        return 1;
    return 0;
}

// Scaffolding for the LTCG link, not part of the unit.
UBOOL Driver_142480(FCollisionClip_142480 *Check, const FPlane *Planes, INT Count, INT Item)
{
    for (INT i = 0; i < Count; i++) {
        if (!Check->Clip(Planes[i], Item))
            return 0;
    }
    if (!Check->Clip(Planes[0], -1))
        return 0;
    return 1;
}
