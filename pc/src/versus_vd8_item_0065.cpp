// Work item 0065: Versus RVA 0x137460 (70 bytes)
//
// Retail 0x137460 tests whether a dynamic light's frustum (at +0x50) intersects
// a view frustum, caching the result in bitfields at +0x34 (bit 7 = tested,
// bit 8 = intersects), unless the scene viewport flag at +0x14c overrides it.
// Type names UnnamedSceneContext_137460, UnnamedLight_137460, and
// UnnamedFrustum_137460 are neutral names; UViewport and FSceneNode follow
// nearby published Versus sources (versus_vd5_item_0293.cpp, versus_vd5_item_0303.cpp).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

struct FVector
{
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
};

struct FPlane : public FVector
{
    FLOAT W;
};

struct FSphere : public FVector
{
    FLOAT W;
};

struct UViewport
{
    BYTE unk_00[0x14c];
    INT Flag_14c;
};

struct FSceneNode
{
    BYTE unk_00[0x04];
    UViewport *Viewport;
};

struct UnnamedSceneContext_137460
{
    FSceneNode *SceneNode;
};

struct UnnamedFrustum_137460
{
    FVector Vertices[8];
    FPlane Planes[6];
    FSphere Bounds;

    UBOOL Intersects(const UnnamedFrustum_137460 &Other) const; // 0x51870
};

struct UnnamedLight_137460
{
    BYTE unk_00[0x34];
    BITFIELD unk_34_0 : 7;
    BITFIELD bFrustumTested : 1; // 0x80
    BITFIELD bInFrustum : 1;     // 0x100
    BYTE unk_38[0x18];
    UnnamedFrustum_137460 Frustum; // +0x50

    // 0x137460
    UBOOL IsInViewFrustum(
        UnnamedSceneContext_137460 *Context,
        const UnnamedFrustum_137460 &ViewFrustum);
};

// UnnamedLight_137460::IsInViewFrustum (0x137460)
// __declspec(noinline) keeps it out of line for the link, as retail did at 0x137ac1.
__declspec(noinline) UBOOL UnnamedLight_137460::IsInViewFrustum(
    UnnamedSceneContext_137460 *Context,
    const UnnamedFrustum_137460 &ViewFrustum)
{
    if (Context->SceneNode->Viewport->Flag_14c)
        return 1;
    if (bFrustumTested)
        return bInFrustum;
    bInFrustum = Frustum.Intersects(ViewFrustum);
    bFrustumTested = 1;
    return bInFrustum;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
UBOOL CheckFaceOverlap(
    const FVector *A, const FVector *B, const FVector *C,
    const FVector *D, const FVector *E);
void SomeCall(void *P);

extern FVector *GFaceTable;
__declspec(noinline) UBOOL UnnamedFrustum_137460::Intersects(
    const UnnamedFrustum_137460 &Other) const
{
    FVector *T = GFaceTable;
    if (CheckFaceOverlap(&Other.Vertices[0], &Other.Vertices[1], &Other.Vertices[2], &T[0], &T[1]))
        return 1;
    if (CheckFaceOverlap(&Other.Vertices[3], &Other.Vertices[4], &Other.Vertices[5], &T[2], &T[3]))
        return 1;
    if (CheckFaceOverlap(&Vertices[0], &Other.Vertices[6], &Other.Vertices[7], &T[4], &T[5]))
        return 1;
    return Bounds.X > Other.Bounds.X;
}

void Driver_137460(
    UnnamedLight_137460 **Lights, INT Count,
    UnnamedSceneContext_137460 *Ctx, const UnnamedFrustum_137460 *View, INT Mode)
{
    for (INT i = 0; i < Count; i++)
    {
        UnnamedLight_137460 *L = Lights[i];
        SomeCall(L);
        if (Mode == 1 && L->IsInViewFrustum(Ctx, *View))
            Escape(L);
        else if (Mode == 2 && L->IsInViewFrustum(Ctx + 1, *View))
            Escape(L + 1);
        else if (Mode == 3 && L->IsInViewFrustum(Ctx, *(View + 1)))
            Escape((void *)View);
        else if (Mode == 4)
        {
            const UnnamedFrustum_137460 *F = &L->Frustum;
            SomeCall((void *)F);
            if (F->Intersects(*View))
                Escape((void *)F);
            SomeCall((void *)View);
        }
    }
}
