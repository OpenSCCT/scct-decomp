// Work item 0372: box/sphere octree helpers (RVA 0x118110-0x1183af).
// Names are neutral; the layout is Min (0..8) / Max (0xc..0x14) like FBox,
// and a sphere is centre XYZ plus extent W at 0xc.
typedef int INT;
typedef float FLOAT;

struct FVec3 { FLOAT X, Y, Z; };
struct FBoxMinMax { FVec3 Min; FVec3 Max; };
struct FCube { FLOAT X, Y, Z, W; };


// 0x118110: do two boxes overlap?
INT __fastcall BoxesOverlap_118110(const FBoxMinMax *A, const FBoxMinMax *B)
{
    if (!(B->Min.X > A->Max.X) && !(A->Min.X > B->Max.X) &&
        !(B->Min.Y > A->Max.Y) && !(A->Min.Y > B->Max.Y) &&
        !(B->Min.Z > A->Max.Z) && !(A->Min.Z > B->Max.Z))
        return 1;
    return 0;
}

// 0x118170: child cube of an octree node (LTCG: result in EAX).
#pragma auto_inline(off)
void ChildCube_118170(FCube *Out, INT Index, const FCube *In)
{
    Out->W = In->W * 0.5f;
    Out->X = (FLOAT)(((Index >> 1) & 2) - 1) * Out->W + In->X;
    Out->Y = (FLOAT)((Index & 2) - 1) * Out->W + In->Y;
    Out->Z = (FLOAT)((Index & 1) * 2 - 1) * Out->W + In->Z;
}
#pragma auto_inline(on)

// 0x118340: which child holds the point, or -1 if it straddles.
INT __fastcall ChildIndex_118340(const FBoxMinMax *B, const FVec3 *P)
{
    INT Index = 0;
    if (B->Min.X > P->X) Index = 4;
    else if (B->Max.X > P->X) return -1;
    if (B->Min.Y > P->Y) Index |= 2;
    else if (B->Max.Y > P->Y) return -1;
    if (B->Min.Z > P->Z) Index |= 1;
    else if (B->Max.Z > P->Z) return -1;
    return Index;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_118170(FCube *O, INT I, const FCube *C) { ChildCube_118170(O, I, C); }
