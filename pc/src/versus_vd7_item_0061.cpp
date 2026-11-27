// Work item 0061: Versus RVA 0x135ac0-0x135d94, 6 functions, 664 bytes.
// All six functions are VC7.0 LTCG (custom calling conventions); verified with try_ltcg.py.
//   0x135ac0: UnnamedSceneAllocDerived_135ac0::~UnnamedSceneAllocDerived_135ac0 (this in ESI)
//   0x135b00: FZoneVisibility::FilterBox (this on stack, Box in EAX)
//   0x135b80: FZoneVisibility::FilterSphere (this in EDI, Sphere in ECX)
//   0x135c10: FDynamicActor::BoxDistanceSquared (this in EAX, Point in ECX)
//   0x135d00: FDynamicActor::CheckCullDistance (this in EAX, Viewport in ECX, ViewOrigin on stack)

#include "versus_zone_visibility.h"

extern "C" double __cdecl tan(double);
#pragma intrinsic(tan)

inline FLOAT appTan(FLOAT V) { return (FLOAT)tan(V); }
template <class T> inline T Square(const T A) { return A * A; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

class FPlane : public FVector
{
public:
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

class FSphere : public FPlane
{
public:
    FSphere() {}
};

// Versus FBox is 0x18 bytes (no IsValid byte).
class FBox
{
public:
    FVector Min;
    FVector Max;

    FBox() {}
    FBox(const FBox &B) : Min(B.Min), Max(B.Max) {}
    void GetCenterAndExtents(FVector &Center, FVector &Extents) const;
};

enum EOutcode
{
    OUTCODE_Inside  = 1,
    OUTCODE_Outside = 2,
};

class FConvexVolume
{
public:
    FPlane BoundingPlanes[32];
    INT NumPlanes;

    BYTE SphereCheck(const FSphere &Sphere) const;
    BYTE BoxCheck(const FVector &Origin, const FVector &Extent) const;
};

// RVA 0x135ac0: Destructor for unnamed scene allocation struct (neutral name;
// unwind funclet at 0x2d7cf0 jumps here with this in ESI, and base unwind at
// 0x2d7cf8 jumps to 0x135a80 freeing +0x10).
class UnnamedSceneAllocBase_135a80
{
public:
    BYTE unk_00[0x10];
    void *AllocPtr_10;

    ~UnnamedSceneAllocBase_135a80()
    {
        if (AllocPtr_10)
            GMalloc->Free(AllocPtr_10);
    }
};

class UnnamedSceneAllocDerived_135ac0 : public UnnamedSceneAllocBase_135a80
{
public:
    void *AllocPtr_14;

    __declspec(noinline) ~UnnamedSceneAllocDerived_135ac0();
};

UnnamedSceneAllocDerived_135ac0::~UnnamedSceneAllocDerived_135ac0()
{
    if (AllocPtr_14)
        GMalloc->Free(AllocPtr_14);
}

// RVA 0x135b00: FZoneVisibility::FilterBox
__declspec(noinline) UBOOL FZoneVisibility::FilterBox(const FBox &Box) const
{
    FVector Extents;
    FVector Center;
    Box.GetCenterAndExtents(Center, Extents);

    UBOOL Visible = 0;
    for (TList<FConvexVolume *> *Volume = Portals; Volume; Volume = Volume->Next)
    {
        if (Volume->Element->BoxCheck(Center, Extents) & OUTCODE_Inside)
        {
            Visible = 1;
            break;
        }
    }
    if (Visible)
    {
        for (TList<FConvexVolume *> *Volume = AntiPortals; Volume; Volume = Volume->Next)
        {
            if (!(Volume->Element->BoxCheck(Center, Extents) & OUTCODE_Outside))
            {
                Visible = 0;
                break;
            }
        }
    }
    return Visible;
}

// RVA 0x135b80: FZoneVisibility::FilterSphere
__declspec(noinline) UBOOL FZoneVisibility::FilterSphere(const FSphere &Sphere) const
{
    UBOOL Visible = 0;
    for (TList<FConvexVolume *> *Volume = Portals; Volume; Volume = Volume->Next)
    {
        if (Volume->Element->SphereCheck(Sphere) & OUTCODE_Inside)
        {
            Visible = 1;
            break;
        }
    }
    if (Visible)
    {
        for (TList<FConvexVolume *> *Volume = AntiPortals; Volume; Volume = Volume->Next)
        {
            if (!(Volume->Element->SphereCheck(Sphere) & OUTCODE_Outside))
            {
                Visible = 0;
                break;
            }
        }
    }
    return Visible;
}

class APlayerController
{
public:
    BYTE unk_00[0x308];
    FLOAT FovAngle;
};

class UViewport
{
public:
    BYTE unk_00[0x30];
    APlayerController *Actor;
    BYTE unk_34[0x14c - 0x34];
    INT IsOrthoFlag;
};

class AActor
{
public:
    BYTE unk_00[0x254];
    FLOAT CullDistance;
};

class FDynamicActor
{
public:
    AActor *Actor;
    BYTE unk_04[0x90 - 0x04];
    FBox BoundingBox;

    __declspec(noinline) FLOAT BoxDistanceSquared(const FVector &Point) const;
    static __declspec(noinline) UBOOL CheckCullDistance(const FDynamicActor *DynamicActor, UViewport *Viewport, const FVector &ViewOrigin);
};

// RVA 0x135c10: FDynamicActor::BoxDistanceSquared
FLOAT FDynamicActor::BoxDistanceSquared(const FVector &Point) const
{
    FBox Box = BoundingBox;
    FLOAT DistSquared = 0.0f;

    if (Point.X < Box.Min.X)
        DistSquared = Square(Point.X - Box.Min.X);
    else if (Point.X > Box.Max.X)
        DistSquared = Square(Point.X - Box.Max.X);

    if (Point.Y < Box.Min.Y)
        DistSquared += Square(Point.Y - Box.Min.Y);
    else if (Point.Y > Box.Max.Y)
        DistSquared += Square(Point.Y - Box.Max.Y);

    if (Point.Z < Box.Min.Z)
        DistSquared += Square(Point.Z - Box.Min.Z);
    else if (Point.Z > Box.Max.Z)
        DistSquared += Square(Point.Z - Box.Max.Z);

    return DistSquared;
}

// RVA 0x135d00: FDynamicActor::CheckCullDistance
UBOOL FDynamicActor::CheckCullDistance(const FDynamicActor *DynamicActor, UViewport *Viewport, const FVector &ViewOrigin)
{
    if (DynamicActor->Actor->CullDistance != 0.0f && Viewport->IsOrthoFlag != 1)
    {
        FLOAT TanHalfFov = appTan(Viewport->Actor->FovAngle * (3.1415926535897932f / 360.0f));
        FLOAT DistSquared = DynamicActor->BoxDistanceSquared(ViewOrigin) * TanHalfFov * TanHalfFov;
        if (DynamicActor->Actor->CullDistance > 0.0f)
            return Square(DynamicActor->Actor->CullDistance) >= DistSquared;
        else
            return -Square(DynamicActor->Actor->CullDistance) <= DistSquared;
    }
    return 1;
}

// ============================================================================
// Scaffolding for the LTCG link, not part of the unit.
// ============================================================================
void Escape(void *);

// Stand-in bodies for retail LTCG callees so the linker reproduces their
// custom register calling conventions.
#pragma auto_inline(off)
void FBox::GetCenterAndExtents(FVector &Center, FVector &Extents) const
{
    Extents.X = (Max.X - Min.X) * 0.5f;
    Extents.Y = (Max.Y - Min.Y) * 0.5f;
    Extents.Z = (Max.Z - Min.Z) * 0.5f;
    Center.X = Min.X + Extents.X;
    Center.Y = Min.Y + Extents.Y;
    Center.Z = Min.Z + Extents.Z;
}

extern UBOOL GIsSSE;
extern INT GDummy0, GDummy1, GDummy2;
BYTE FConvexVolume::BoxCheck(const FVector &Origin, const FVector &Extent) const
{
    __declspec(align(16)) FLOAT LocalBuf[8];
    BYTE Result = OUTCODE_Inside;
    if (GIsSSE && NumPlanes >= 4)
    {
        INT A = GDummy0 / GDummy1;
        INT B = A << GDummy2;
        INT C = NumPlanes - (NumPlanes % 4);
        for (INT i = 0; i < C; i += 4)
        {
            A += i; B ^= A;
            LocalBuf[0] = Origin.X + Extent.X;
            LocalBuf[1] = Origin.Y + Extent.Y;
            FLOAT Push = BoundingPlanes[i].X * Extent.X + BoundingPlanes[i].Y * Extent.Y + BoundingPlanes[i].Z * Extent.Z;
            FLOAT Dist = BoundingPlanes[i].X * Origin.X + BoundingPlanes[i].Y * Origin.Y + BoundingPlanes[i].Z * Origin.Z - BoundingPlanes[i].W;
            if (Dist > Push + LocalBuf[0]) return OUTCODE_Outside;
            if (Dist > -Push + LocalBuf[1]) Result |= OUTCODE_Outside;
        }
        GDummy0 = A + B;
    }
    for (INT i = 0; i < NumPlanes; i++)
    {
        FLOAT Push = BoundingPlanes[i].X * Extent.X + BoundingPlanes[i].Y * Extent.Y + BoundingPlanes[i].Z * Extent.Z;
        FLOAT Dist = BoundingPlanes[i].X * Origin.X + BoundingPlanes[i].Y * Origin.Y + BoundingPlanes[i].Z * Origin.Z - BoundingPlanes[i].W;
        if (Dist > Push) return OUTCODE_Outside;
        if (Dist > -Push) Result |= OUTCODE_Outside;
    }
    return Result;
}

BYTE FConvexVolume::SphereCheck(const FSphere &Sphere) const
{
    __declspec(align(16)) FLOAT LocalBuf[8];
    BYTE Result = OUTCODE_Inside;
    if (GIsSSE && NumPlanes >= 4)
    {
        INT Rem = NumPlanes % 4;
        INT Count = NumPlanes - Rem;
        LocalBuf[0] = Sphere.X * 1.0f;
        for (INT i = 0; i < Count; i += 4)
        {
            LocalBuf[0] += BoundingPlanes[i].X * Sphere.X + BoundingPlanes[i].Y * Sphere.Y + BoundingPlanes[i].Z * Sphere.Z - BoundingPlanes[i].W;
        }
        if (LocalBuf[0] > Sphere.W) return OUTCODE_Outside;
        if (Rem)
        {
            for (INT i = Count; i < NumPlanes; i++)
            {
                FLOAT Dist = BoundingPlanes[i].X * Sphere.X + BoundingPlanes[i].Y * Sphere.Y + BoundingPlanes[i].Z * Sphere.Z - BoundingPlanes[i].W;
                if (Dist > Sphere.W) return OUTCODE_Outside;
                if (Dist > -Sphere.W) Result |= OUTCODE_Outside;
            }
        }
        return Result;
    }
    for (INT i = 0; i < NumPlanes; i++)
    {
        FLOAT Dist = BoundingPlanes[i].X * Sphere.X + BoundingPlanes[i].Y * Sphere.Y + BoundingPlanes[i].Z * Sphere.Z - BoundingPlanes[i].W;
        if (Dist > Sphere.W) return OUTCODE_Outside;
        if (Dist > -Sphere.W) Result |= OUTCODE_Outside;
    }
    return Result;
}
#pragma auto_inline(on)

void Driver_135ac0(UnnamedSceneAllocDerived_135ac0 *Obj)
{
    Escape(&GMalloc);
    Escape(Obj);
    Obj->~UnnamedSceneAllocDerived_135ac0();
}

UBOOL Driver_135b00(const FZoneVisibility *Zones, INT ZoneIdx, const FDynamicActor *DynActor)
{
    Escape(&GIsSSE);
    return Zones[ZoneIdx].FilterBox(DynActor->BoundingBox);
}

UBOOL __fastcall Driver_135b80(const FSphere *S, const FZoneVisibility *Zones)
{
    if (!S) Escape(&GIsSSE);
    return Zones->FilterSphere(*S);
}



FLOAT Driver_135c10(const FDynamicActor *DynActor, const FVector *Pt)
{
    return DynActor->BoxDistanceSquared(*Pt);
}

struct FLevelSceneNodeStub
{
    INT Field0;
    UViewport *Viewport;
    BYTE unk_08[0x194 - 0x08];
    FVector ViewOrigin;
};

UBOOL Driver_135d00(const FDynamicActor *DynActor, FLevelSceneNodeStub *SceneNode)
{
    Escape(SceneNode);
    return FDynamicActor::CheckCullDistance(DynActor, SceneNode->Viewport, SceneNode->ViewOrigin);
}
