// Work item 0085: Versus RVA 0x149ad0-0x14a0b0 (UStaticMesh collision + helpers).
// Functions:
//   0x149ad0 UStaticMesh::GetCollisionBoundingBox (vtable slot 26)
//   0x149b60 UStaticMesh::LineCheck               (vtable slot 23)
//   0x149db0 UStaticMesh::PointCheck              (vtable slot 22)
//   0x149e50 FindMinMax                           (LTCG helper)
//   0x149ee0 FLineBoxIntersection                 (LTCG helper)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Clamp(const T X, const T MinVal, const T MaxVal)
{
    return X < MinVal ? MinVal : X < MaxVal ? X : MaxVal;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT &operator[](INT i) { return (&X)[i]; }
    const FLOAT &operator[](INT i) const { return (&X)[i]; }
    UBOOL Normalize();
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    {
        M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
        M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
        M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
        M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
    }
    FPlane TransformFPlane(const FPlane &P) const;
    FPlane TransformFVector(const FVector &V) const { return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.f)); }
};

struct FBox
{
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax) : Min(InMin), Max(InMax) {}
    const FVector &GetExtrema(INT i) const { return (&Min)[i]; }
    FBox TransformBy(const FMatrix &M) const;
    FBox &operator+=(const FVector &V);
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C);
};
extern FGlobalMath GMath;

__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4
extern DWORD GStaticMeshCollisionChecks;                 // 0x10c92294

class UPrimitive;

class AActor
{
public:
    BYTE Pad00[0x80];
    FVector Location;          // 0x80
    BYTE Pad8C[0xb0 - 0x8c];
    FVector DrawScale3D;       // 0xb0
    FVector PrePivot;          // 0xbc
    BYTE PadC8[0xe0 - 0xc8];
    FRotator Rotation;         // 0xe0
    BYTE PadEC[0x23c - 0xec];
    FLOAT DrawScale;           // 0x23c
    BYTE Pad240[0x268 - 0x240];
    FLOAT CollisionRadius;     // 0x268
    FLOAT CollisionHeight;     // 0x26c
    BYTE Pad270[0x2f0 - 0x270];
    DWORD bUseCylinderCollision_Pad : 21;
    DWORD bUseCylinderCollision : 1; // 0x2f0 bit 21 (0x200000)

    FMatrix LocalToWorld() const;
    FMatrix WorldToLocal() const;
};

struct FCheckResult
{
    FCheckResult *Next;        // 0x00
    AActor *Actor;             // 0x04
    FVector Location;          // 0x08
    FVector Normal;            // 0x14
    UPrimitive *Primitive;     // 0x20
    FLOAT Time;                // 0x24
};

class UPrimitive
{
public:
    virtual ~UPrimitive();
    BYTE Pad04[0x28 - 0x04];
    FBox BoundingBox;          // 0x28

    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Point, const FVector &Extent, DWORD ExtraNodeFlags);
    virtual UBOOL LineCheck(FCheckResult &Result, AActor *Owner, const FVector &End, const FVector &Start, const FVector &Extent, DWORD ExtraNodeFlags, DWORD TraceFlags);
    virtual FBox GetCollisionBoundingBox(const AActor *Owner) const;
};

class UStaticMesh : public UPrimitive
{
public:
    BYTE Pad40[0x60 - 0x40];
    void *Field60;             // 0x60
    BYTE Pad64[0xe8 - 0x64];
    void *FieldE8;             // 0xe8
    BYTE PadEC[0xf0 - 0xec];
    void *FieldF0;             // 0xf0
    BYTE PadF4[0xf8 - 0xf4];
    void *FieldF8;             // 0xf8
    BYTE PadFC[0x10c - 0xfc];
    void *Field10C;            // 0x10c
    BYTE Pad110[0x124 - 0x110];
    void *Field124;            // 0x124
    BYTE Pad128[0x12c - 0x128];
    void *Field12C;            // 0x12c
    BYTE Pad130[0x134 - 0x130];
    void *Field134;            // 0x134
    DWORD CollisionFlags138;   // 0x138

    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Point, const FVector &Extent, DWORD ExtraNodeFlags);
    virtual UBOOL LineCheck(FCheckResult &Result, AActor *Owner, const FVector &End, const FVector &Start, const FVector &Extent, DWORD ExtraNodeFlags, DWORD TraceFlags);
    virtual FBox GetCollisionBoundingBox(const AActor *Owner) const;
};

struct FStaticMeshCollisionCheck
{
    FCheckResult *Result;      // 0x00
    AActor *Owner;             // 0x04
    UStaticMesh *StaticMesh;   // 0x08
    void *Nodes;               // 0x0c
    void *Triangles;           // 0x10
    void *Vertices;            // 0x14
    void *Materials;           // 0x18

    FStaticMeshCollisionCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, DWORD InFlags);
};

struct FStaticMeshPointCheck : public FStaticMeshCollisionCheck
{
    FVector LocalPoint;        // 0x1c
    FVector LocalExtent;       // 0x28
    FMatrix LocalToWorld;      // 0x34
    FLOAT BestDistance;        // 0x74

    FStaticMeshPointCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InPoint, const FVector &InExtent, DWORD InFlags);
    UBOOL CheckNode(INT NodeIndex, const FBox &Box);
};

struct FStaticMeshLineCheck : public FStaticMeshCollisionCheck
{
    FVector LocalStart;            // 0x1c
    FVector LocalEnd;              // 0x28
    FVector LocalDirection;        // 0x34
    FVector LocalOneOverDirection; // 0x40
    FMatrix LocalToWorld;          // 0x4c

    FStaticMeshLineCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InStart, const FVector &InEnd, DWORD InFlags);
    UBOOL CheckNode(INT NodeIndex, const FBox &Box);
};

struct FStaticMeshExtentLineCheck : public FStaticMeshCollisionCheck
{
    FVector LocalStart;            // 0x1c
    FVector LocalEnd;              // 0x28
    FVector LocalDirection;        // 0x34
    FVector LocalOneOverDirection; // 0x40
    FVector LocalExtent;           // 0x4c
    FVector Start;                 // 0x58
    FVector Extent;                // 0x64
    FVector Direction;             // 0x70
    FMatrix LocalToWorld;          // 0x7c

    FStaticMeshExtentLineCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InStart, const FVector &InEnd, const FVector &InExtent, DWORD InFlags);
    UBOOL CheckNode(INT NodeIndex, const FBox &Box);
};

// ---------------------------------------------------------------------------
// 0x149ad0: UStaticMesh::GetCollisionBoundingBox
FBox UStaticMesh::GetCollisionBoundingBox(const AActor *Owner) const
{
    FBox Result;
    if (Owner->bUseCylinderCollision)
        Result = UPrimitive::GetCollisionBoundingBox(Owner);
    else
        Result = BoundingBox.TransformBy(Owner->LocalToWorld());
    return Result;
}

// ---------------------------------------------------------------------------
// 0x149b60: UStaticMesh::LineCheck
UBOOL UStaticMesh::LineCheck(FCheckResult &Result, AActor *Owner, const FVector &End, const FVector &Start, const FVector &Extent, DWORD ExtraNodeFlags, DWORD TraceFlags)
{
    UBOOL Hit = 0;
    if (Owner->bUseCylinderCollision)
    {
        Hit = !UPrimitive::LineCheck(Result, Owner, End, Start, Extent, ExtraNodeFlags, TraceFlags);
    }
    else
    {
        UBOOL ZeroExtent = (Extent == GMath_Zero);
        DWORD CollisionFlags = CollisionFlags138;
        if (ZeroExtent)
        {
            Hit = FStaticMeshLineCheck(&Result, Owner, this, Start, End, CollisionFlags).CheckNode(0, BoundingBox);
        }
        else
        {
            Hit = FStaticMeshExtentLineCheck(&Result, Owner, this, Start, End, Extent, CollisionFlags).CheckNode(0, BoundingBox);
            if (Hit)
            {
                Result.Actor = Owner;
                Result.Primitive = this;
                Result.Normal.Normalize();
            }
        }

        if (Hit)
        {
            FVector Direction = End - Start;
            Result.Time = Clamp(Result.Time - Clamp(0.1f, 0.1f / Direction.Size(), 1.0f / Direction.Size()), 0.0f, 1.0f);
            Result.Location = Start + Direction * Result.Time;
        }
    }

    return !Hit;
}

// ---------------------------------------------------------------------------
// 0x149db0: UStaticMesh::PointCheck
UBOOL UStaticMesh::PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Point, const FVector &Extent, DWORD ExtraNodeFlags)
{
    UBOOL Hit = 0;
    DWORD CollisionFlags = CollisionFlags138;
    if (Owner->bUseCylinderCollision)
        Hit = !UPrimitive::PointCheck(Result, Owner, Point, Extent, ExtraNodeFlags);
    else
        Hit = FStaticMeshPointCheck(&Result, Owner, this, Point, Extent, CollisionFlags).CheckNode(0, BoundingBox);
    return !Hit;
}

// ---------------------------------------------------------------------------
// 0x149e50: FindMinMax
#pragma auto_inline(off)
void FindMinMax(FLOAT X0, FLOAT X1, FLOAT X2, FLOAT &OutMin, FLOAT &OutMax)
{
    if (X0 < X1)
    {
        if (X2 < X0)
        {
            OutMin = X2;
            OutMax = X1;
        }
        else
        {
            OutMin = X0;
            OutMax = Max(X1, X2);
        }
    }
    else
    {
        if (X2 < X1)
        {
            OutMin = X2;
            OutMax = X0;
        }
        else
        {
            OutMin = X1;
            OutMax = Max(X0, X2);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x149ee0: FLineBoxIntersection
UBOOL FLineBoxIntersection(const FBox &Box, const FVector &Start, const FVector &End, const FVector &Direction, const FVector &OneOverDirection)
{
    UBOOL Inside = 1;
    FVector Time(0.f, 0.f, 0.f);

    for (INT i = 0; i < 3; i++)
    {
        if (Start[i] < Box.Min[i])
        {
            if (Direction[i] <= 0.f)
                return 0;
            else
            {
                Inside = 0;
                Time[i] = (Box.Min[i] - Start[i]) * OneOverDirection[i];
            }
        }
        else if (Start[i] > Box.Max[i])
        {
            if (Direction[i] >= 0.f)
                return 0;
            else
            {
                Inside = 0;
                Time[i] = (Box.Max[i] - Start[i]) * OneOverDirection[i];
            }
        }
    }

    if (Inside)
        return 1;

    FLOAT MaxTime = Max(Max(Time.X, Time.Y), Time.Z);
    if (MaxTime >= 0.f && MaxTime <= 1.f)
    {
        FVector Hit = Start + Direction * MaxTime;
        if (Hit.X > Box.Min.X - 0.1f && Hit.X < Box.Max.X + 0.1f &&
            Hit.Y > Box.Min.Y - 0.1f && Hit.Y < Box.Max.Y + 0.1f &&
            Hit.Z > Box.Min.Z - 0.1f && Hit.Z < Box.Max.Z + 0.1f)
            return 1;
    }
    return 0;
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// External LTCG callee bodies (only so linker assigns their retail CCs).
#pragma auto_inline(off)
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

FBox &FBox::operator+=(const FVector &V)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, V.X); Min.Y = ::Min(Min.Y, V.Y); Min.Z = ::Min(Min.Z, V.Z);
        Max.X = ::Max(Max.X, V.X); Max.Y = ::Max(Max.Y, V.Y); Max.Z = ::Max(Max.Z, V.Z);
    }
    else
    {
        Min = Max = V;
    }
    return *this;
}

FBox FBox::TransformBy(const FMatrix &M) const
{
    FBox NewBox(GMath_UnitX, GMath_Zero);
    for (INT i = 0; i < 2; i++)
        for (INT j = 0; j < 2; j++)
            for (INT k = 0; k < 2; k++)
                NewBox += FVector(M.TransformFPlane(FPlane(FVector(GetExtrema(i).X, GetExtrema(j).Y, GetExtrema(k).Z), 1.f)));
    return NewBox;
}

FStaticMeshCollisionCheck::FStaticMeshCollisionCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, DWORD InFlags)
{
    Result = InResult;
    Owner = InOwner;
    StaticMesh = InStaticMesh;
    Nodes = InFlags ? InStaticMesh->Field134 : InStaticMesh->FieldF8;
    Triangles = InFlags ? InStaticMesh->Field124 : InStaticMesh->FieldE8;
    Vertices = InFlags ? InStaticMesh->Field12C : InStaticMesh->FieldF0;
    Materials = InFlags ? InStaticMesh->Field10C : InStaticMesh->Field60;
    GStaticMeshCollisionChecks++;
}

FStaticMeshPointCheck::FStaticMeshPointCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InPoint, const FVector &InExtent, DWORD InFlags)
    : FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, InFlags)
{
    FMatrix WorldToLocal = InOwner->WorldToLocal();
    LocalPoint = WorldToLocal.TransformFVector(InPoint);
    LocalExtent = WorldToLocal.TransformFVector(InExtent);
    LocalToWorld = InOwner->LocalToWorld();
    BestDistance = 100000.f;
}

FMatrix AActor::WorldToLocal() const
{
    FLOAT SR, CR, SP, CP, SY, CY;
    GMath.SinCos(Rotation.Yaw, &SY, &CY);
    GMath.SinCos(Rotation.Pitch, &SP, &CP);
    GMath.SinCos(Rotation.Roll, &SR, &CR);
    FLOAT LX = Location.X, LY = Location.Y, LZ = Location.Z;
    return FMatrix(
        FPlane(CP * CY, CP * SY, SP, 0.f),
        FPlane(CY * SP * SR - CR * SY, CR * CY + SP * SR * SY, -CP * SR, 0.f),
        FPlane(-CR * CY * SP - SR * SY, CY * SR - CR * SP * SY, CP * CR, 0.f),
        FPlane(-LX, -LY, -LZ, 1.f));
}

FStaticMeshLineCheck::FStaticMeshLineCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InStart, const FVector &InEnd, DWORD InFlags)
    : FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, InFlags)
{
    InResult->Time = 1.f;
    FMatrix WorldToLocal = InOwner->WorldToLocal();
    LocalToWorld = InOwner->LocalToWorld();
    LocalStart = WorldToLocal.TransformFVector(InStart);
    LocalEnd = WorldToLocal.TransformFVector(InEnd);
    LocalDirection = LocalEnd - LocalStart;
    LocalOneOverDirection = FVector(1.f / LocalDirection.X, 1.f / LocalDirection.Y, 1.f / LocalDirection.Z);
}

FStaticMeshExtentLineCheck::FStaticMeshExtentLineCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, const FVector &InStart, const FVector &InEnd, const FVector &InExtent, DWORD InFlags)
    : FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, InFlags)
{
    Start = InStart;
    Extent = InExtent;
    Direction = InEnd - InStart;
    InResult->Time = 1.f;
    FMatrix WorldToLocal = InOwner->WorldToLocal();
    LocalToWorld = InOwner->LocalToWorld();
    LocalStart = WorldToLocal.TransformFVector(InStart);
    LocalEnd = WorldToLocal.TransformFVector(InEnd);
    LocalExtent = WorldToLocal.TransformFVector(InExtent);
    LocalDirection = LocalEnd - LocalStart;
    LocalOneOverDirection = FVector(1.f / LocalDirection.X, 1.f / LocalDirection.Y, 1.f / LocalDirection.Z);
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

void Driver_149ad0(void *Mem, const AActor *A, FBox *Out)
{
    Escape((void *)&GMath_Zero);
    Escape((void *)&GMath_UnitX);
    UStaticMesh *M = new(Mem) UStaticMesh;
    Escape(M);
    *Out = M->GetCollisionBoundingBox(A);
    FBox B = Out->TransformBy(A->LocalToWorld());
    Escape(&B);
}

UBOOL Driver_149b60(void *Mem, FCheckResult *R, AActor *A, const FVector *End, const FVector *Start, const FVector *Extent, DWORD Flags1, DWORD Flags2)
{
    Escape((void *)&GMath_Zero);
    Escape(&GStaticMeshCollisionChecks);
    UStaticMesh *M = new(Mem) UStaticMesh;
    Escape(M);
    return M->LineCheck(*R, A, *End, *Start, *Extent, Flags1, Flags2);
}

UBOOL Driver_149db0(void *Mem, FCheckResult *R, AActor *A, const FVector *Point, const FVector *Extent, DWORD Flags)
{
    Escape(&GStaticMeshCollisionChecks);
    UStaticMesh *M = new(Mem) UStaticMesh;
    Escape(M);
    return M->PointCheck(*R, A, *Point, *Extent, Flags);
}

void Driver_149e50(FLOAT X0, FLOAT X1, FLOAT X2, FLOAT *OutMin, FLOAT *OutMax)
{
    FindMinMax(X0, X1, X2, *OutMin, *OutMax);
    FindMinMax(X1, X2, X0, *OutMin, *OutMax);
}

UBOOL Driver_149ee0(const FBox *Box, const FVector *Start, const FVector *End, const FVector *Dir, const FVector *OneOverDir)
{
    UBOOL R = FLineBoxIntersection(*Box, *Start, *End, *Dir, *OneOverDir);
    R += FLineBoxIntersection(*Box, *End, *Start, *Dir, *OneOverDir);
    return R;
}
