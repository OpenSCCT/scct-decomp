// Work item 0073: FStaticMeshPointCheck constructor and plane check (Versus RVA 0x141400, 0x141460).
// Both functions were compiled with VC7.0 /GL and linked with /LTCG.

typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class AActor;
class UPrimitive {};
class UStaticMesh : public UPrimitive {};

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FVector operator+(const FVector &V) const
    {
        return FVector(X + V.X, Y + V.Y, Z + V.Z);
    }

    FVector operator*(FLOAT Scale) const
    {
        return FVector(X * Scale, Y * Scale, Z * Scale);
    }
};

inline FVector operator*(FLOAT Scale, const FVector &V)
{
    return FVector(Scale * V.X, Scale * V.Y, Scale * V.Z);
}

struct FPlane : public FVector
{
    FLOAT W;

    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}

    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

inline FLOAT FBoxPushOut(const FVector &Normal, const FVector &Size)
{
    FLOAT PX = Normal.X * Size.X;
    FLOAT PY = Normal.Y * Size.Y;
    FLOAT PZ = Normal.Z * Size.Z;
    *(DWORD *)&PX &= 0x7fffffff;
    *(DWORD *)&PY &= 0x7fffffff;
    *(DWORD *)&PZ &= 0x7fffffff;
    return PX + PY + PZ;
}

struct FMatrix
{
    FLOAT M[4][4];

    static FMatrix Identity;

    FMatrix Inverse() const;
};

struct FBox
{
    FVector Min;
    FVector Max;
};

extern FVector *GBoxInitMin;
extern FVector *GBoxInitMax;

struct FCheckResult
{
    FCheckResult *GetNext;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UPrimitive *Primitive;
    FLOAT Time;
    INT Item;
};

class FStaticMeshCollisionCheck
{
public:
    FCheckResult *Result;       // 0x000
    UStaticMesh *StaticMesh;    // 0x004
    AActor *Owner;              // 0x008
    FMatrix LocalToWorld;       // 0x00c
    FVector Extent;             // 0x04c
    DWORD ExtraNodeFlags;       // 0x058
    INT NumPlanes;              // 0x05c
    BYTE unk_60[0x0c];          // 0x060
    FBox LocalBox;              // 0x06c
    BYTE unk_84[0x08];          // 0x084
    FMatrix WorldToLocal;       // 0x08c
    FPlane Planes[80];          // 0x0cc
    INT *PlaneItems;            // 0x5cc

    FStaticMeshCollisionCheck(
        FCheckResult *InResult,
        UStaticMesh *InStaticMesh,
        AActor *InOwner,
        FVector InExtent,
        DWORD InExtraNodeFlags
    );
};

class FStaticMeshPointCheck : public FStaticMeshCollisionCheck
{
public:
    FVector Location;           // 0x5d0
    FLOAT BestDistance;         // 0x5dc

    FStaticMeshPointCheck(
        FCheckResult *InResult,
        UStaticMesh *InStaticMesh,
        AActor *InOwner,
        const FVector &InLocation,
        const FVector &InExtent,
        FLOAT InExtraNodeFlags
    );

    UBOOL CheckPlane(const FPlane &Plane, INT Item);
};

// FStaticMeshPointCheck::FStaticMeshPointCheck (RVA 0x141400)
__declspec(noinline) FStaticMeshPointCheck::FStaticMeshPointCheck(
    FCheckResult *InResult,
    UStaticMesh *InStaticMesh,
    AActor *InOwner,
    const FVector &InLocation,
    const FVector &InExtent,
    FLOAT InExtraNodeFlags
)
    : FStaticMeshCollisionCheck(InResult, InStaticMesh, InOwner, InExtent, (INT)InExtraNodeFlags),
      Location(InLocation),
      BestDistance(100000.0f)
{
}

// FStaticMeshPointCheck::CheckPlane (RVA 0x141460)
__declspec(noinline) UBOOL FStaticMeshPointCheck::CheckPlane(const FPlane &Plane, INT Item)
{
    FLOAT PushOut = FBoxPushOut(Plane, Extent);
    FLOAT Distance = Plane.PlaneDot(Location);

    if (Distance > 0.0f && Distance < BestDistance)
    {
        if (Distance < PushOut)
        {
            BestDistance = Distance;
            Result->Location = Location + (PushOut - Distance) * (Plane * 1.02f);
            Result->Normal = Plane;
            Result->Actor = Owner;
            Result->Primitive = StaticMesh;
            Result->Item = Item;
            Result->Time = 0.0f;
        }
        else
            return 0;
    }

    return Distance < PushOut;
}

// Scaffolding for the LTCG link, not part of the unit.
// FStaticMeshCollisionCheck::FStaticMeshCollisionCheck (retail 0x1410d0) is reproduced
// here only so the LTCG linker assigns its retail register convention (this in ebx,
// Result in eax, StaticMesh in ecx, Owner in edx).
extern FMatrix ActorLocalToWorld(const AActor *Actor);

__declspec(noinline) FStaticMeshCollisionCheck::FStaticMeshCollisionCheck(
    FCheckResult *InResult,
    UStaticMesh *InStaticMesh,
    AActor *InOwner,
    FVector InExtent,
    DWORD InExtraNodeFlags
)
    : Result(InResult),
      StaticMesh(InStaticMesh),
      Owner(InOwner),
      Extent(InExtent),
      ExtraNodeFlags(InExtraNodeFlags)
{
    LocalBox.Min = *GBoxInitMin;
    LocalBox.Max = *GBoxInitMax;
    if (Owner)
    {
        LocalToWorld = ActorLocalToWorld(Owner);
        WorldToLocal = LocalToWorld.Inverse();
    }
    else
    {
        WorldToLocal = FMatrix::Identity;
        LocalToWorld = WorldToLocal;
    }
}

void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

FStaticMeshPointCheck *Driver_141400(
    FStaticMeshPointCheck *Mem,
    FCheckResult *InResult,
    UStaticMesh *InStaticMesh,
    AActor *InOwner,
    const FVector *InLocation,
    const FVector *InExtent,
    FLOAT InExtraNodeFlags
)
{
    Escape(&GBoxInitMin);
    Escape(&GBoxInitMax);
    Escape(&FMatrix::Identity);
    return new (Mem) FStaticMeshPointCheck(
        InResult, InStaticMesh, InOwner, *InLocation, *InExtent, InExtraNodeFlags);
}

UBOOL Driver_141460(FStaticMeshPointCheck *Check, const FPlane *Plane, INT Item)
{
    return Check->CheckPlane(*Plane, Item);
}
