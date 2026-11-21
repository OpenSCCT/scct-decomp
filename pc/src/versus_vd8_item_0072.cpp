// Work item 0072: Versus RVA 0x140e80-0x141184 (4 functions).
//   0x140e80 FMatrix::TransposeAdjoint() const
//   0x140f70 FPlane::TransformByUsingAdjointT(const FMatrix &, const FMatrix &) const
//   0x141070 UModel::GetRenderBoundingBox(const AActor *)
//   0x1410d0 UnnamedModelContext constructor (neutral name; no vtable/string evidence)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector SafeNormal() const;
};

__declspec(dllimport) extern const FVector GZeroVector;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GBoxStartMin;  // 0x10ccacc4

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C) const;
};
extern FGlobalMath GMath;

struct FMatrix;

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane(FVector Base, const FVector &Normal) : FVector(Normal), W(Base | Normal) {}
    FPlane TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const;
};

struct FMatrix
{
    FLOAT M[4][4];
    static FMatrix Identity; // 0x10cc9560

    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    {
        M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
        M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
        M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
        M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
    }

    FPlane TransformFPlane(const FPlane &P) const; // 0x4fe60
    FVector TransformFVector(const FVector &V) const;
    FPlane TransformNormal(const FVector &V) const;
    FLOAT Determinant() const; // 0x4ff90
    FMatrix TransposeAdjoint() const; // 0x140e80
};

struct FBox
{
    FVector Min, Max;
    FBox() : Min(GBoxStartMin), Max(GZeroVector) {}
    FBox(const FVector &InMin, const FVector &InMax) : Min(InMin), Max(InMax) {}
    const FVector &GetExtrema(INT i) const { return (&Min)[i]; }
    FBox TransformBy(const FMatrix &M) const; // 0x50da0
    FBox &operator+=(const FVector &Other);   // 0x4f820
};

class AActor
{
public:
    BYTE Pad0[0x80];
    FVector Location;          // 0x80
    BYTE Pad8C[0xb0 - 0x8c];
    FVector DrawScale3D;       // 0xb0
    FVector PrePivot;          // 0xbc
    BYTE PadC8[0xe0 - 0xc8];
    FRotator Rotation;         // 0xe0
    BYTE PadEC[0x23c - 0xec];
    FLOAT DrawScale;           // 0x23c
    FMatrix LocalToWorld() const; // 0x9e5b0
};

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    DWORD ObjectFields[9]; // 0x04..0x27
};

class UPrimitive : public UObject
{
public:
    FBox BoundingBox;       // 0x28..0x3f
    FPlane BoundingSphere;  // 0x40..0x4f
    virtual FBox GetRenderBoundingBox(const AActor *Owner);
};

class UModel : public UPrimitive
{
public:
    virtual FBox GetRenderBoundingBox(const AActor *Owner);
};

// ---------------------------------------------------------------------------
// RVA 0x140e80: FMatrix::TransposeAdjoint
FMatrix FMatrix::TransposeAdjoint() const
{
    FMatrix TA;

    TA.M[0][0] = M[1][1] * M[2][2] - M[2][1] * M[1][2];
    TA.M[0][1] = M[2][0] * M[1][2] - M[1][0] * M[2][2];
    TA.M[0][2] = M[2][1] * M[1][0] - M[2][0] * M[1][1];
    TA.M[0][3] = 0.0f;

    TA.M[1][0] = M[2][1] * M[0][2] - M[0][1] * M[2][2];
    TA.M[1][1] = M[0][0] * M[2][2] - M[2][0] * M[0][2];
    TA.M[1][2] = M[2][0] * M[0][1] - M[2][1] * M[0][0];
    TA.M[1][3] = 0.0f;

    TA.M[2][0] = M[0][1] * M[1][2] - M[0][2] * M[1][1];
    TA.M[2][1] = M[1][0] * M[0][2] - M[0][0] * M[1][2];
    TA.M[2][2] = M[1][1] * M[0][0] - M[1][0] * M[0][1];
    TA.M[2][3] = 0.0f;

    TA.M[3][0] = 0.0f;
    TA.M[3][1] = 0.0f;
    TA.M[3][2] = 0.0f;
    TA.M[3][3] = 1.0f;

    return TA;
}

// ---------------------------------------------------------------------------
// RVA 0x140f70: FPlane::TransformByUsingAdjointT
FPlane FPlane::TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const
{
    FVector newNorm = TA.TransformNormal(*this).SafeNormal();

    if (M.Determinant() < 0.f)
        newNorm *= -1.0f;

    return FPlane(M.TransformFVector(*this * W), newNorm);
}

FVector FMatrix::TransformFVector(const FVector &V) const
{
    return TransformFPlane(FPlane(V, 1.f));
}

FPlane FMatrix::TransformNormal(const FVector &V) const
{
    return TransformFPlane(FPlane(V, 0.f));
}

// ---------------------------------------------------------------------------
// RVA 0x141070: UModel::GetRenderBoundingBox
FBox UModel::GetRenderBoundingBox(const AActor *Owner)
{
    return Owner ? BoundingBox.TransformBy(Owner->LocalToWorld()) : BoundingBox;
}

// ---------------------------------------------------------------------------
// RVA 0x1410d0: UnnamedModelContext constructor (neutral name)
struct UnnamedModelContext
{
    DWORD Field00;          // 0x00
    DWORD Field04;          // 0x04
    const AActor *Owner;    // 0x08
    FMatrix LocalToWorld;   // 0x0c
    FVector Vec4C;          // 0x4c..0x57
    DWORD Field58;          // 0x58
    DWORD Field5C[4];       // 0x5c..0x6b
    FBox Box;               // 0x6c..0x83
    DWORD Field84[2];       // 0x84..0x8b
    FMatrix TransposeAdjoint; // 0x8c..0xcb

    UnnamedModelContext(DWORD In00, DWORD In04, const AActor *InOwner, FVector InVec4C, DWORD In58);
};

UnnamedModelContext::UnnamedModelContext(DWORD In00, DWORD In04, const AActor *InOwner, FVector InVec4C, DWORD In58)
    : Field00(In00), Field04(In04), Owner(InOwner), Vec4C(InVec4C), Field58(In58)
{
    if (InOwner)
    {
        LocalToWorld = InOwner->LocalToWorld();
        TransposeAdjoint = LocalToWorld.TransposeAdjoint();
    }
    else
    {
        LocalToWorld = TransposeAdjoint = FMatrix::Identity;
    }
}

// ---------------------------------------------------------------------------
// Callees defined elsewhere in the LTCG program; bodies here only so the
// linker gives them their custom conventions. Not part of the unit.
#pragma auto_inline(off)
FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

FLOAT FMatrix::Determinant() const
{
    return  M[0][0] * (
                M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
                M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
                ) -
            M[1][0] * (
                M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
                ) +
            M[2][0] * (
                M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
                M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                ) -
            M[3][0] * (
                M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
                M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
                M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                );
}

FMatrix AActor::LocalToWorld() const
{
    FLOAT SR, CR, SP, CP, SY, CY;
    GMath.SinCos(Rotation.Yaw, &SY, &CY);
    GMath.SinCos(Rotation.Pitch, &SP, &CP);
    GMath.SinCos(Rotation.Roll, &SR, &CR);
    FLOAT LX = Location.X, LY = Location.Y, LZ = Location.Z;
    FLOAT PX = PrePivot.X, PY = PrePivot.Y, PZ = PrePivot.Z;
    FLOAT DX = DrawScale3D.X * DrawScale, DY = DrawScale3D.Y * DrawScale, DZ = DrawScale3D.Z * DrawScale;
    return FMatrix(
        FPlane(CP * CY * DX, CP * DX * SY, DX * SP, 0.f),
        FPlane(DY * (CY * SP * SR - CR * SY), DY * (CR * CY + SP * SR * SY), -CP * DY * SR, 0.f),
        FPlane(DZ * (-CR * CY * SP - SR * SY), DZ * (CY * SR - CR * SP * SY), CP * CR * DZ, 0.f),
        FPlane(LX - CP * CY * DX * PX + (CR * SY - CY * SP * SR) * DY * PY + (CR * CY * SP + SR * SY) * DZ * PZ,
               LY - (CR * CY + SP * SR * SY) * DY * PY + (CR * SP * SY - CY * SR) * DZ * PZ - CP * DX * PX * SY,
               LZ + CP * DY * PY * SR - CP * CR * DZ * PZ - DX * PX * SP,
               1.f));
}

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X); Min.Y = ::Min(Min.Y, Other.Y); Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X); Max.Y = ::Max(Max.Y, Other.Y); Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

FBox FBox::TransformBy(const FMatrix &M) const
{
    FBox NewBox(GBoxStartMin, GZeroVector);
    for (INT i = 0; i < 2; i++)
        for (INT j = 0; j < 2; j++)
            for (INT k = 0; k < 2; k++)
                NewBox += FVector(M.TransformFPlane(FPlane(FVector(GetExtrema(i).X, GetExtrema(j).Y, GetExtrema(k).Z), 1.f)));
    return NewBox;
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
void Escape(void *);

void Driver_140e80(const FMatrix *M, FMatrix *Out)
{
    *Out = M->TransposeAdjoint();
    Escape(Out);
}

void Driver_140f70(const FPlane *P, const FMatrix *M, const FMatrix *TA, FPlane *Out)
{
    *Out = P->TransformByUsingAdjointT(*M, *TA);
    Escape(Out);
}

void Driver_141070(void *Mem, const AActor *A, FBox *Out)
{
    UModel *M = new(Mem) UModel;
    *Out = M->GetRenderBoundingBox(A);
    FBox B = Out->TransformBy(A->LocalToWorld());
    Escape(&B);
}

void Driver_1410d0(DWORD A, DWORD B, const AActor *Owner, FVector V, DWORD F)
{
    Escape(&FMatrix::Identity);
    UnnamedModelContext Ctx(A, B, Owner, V, F);
    Escape(&Ctx);
}
