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

// 0x1181d0: is the cube wholly inside the box?
// Near miss: retail loads W before Y for the Y+ test (fld [ecx+0xc]; fadd [ecx+4]).
INT __fastcall CubeInsideBox_1181d0(const FCube *C, const FBoxMinMax *B)
{
    if (C->X - C->W < B->Min.X || C->X + C->W > B->Max.X ||
        C->Y - C->W < B->Min.Y || C->Y + C->W > B->Max.Y ||
        C->Z - C->W < B->Min.Z || C->Z + C->W > B->Max.Z)
        return 0;
    return 1;
}

// 0x118240: octree children a box touches around a centre (LTCG: ESI/EDI).
INT ChildrenTouched_118240(const FVec3 *P, const FBoxMinMax *B, INT *Out)
{
    INT N = 0;
    if (B->Max.X > P->X) {
        if (B->Max.Y > P->Y) {
            if (B->Max.Z > P->Z) Out[N++] = 7;
            if (B->Min.Z < P->Z) Out[N++] = 6;
        }
        if (B->Min.Y < P->Y) {
            if (B->Max.Z > P->Z) Out[N++] = 5;
            if (B->Min.Z < P->Z) Out[N++] = 4;
        }
    }
    if (B->Min.X < P->X) {
        if (B->Max.Y > P->Y) {
            if (B->Max.Z > P->Z) Out[N++] = 3;
            if (B->Min.Z < P->Z) Out[N++] = 2;
        }
        if (B->Min.Y < P->Y) {
            if (B->Max.Z > P->Z) Out[N++] = 1;
            if (B->Min.Z < P->Z) Out[N++] = 0;
        }
    }
    return N;
}

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
INT Driver_118240(const FVec3 *P, const FBoxMinMax *B, INT *O) { return ChildrenTouched_118240(P, B, O) + ChildrenTouched_118240(P + 1, B + 1, O + 8); }
