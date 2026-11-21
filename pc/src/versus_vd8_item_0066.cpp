// w4_item_0066.cpp -- Versus RVA 0x138f90 and 0x138fb0
//
// Neutral class/function names are used because retail symbols are not present.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FSphere : public FVector {
    FLOAT W;
};

// Neutral name for the 8-byte element with non-trivial ctor/dtor at +0x24 of UnnamedStruct_138f90.
struct UnnamedElem_138f90 {
    DWORD unk_00;
    DWORD unk_04;

    UnnamedElem_138f90();
    ~UnnamedElem_138f90();
};

// Neutral name for the 0x298-byte structure constructed at RVA 0x138f90.
struct UnnamedStruct_138f90 {
    BYTE unk_00[0x24];
    UnnamedElem_138f90 Elements[64];
    BYTE unk_224[0x74];

    UnnamedStruct_138f90();
};

// Neutral name for the structure whose bounding box (+0x90..+0xa4) and sphere (+0xa8..+0xb4)
// are compared against a view origin at RVA 0x138fb0.
struct UnnamedBounds_138fb0 {
    BYTE unk_00[0x90];
    FVector BoxMin;
    FVector BoxMax;
    FSphere BoundingSphere;
};

// RVA 0x138f90: default constructor initializing Elements[64] via eh_vector_constructor_iterator.
UnnamedStruct_138f90::UnnamedStruct_138f90()
{
}

// RVA 0x138fb0: compare two bounded objects against ViewOrigin along the thinnest box axis.
UBOOL CompareBounds_138fb0(
    const UnnamedBounds_138fb0 *A,
    const UnnamedBounds_138fb0 *B,
    const FVector *ViewOrigin)
{
    FVector ASize = A->BoxMax - A->BoxMin;
    FLOAT MinDim;
    INT Axis;
    UBOOL bSide;
    UBOOL bUseB = 0;

    if (ASize.X < ASize.Y && ASize.X < ASize.Z) {
        MinDim = ASize.X;
        Axis = 0;
        bSide = (A->BoxMin.X + A->BoxMax.X) * 0.5f > ViewOrigin->X;
    } else if (ASize.Y < ASize.X && ASize.Y < ASize.Z) {
        MinDim = ASize.Y;
        Axis = 1;
        bSide = (A->BoxMax.Y + A->BoxMin.Y) * 0.5f > ViewOrigin->Y;
    } else {
        MinDim = ASize.Z;
        Axis = 2;
        bSide = (A->BoxMin.Z + A->BoxMax.Z) * 0.5f > ViewOrigin->Z;
    }

    FVector BSize = B->BoxMax - B->BoxMin;

    if (BSize.X < MinDim && BSize.X < BSize.Y && BSize.X < BSize.Z) {
        bUseB = 1;
        Axis = 0;
        bSide = (B->BoxMin.X + B->BoxMax.X) * 0.5f > ViewOrigin->X;
    } else if (BSize.Y < MinDim && BSize.Y < BSize.X && BSize.Y < BSize.Z) {
        bUseB = 1;
        Axis = 1;
        bSide = (B->BoxMax.Y + B->BoxMin.Y) * 0.5f > ViewOrigin->Y;
    } else if (BSize.Z < MinDim) {
        bUseB = 1;
        Axis = 2;
        bSide = (B->BoxMax.Z + B->BoxMin.Z) * 0.5f > ViewOrigin->Z;
    }

    if (!bUseB) {
        if (Axis == 0) {
            if (bSide) {
                return A->BoxMin.X <= B->BoundingSphere.X;
            } else {
                return A->BoxMax.X >= B->BoundingSphere.X;
            }
        } else if (Axis == 1) {
            if (bSide) {
                return A->BoxMin.Y <= B->BoundingSphere.Y;
            } else {
                return A->BoxMax.Y >= B->BoundingSphere.Y;
            }
        } else {
            if (bSide) {
                return A->BoxMin.Z <= B->BoundingSphere.Z;
            } else {
                return A->BoxMax.Z >= B->BoundingSphere.Z;
            }
        }
    } else {
        if (Axis == 0) {
            if (bSide) {
                return A->BoundingSphere.X <= B->BoxMin.X;
            } else {
                return A->BoundingSphere.X >= B->BoxMax.X;
            }
        } else if (Axis == 1) {
            if (bSide) {
                return A->BoundingSphere.Y <= B->BoxMin.Y;
            } else {
                return A->BoundingSphere.Y >= B->BoxMax.Y;
            }
        } else {
            if (bSide) {
                return A->BoundingSphere.Z <= B->BoxMin.Z;
            } else {
                return A->BoundingSphere.Z >= B->BoxMax.Z;
            }
        }
    }
}

// Scaffolding for the LTCG link, not part of the unit.
inline void *__cdecl operator new(unsigned int, void *Ptr) { return Ptr; }
void *AllocMem_138f90(int Size);
void UseObj_138f90(UnnamedStruct_138f90 *P, void *Owner);

void Driver_138f90(void *Owner1, void *Owner2)
{
    UnnamedStruct_138f90 *P = (UnnamedStruct_138f90 *)AllocMem_138f90(sizeof(UnnamedStruct_138f90));
    if (P) {
        new (P) UnnamedStruct_138f90();
    }
    UseObj_138f90(P, Owner1);

    UnnamedStruct_138f90 *Q = (UnnamedStruct_138f90 *)AllocMem_138f90(sizeof(UnnamedStruct_138f90));
    if (Q) {
        new (Q) UnnamedStruct_138f90();
    }
    UseObj_138f90(Q, Owner2);
}

UBOOL UseResult_138fb0(
    UBOOL R,
    const UnnamedBounds_138fb0 *A,
    const UnnamedBounds_138fb0 *B,
    const FVector *V);

void Driver_138fb0(
    const UnnamedBounds_138fb0 *A,
    const UnnamedBounds_138fb0 *B,
    const FVector *V)
{
    UBOOL R1 = CompareBounds_138fb0(A, B, V);
    UseResult_138fb0(R1, A, B, V);
    UBOOL R2 = CompareBounds_138fb0(B, A, V);
    UseResult_138fb0(R2, B, A, V);
}
