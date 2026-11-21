// Work item 0205: Versus RVA 0x50580-0x50ac0.
// Core math (UnMath.cpp): FCoords::Inverse, FCoords::OrthoRotation,
// FCoords::Matrix and an axis-angle rotation of FCoords. These were compiled
// with /GL and linked with /LTCG, so the retail calls use register conventions.

typedef int INT;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, atan2, cos, fabs)

#define PI (3.1415926535897932f)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appAtan2(FLOAT Y, FLOAT X) { return (FLOAT)atan2(Y, X); }
inline FLOAT appCos(FLOAT F) { return (FLOAT)cos(F); }
inline FLOAT Abs(FLOAT F) { return (FLOAT)fabs(F); }
inline FLOAT Square(FLOAT F) { return F * F; }

struct FCoords;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector TransformVectorBy(const FCoords &Coords) const;
};

inline FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }

inline FLOAT FTriple(const FVector &X, const FVector &Y, const FVector &Z)
{
    return (X.X * (Y.Y * Z.Z - Y.Z * Z.Y)) + (X.Y * (Y.Z * Z.X - Y.X * Z.Z)) + (X.Z * (Y.X * Z.Y - Y.Y * Z.X));
}

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(FPlane InX, FPlane InY, FPlane InZ, FPlane InW)
    {
        M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
        M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
        M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
        M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
    }
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords &operator*=(const FCoords &TransformCoords);
    FCoords operator/(const FRotator &Rot) const;
    FCoords Inverse() const;
    FRotator OrthoRotation() const;
    FMatrix Matrix() const;
    FCoords &RotateAxis_50920(FLOAT Angle, const FVector &Axis);
};

// Global math table (GMath at 0x10ccac00); UnitCoords is its first member.
struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

// Constant zero vector reached through a reference (0x10ccacc0).
extern const FVector &GMath_Zero;

// RVA 0x40ab0 (item 0154).
void TransformVector_40ab0(const FCoords &Coords, const FVector &V, FVector &Result);

// RVA 0x40b60 (item 0154); retail inlines it under LTCG.
FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Result;
    TransformVector_40ab0(Coords, *this, Result);
    return Result;
}

// RVA 0x50580 (LTCG: this in EAX, result pointer in ESI)
__declspec(noinline) FCoords FCoords::Inverse() const
{
    FLOAT RDet = 1.f / FTriple(XAxis, YAxis, ZAxis);
    FCoords Temp;
    Temp.XAxis = RDet * FVector(
        (YAxis.Y * ZAxis.Z - YAxis.Z * ZAxis.Y),
        (ZAxis.Y * XAxis.Z - ZAxis.Z * XAxis.Y),
        (XAxis.Y * YAxis.Z - XAxis.Z * YAxis.Y));
    Temp.YAxis = RDet * FVector(
        (YAxis.Z * ZAxis.X - ZAxis.Z * YAxis.X),
        (ZAxis.Z * XAxis.X - XAxis.Z * ZAxis.X),
        (XAxis.Z * YAxis.X - XAxis.X * YAxis.Z));
    Temp.ZAxis = RDet * FVector(
        (YAxis.X * ZAxis.Y - YAxis.Y * ZAxis.X),
        (ZAxis.X * XAxis.Y - ZAxis.Y * XAxis.X),
        (XAxis.X * YAxis.Y - XAxis.Y * YAxis.X));
    return FCoords((-Origin).TransformVectorBy(Temp), Temp.XAxis, Temp.YAxis, Temp.ZAxis);
}

// RVA 0x50770 (LTCG: this in ESI, result pointer in EDI)
__declspec(noinline) FRotator FCoords::OrthoRotation() const
{
    INT Pitch = (INT)(appAtan2(XAxis.Z, appSqrt(Square(XAxis.X) + Square(XAxis.Y))) * (32768.f / PI));
    FRotator R;
    R.Pitch = Pitch;
    INT Yaw = (INT)(appAtan2(XAxis.Y, XAxis.X) * (32768.f / PI));
    R.Yaw = Yaw;
    R.Roll = 0;
    const FCoords S = GMath.UnitCoords / R;
    return FRotator(Pitch, Yaw, (INT)(appAtan2(ZAxis | S.YAxis, YAxis | S.YAxis) * (32768.f / PI)));
}

// RVA 0x50830 (LTCG: this in ECX, result pointer in EAX)
__declspec(noinline) FMatrix FCoords::Matrix() const
{
    FMatrix M;
    M.M[0][0] = XAxis.X; M.M[0][1] = YAxis.X; M.M[0][2] = ZAxis.X; M.M[0][3] = 0.f;
    M.M[1][0] = XAxis.Y; M.M[1][1] = YAxis.Y; M.M[1][2] = ZAxis.Y; M.M[1][3] = 0.f;
    M.M[2][0] = XAxis.Z; M.M[2][1] = YAxis.Z; M.M[2][2] = ZAxis.Z; M.M[2][3] = 0.f;
    M.M[3][0] = -Origin | XAxis; M.M[3][1] = -Origin | YAxis; M.M[3][2] = -Origin | ZAxis; M.M[3][3] = 1.f;
    return M;
}

inline FLOAT Sgn(FLOAT A) { return A < 0.f ? -1.f : (A > 0.f ? 1.f : 0.f); }

// RVA 0x50920 (LTCG: this in EDI, Axis in ESI, Angle on the stack).
// Name is neutral: rotates the coordinate system by Angle radians about Axis.
__declspec(noinline) FCoords &FCoords::RotateAxis_50920(FLOAT Angle, const FVector &Axis)
{
    FLOAT A = Angle - (INT)(Angle * (1.f / (2.f * PI))) * (2.f * PI);
    FLOAT C = appCos(Angle);
    FLOAT S = (Abs(A) < PI ? Sgn(A) : -Sgn(A)) * appSqrt(1.f - C * C);
    FLOAT OMC = 1.f - C;
    FCoords R;
    R.Origin = GMath_Zero;
    FLOAT XX = Square(Axis.X);
    R.XAxis.X = (1.f - XX) * C + XX;
    R.XAxis.Y = Axis.Y * Axis.X * OMC + S * Axis.Z;
    R.XAxis.Z = Axis.Z * Axis.X * OMC - S * Axis.Y;
    R.YAxis.X = Axis.Y * Axis.X * OMC - S * Axis.Z;
    FLOAT YY = Square(Axis.Y);
    R.YAxis.Y = (1.f - YY) * C + YY;
    R.YAxis.Z = Axis.Z * Axis.Y * OMC + S * Axis.X;
    R.ZAxis.X = Axis.Z * Axis.X * OMC + S * Axis.Y;
    R.ZAxis.Y = Axis.Z * Axis.Y * OMC - S * Axis.X;
    FLOAT ZZ = Square(Axis.Z);
    R.ZAxis.Z = (1.f - ZZ) * C + ZZ;
    *this *= R;
    return *this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_50580(FCoords *Out, const FCoords *C) { *Out = C->Inverse(); }
void Driver_50770(FRotator *Out, const FCoords *C) { Escape(&GMath); *Out = C->OrthoRotation(); }
void Driver_50830(FMatrix *Out, const FCoords *C) { *Out = C->Matrix(); }
void Driver_50920(FCoords *C, FLOAT Angle, const FVector *Axis) { Escape((void *)&GMath_Zero); C->RotateAxis_50920(Angle, *Axis); }
