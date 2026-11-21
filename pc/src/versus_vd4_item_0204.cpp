// Work item 0204: Versus RVA 0x500c0-0x5057e.
// Core UnMath.cpp: FVector::Rotation, FVector::FindBestAxisVectors,
// FCoords::Inverse, FCoords::ApplyPivot and one more FCoords helper.
// All five came out of the LTCG link with register calling conventions.

typedef int INT;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, atan2, fabs)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appAtan2(FLOAT Y, FLOAT X) { return (FLOAT)atan2(Y, X); }
inline INT appTrunc(FLOAT F) { return (INT)F; } // _ftol at 0x10b83aa0
inline FLOAT Abs(FLOAT A) { return (FLOAT)fabs(A); }

#define PI 3.1415926535897932f
#define MAXWORD 0xffff

struct FCoords;

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FVector SafeNormal() const; // RVA 0x50d30
    inline FVector TransformVectorBy(const FCoords &Coords) const;
    FRotator Rotation();
    void FindBestAxisVectors(FVector &Axis1, FVector &Axis2);
};

inline FVector operator*(FLOAT Scale, const FVector &V)
{
    return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale);
}

inline FLOAT FTriple(const FVector &X, const FVector &Y, const FVector &Z)
{
    return (X.X * (Y.Y * Z.Z - Y.Z * Z.Y))
         + (X.Y * (Y.Z * Z.X - Y.X * Z.Z))
         + (X.Z * (Y.X * Z.Y - Y.Y * Z.X));
}

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords Inverse() const;
    FCoords ApplyPivot(const FCoords &CoordsB) const;
    FCoords Unnamed_50480(const FCoords &Other) const;
};

// RVA 0x40ab0: UnMath.h's ASMTransformVector, a whole __asm body (see item 0154).
void ASMTransformVector(const FCoords &Coords, const FVector &InVector, FVector &OutVector);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Temp;
    ASMTransformVector(Coords, *this, Temp);
    return Temp;
}

// Unit axis vectors reached through references (0x10ccacc4 and 0x10ccacbc).
extern const FVector &UnitX_Ref;
extern const FVector &UnitZ_Ref;

// RVA 0x50d30, defined here only so the link gives it the register
// convention retail callers use; it is matched in its own item.
#pragma auto_inline(off)
FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / appSqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
#pragma auto_inline(on)

// RVA 0x500c0
FRotator FVector::Rotation()
{
    FRotator R;
    // Find yaw.
    R.Yaw = appTrunc(appAtan2(Y, X) * (FLOAT)MAXWORD / (2.f * PI));
    // Find pitch.
    R.Pitch = appTrunc(appAtan2(Z, appSqrt(X * X + Y * Y)) * (FLOAT)MAXWORD / (2.f * PI));
    // Find roll.
    R.Roll = 0;
    return R;
}

// RVA 0x50110 (near: 25 bytes differ, the order of the dot-product terms
// and of one cross-product multiply)
void FVector::FindBestAxisVectors(FVector &Axis1, FVector &Axis2)
{
    FLOAT NX = Abs(X);
    FLOAT NY = Abs(Y);
    FLOAT NZ = Abs(Z);

    // Find best basis vectors.
    if (NZ > NX && NZ > NY) Axis1 = UnitX_Ref;
    else                    Axis1 = UnitZ_Ref;

    Axis1 = (Axis1 - *this * (Axis1 | *this)).SafeNormal();
    Axis2 = Axis1 ^ *this;
}

// RVA 0x50220 (near: 22 bytes differ, the operand order of six cofactor
// products; the compiler orders commuted operands itself, so the source
// order of the products has no effect)
FCoords FCoords::Inverse() const
{
    FLOAT Div = FTriple(XAxis, YAxis, ZAxis);
    if (!Div) Div = 1.f;

    FLOAT RDet = 1.f / Div;
    return FCoords
    (   -Origin.TransformVectorBy(*this)
    ,   RDet * FVector
        (   (YAxis.Y * ZAxis.Z - YAxis.Z * ZAxis.Y)
        ,   (ZAxis.Y * XAxis.Z - ZAxis.Z * XAxis.Y)
        ,   (XAxis.Y * YAxis.Z - XAxis.Z * YAxis.Y) )
    ,   RDet * FVector
        (   (YAxis.Z * ZAxis.X - ZAxis.Z * YAxis.X)
        ,   (ZAxis.Z * XAxis.X - XAxis.Z * ZAxis.X)
        ,   (XAxis.Z * YAxis.X - XAxis.X * YAxis.Z) )
    ,   RDet * FVector
        (   (YAxis.X * ZAxis.Y - YAxis.Y * ZAxis.X)
        ,   (ZAxis.X * XAxis.Y - ZAxis.Y * XAxis.X)
        ,   (XAxis.X * YAxis.Y - XAxis.Y * YAxis.X) )
    );
}

// RVA 0x503c0
FCoords FCoords::ApplyPivot(const FCoords &CoordsB) const
{
    // Fast solution assuming orthogonal coordinate system.
    FCoords Temp;
    Temp.Origin = CoordsB.Origin + Origin.TransformVectorBy(CoordsB);
    Temp.XAxis = CoordsB.XAxis.TransformVectorBy(*this);
    Temp.YAxis = CoordsB.YAxis.TransformVectorBy(*this);
    Temp.ZAxis = CoordsB.ZAxis.TransformVectorBy(*this);
    return Temp;
}

// RVA 0x50480: name not recovered. Expresses this coordinate system
// relative to Other, using the inverses of both.
FCoords FCoords::Unnamed_50480(const FCoords &Other) const
{
    FCoords InvOther = Other.Inverse();
    FCoords Temp;
    Temp.Origin = (Origin - Other.Origin).TransformVectorBy(InvOther);
    FCoords InvThis = Inverse();
    Temp.XAxis = InvThis.XAxis.TransformVectorBy(InvOther);
    Temp.YAxis = InvThis.YAxis.TransformVectorBy(InvOther);
    Temp.ZAxis = InvThis.ZAxis.TransformVectorBy(InvOther);
    return Temp;
}

// Scaffolding for the link, not part of the unit.
#pragma inline_depth(0)
void Escape(void *);
void Driver_500c0(FVector *V, FRotator *R) { *R = V->Rotation(); }
void Driver_50110(FVector *V, FVector *A, FVector *B) { Escape((void *)&UnitX_Ref); Escape((void *)&UnitZ_Ref); V->FindBestAxisVectors(*A, *B); }
void Driver_50220(FCoords *C, FCoords *R) { *R = C->Inverse(); }
void Driver_503c0(FCoords *A, FCoords *B, FCoords *R) { *R = A->ApplyPivot(*B); }
void Driver_50480(FCoords *A, FCoords *B, FCoords *R) { *R = A->Unnamed_50480(*B); }
