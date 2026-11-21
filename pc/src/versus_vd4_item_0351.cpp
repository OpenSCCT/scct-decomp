// Work item 0351: Versus RVA 0x99810-0x99cdf.
// Unit compiled with VC7.0 /GL and linked /LTCG: the two constructors take
// `this` in ESI (and an actor in EAX), AActor::LocalToWorld takes `this` in
// EDI and the result in ESI, FBox::TransformBy takes everything on the stack.
// Class names other than UE2 core types are neutral (named after vtables).
// Status (try_ltcg.py, /O2 /Gy):
//   0x99cb0 UESBPatch::GetRenderBoundingBox  MATCH (root Driver_99cb0)
//   0x999d0 default constructor  6 bytes off: final fstp scheduled after pop edi
//   0x99b10 actor constructor    8 bytes off: lea/load order in the Location copy
//   0x99810 GetStreamData        159 bytes off: register choice and the
//           scheduling of the FPlane argument build
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;

extern "C" __declspec(dllimport) int __cdecl rand(void);
extern "C" __declspec(dllimport) double __cdecl floor(double);

inline void *operator new(unsigned int, void *Mem) { return Mem; }

inline INT appTrunc(FLOAT F) { return (INT)F; }
inline INT appFloor(FLOAT F) { return appTrunc((FLOAT)floor(F)); }
extern const FLOAT InvRandMax_41260; // 0x10c10a88, 1/32768
inline FLOAT appFrand() { return rand() * InvRandMax_41260; }

template<class T> inline T Clamp(T X, T Min, T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FArray
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
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
    BYTE IsValid;
    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax) : Min(InMin), Max(InMax), IsValid(0) {}
    const FVector &GetExtrema(INT i) const { return (&Min)[i]; }
    FBox TransformBy(const FMatrix &M) const;
    FBox &operator+=(const FVector &V);
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
    FMatrix LocalToWorld() const;
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C);
};
extern FGlobalMath GMath;

// Globals read through pointers by the base constructor.
extern FVector *GVector_ccacc4;
extern FVector *GVector_ccacc0;
extern DWORD GGlobal_c4da0c;

// ---------------------------------------------------------------------------
// Base class, vtable 0x10c0bae8 (constructor always inlined).
class UnnamedPrimitive_c0bae8
{
public:
    virtual void Slot0();
    DWORD ObjectFields[9];     // 0x04..0x27
    FVector Vector28;          // 0x28
    FVector Vector34;          // 0x34
    FPlane Plane40;            // 0x40

    UnnamedPrimitive_c0bae8()
        : Vector28(*GVector_ccacc4), Vector34(*GVector_ccacc0),
          Plane40(0, 0, 0, 0)
    {
    }
};

// Derived class, vtable 0x10c0b8a0. Constructors at 0x999d0 and 0x99b10.
class UnnamedPrimitive_c0b8a0 : public UnnamedPrimitive_c0bae8
{
public:
    DWORD Field50;
    AActor *Actor;             // 0x54
    FLOAT Field58;
    DWORD Pad5C[2];
    DWORD Field64;
    DWORD Pad68[2];
    FArray Array70, Array7C, Array88, Array94, ArrayA0, ArrayAC;
    DWORD PadB8[(0x100 - 0xb8) / 4];
    DWORD Field100, Field104;
    DWORD Pad108[3];
    FLOAT Field114, Field118;
    FArray Array11C;           // 0x11c
    FLOAT Field128, Field12C, Field130, Field134;
    DWORD Pad138;
    FVector Location;          // 0x13c
    FRotator Rotation;         // 0x148
    INT Field154;
    INT Field158;

    virtual void Slot0();
    UnnamedPrimitive_c0b8a0();
    UnnamedPrimitive_c0b8a0(AActor *InActor);
};

#pragma auto_inline(off)
UnnamedPrimitive_c0b8a0::UnnamedPrimitive_c0b8a0()
    : Field58(1.f), Field64(0)
{
    Field114 = appFrand() * 256.f;
    Field118 = appFrand() * 256.f;
    Field128 = -10.f;
    Field12C = 0.03333f;
    Field130 = 0.03333f;
    Field134 = 1.f;
    Field154 = 25;
    Field158 = 1;
}

UnnamedPrimitive_c0b8a0::UnnamedPrimitive_c0b8a0(AActor *InActor)
    : Field58(1.f), Field64(0)
{
    Field50 = GGlobal_c4da0c;
    Field100 = 1;
    Field104 = 1;
    Field114 = appFrand() * 256.f;
    Field118 = appFrand() * 256.f;
    Field128 = -10.f;
    Field12C = 0.03333f;
    Field130 = 0.03333f;
    Actor = InActor;
    Rotation = InActor->Rotation;
    Location = InActor->Location;
    Field134 = 1.f;
    Field154 = 25;
    Field158 = 1;
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// UESBPatch (vtable 0x10bf2c80), slot 26 at 0x99cb0.
class UESBPatch : public UnnamedPrimitive_c0b8a0
{
public:
    virtual FBox GetRenderBoundingBox(const AActor *Owner);
};

FBox UESBPatch::GetRenderBoundingBox(const AActor *Owner)
{
    return ((FBox *)&Field58)->TransformBy(Owner->LocalToWorld());
}

// ---------------------------------------------------------------------------
// Vertex stream for a patch (0x99810). Neutral names.
struct FPatchPoint
{
    FVector Position;
    FLOAT Alpha;
};

struct FPatchUV
{
    FLOAT U, V;
};

struct UnnamedPatchOwner
{
    BYTE Pad0[8];
    DOUBLE StartTime;          // 0x08
    DOUBLE EndTime;            // 0x10
    BYTE Pad18[0x24 - 0x18];
    FMatrix Matrix;            // 0x24
    BYTE Pad64[0x15c - 0x64];
    DWORD Flags;               // 0x15c
};

struct UnnamedPatchData
{
    UnnamedPatchOwner *Owner;
    UBOOL bHasUVs;
    FPatchPoint *Points;
    INT NumPoints;
    INT MaxPoints;
    FPatchUV *UVs;
};

struct FPatchVertex
{
    FVector Position;
    FColor Color;
    FVector Projected;
};

class UnnamedVertexStream_99810
{
public:
    virtual void Slot0();
    DWORD Pad4[2];
    UnnamedPatchData *Data;    // 0x0c
    virtual void GetStreamData(void *Dest);
};

void UnnamedVertexStream_99810::GetStreamData(void *Dest)
{
    for (INT i = 0; i < Data->NumPoints; i++)
    {
        FPatchPoint &P = Data->Points[i];
        FPatchVertex *V = (FPatchVertex *)Dest;
        V->Position = P.Position;
        FVector Proj = Data->Owner->Matrix.TransformFPlane(FPlane(P.Position.X, P.Position.Y, P.Position.Z, 1.f));
        if (!(Data->Owner->Flags & 1))
            Proj.Z = 1.f;
        V->Projected = Proj;
        UnnamedPatchOwner *O = Data->Owner;
        BYTE B = (BYTE)Clamp(appFloor(Clamp<FLOAT>(O->EndTime == 0.0 ? 1.0 : O->EndTime - O->StartTime, 0.f, 1.f) * P.Alpha * 255.f), 0, 255);
        V->Color = FColor(B, B, B, B);
        Dest = V + 1;
        if (Data->bHasUVs)
        {
            FPatchUV *UV = (FPatchUV *)Dest;
            UV->U = Data->UVs[i].U;
            UV->V = Data->UVs[i].V;
            Dest = UV + 1;
        }
    }
}

// ---------------------------------------------------------------------------
// Callees defined elsewhere in the LTCG program; bodies here only so the
// linker gives them their custom conventions. Not part of the unit.
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
FBox FBox::TransformBy(const FMatrix &M) const
{
    FBox NewBox(*GVector_ccacc4, *GVector_ccacc0);
    for (INT i = 0; i < 2; i++)
        for (INT j = 0; j < 2; j++)
            for (INT k = 0; k < 2; k++)
                NewBox += FVector(M.TransformFPlane(FPlane(FVector(GetExtrema(i).X, GetExtrema(j).Y, GetExtrema(k).Z), 1.f)));
    return NewBox;
}
FBox &FBox::operator+=(const FVector &V)
{
    if (IsValid)
    {
        if (V.X < Min.X) Min.X = V.X;
        if (V.Y < Min.Y) Min.Y = V.Y;
        if (V.Z < Min.Z) Min.Z = V.Z;
        if (V.X > Max.X) Max.X = V.X;
        if (V.Y > Max.Y) Max.Y = V.Y;
        if (V.Z > Max.Z) Max.Z = V.Z;
    }
    else
    {
        Min = Max = V;
        IsValid = 1;
    }
    return *this;
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_999d0(void *Mem)
{
    Escape(&GVector_ccacc4);
    Escape(&GVector_ccacc0);
    if (Mem)
        new(Mem) UnnamedPrimitive_c0b8a0;
}
void Driver_99b10(void *Mem, AActor *A)
{
    Escape(&GVector_ccacc4);
    Escape(&GVector_ccacc0);
    new(Mem) UnnamedPrimitive_c0b8a0(A);
}
void Driver_99cb0(void *Mem, const AActor *A, FBox *Out)
{
    UESBPatch *P = new(Mem) UESBPatch;
    *Out = P->GetRenderBoundingBox(A);
    FBox B = Out->TransformBy(A->LocalToWorld());
    Escape(&B);
}
void Driver_99810(void *Mem, void *Dest)
{
    UnnamedVertexStream_99810 *S = new(Mem) UnnamedVertexStream_99810;
    S->GetStreamData(Dest);
}
