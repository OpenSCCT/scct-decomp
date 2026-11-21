// Work item 0071: Versus RVA 0x140910-0x140e74.
// Engine/Core inline helpers (VC7.0 /GL + /LTCG):
// - 0x140910: New<DWORD>(FMemStack&, INT, INT)
// - 0x140950: NewZeroed<DWORD>(FMemStack&, INT, INT)
// - 0x1409c0: FConvexVolume::Set(const FMatrix&) (neutral method name)
// - 0x140d40: FPerspectiveMatrix::FPerspectiveMatrix(FLOAT, FLOAT, FLOAT, FLOAT, FLOAT)
// - 0x140e00: FVector::SafeNormalInPlace() (neutral method name)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl tan(double);
extern "C" void * __cdecl memset(void *Dest, int Val, unsigned int Count);
#pragma intrinsic(sqrt, tan, memset)

inline FLOAT appSqrt(FLOAT A) { return (FLOAT)sqrt(A); }
inline FLOAT appTan(FLOAT A) { return (FLOAT)tan(A); }
inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }

template <class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// ---- FMemStack (from pc/src/versus_vd3_item_0234.cpp) ----

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[];

inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }

class FMemStack
{
public:
    struct FTaggedMemory
    {
        FTaggedMemory *Next;
        INT DataSize;
        BYTE Data[1];
    };

    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;

    static FTaggedMemory *UnusedChunks;

    __declspec(noinline) BYTE *AllocateNewChunk(INT MinSize);

    inline BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

// Retail 0x577c0, reproduced so LTCG uses its custom calling convention (edi=this, eax=MinSize).
BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

// 0x140910: New<T>(FMemStack&, INT, INT) for 4-byte element type (LTCG: eax=&Mem, ebx=Align, stack=Count).
template <class T>
__declspec(noinline) T *New(FMemStack &Mem, INT Count, INT Align)
{
    return (T *)Mem.PushBytes(Count * sizeof(T), Align);
}

// 0x140950: NewZeroed<T>(FMemStack&, INT, INT) for 4-byte element type (LTCG: eax=&Mem, ecx=Count, stack=Align).
// Near miss: retail inlines UE2's inline-asm appMemzero (UnVcWin32.h); kept as C memset under no-asm rule.
template <class T>
__declspec(noinline) T *NewZeroed(FMemStack &Mem, INT Count, INT Align)
{
    BYTE *Result = Mem.PushBytes(Count * sizeof(T), Align);
    appMemzero(Result, Count * sizeof(T));
    return (T *)Result;
}

// ---- Core Math (from pc/src/versus_vd3_item_0206.cpp and versus_vd4_item_0202.cpp) ----

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator/(FLOAT Scale) const { FLOAT RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    __declspec(noinline) FVector SafeNormalInPlace();
};

__declspec(dllimport) extern const FVector GZeroVector;
__declspec(dllimport) extern const FVector GBoxStartMin;

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FBox
{
    FVector Min, Max;
    __declspec(noinline) FBox(const FVector *Points, INT Count);
    FVector GetCenter() const { return FVector((Min + Max) * 0.5f); }
    __declspec(noinline) FBox &operator+=(const FVector &Other);
};

struct FSphere : public FPlane
{
    FSphere() {}
    FSphere(const FVector &V, FLOAT InW) : FPlane(V, InW) {}
    __declspec(noinline) FSphere(const FVector *Pts, INT Count);
};

inline FLOAT FDistSquared(const FVector &V1, const FVector &V2)
{
    return (V1 - V2).SizeSquared();
}

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

FBox::FBox(const FVector *Points, INT Count)
    : Min(GBoxStartMin), Max(GZeroVector)
{
    for (INT i = 0; i < Count; i++)
        *this += Points[i];
}

// Retail 0x50ac0, reproduced so LTCG uses its custom calling convention (edi=this, eax=Count, stack=Pts).
FSphere::FSphere(const FVector *Pts, INT Count)
    : FPlane(0, 0, 0, 0)
{
    if (Count)
    {
        FBox Box(Pts, Count);
        *this = FSphere(Box.GetCenter(), 0);
        for (INT i = 0; i < Count; i++)
        {
            FLOAT Dist = FDistSquared(*this, Pts[i]);
            if (Dist > W)
                W = Dist;
        }
        W = (FLOAT)sqrt(W) * 1.001f;
    }
}

struct FMatrix
{
    FLOAT M[4][4];
    static FMatrix Identity;
    FMatrix() {}
    __declspec(noinline) FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FLOAT Determinant() const;
    __declspec(noinline) FMatrix Inverse() const;
    FPlane TransformFPlane(const FPlane &P) const;
};

// Retail 0x4fbc0, reproduced so LTCG uses its custom calling convention (eax=this, edx=InZ, ecx=InW, stack=InX,InY).
FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
{
    M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
    M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
    M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
    M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}

// Retail 0x53af0 stub body so LTCG uses its custom calling convention (eax=this, ebx=hidden return).
FMatrix FMatrix::Inverse() const
{
    FMatrix Result;
    FLOAT Det = Determinant();
    if (Det == 0.0f)
        return Identity;
    FLOAT RDet = 1.0f / Det;
    Result.M[0][0] = RDet * (M[3][3] * M[2][2] - M[2][3] * M[3][2]);
    return Result;
}

// ---- 0x1409c0: FConvexVolume::Set (neutral method name) ----
// Original used a function-local static FPlane[8] initialized on first call (guard at 0x10d50ea0,
// array at 0x10d50e20); declared extern so try_ltcg can bind the writable data addresses.

extern DWORD FConvexVolume_Set_Guard;
extern FPlane FConvexVolume_Set_ClipVertices[8];

struct FConvexVolume
{
    FVector BoundingVertices[8];
    FPlane BoundingPlanes[6];
    FSphere BoundingSphere;

    __declspec(noinline) void Set(const FMatrix &Matrix);
};

void FConvexVolume::Set(const FMatrix &Matrix)
{
    if (!(FConvexVolume_Set_Guard & 1))
    {
        FConvexVolume_Set_Guard |= 1;
        FConvexVolume_Set_ClipVertices[0].X = 1.0f;  FConvexVolume_Set_ClipVertices[0].Y = 1.0f;  FConvexVolume_Set_ClipVertices[0].Z = 0.0f; FConvexVolume_Set_ClipVertices[0].W = 1.0f;
        FConvexVolume_Set_ClipVertices[1].X = 1.0f;  FConvexVolume_Set_ClipVertices[1].Y = 1.0f;  FConvexVolume_Set_ClipVertices[1].Z = 1.0f; FConvexVolume_Set_ClipVertices[1].W = 1.0f;
        FConvexVolume_Set_ClipVertices[2].X = -1.0f; FConvexVolume_Set_ClipVertices[2].Y = 1.0f;  FConvexVolume_Set_ClipVertices[2].Z = 0.0f; FConvexVolume_Set_ClipVertices[2].W = 1.0f;
        FConvexVolume_Set_ClipVertices[3].X = -1.0f; FConvexVolume_Set_ClipVertices[3].Y = 1.0f;  FConvexVolume_Set_ClipVertices[3].Z = 1.0f; FConvexVolume_Set_ClipVertices[3].W = 1.0f;
        FConvexVolume_Set_ClipVertices[4].X = -1.0f; FConvexVolume_Set_ClipVertices[4].Y = -1.0f; FConvexVolume_Set_ClipVertices[4].Z = 0.0f; FConvexVolume_Set_ClipVertices[4].W = 1.0f;
        FConvexVolume_Set_ClipVertices[5].X = -1.0f; FConvexVolume_Set_ClipVertices[5].Y = -1.0f; FConvexVolume_Set_ClipVertices[5].Z = 1.0f; FConvexVolume_Set_ClipVertices[5].W = 1.0f;
        FConvexVolume_Set_ClipVertices[6].X = 1.0f;  FConvexVolume_Set_ClipVertices[6].Y = -1.0f; FConvexVolume_Set_ClipVertices[6].Z = 0.0f; FConvexVolume_Set_ClipVertices[6].W = 1.0f;
        FConvexVolume_Set_ClipVertices[7].X = 1.0f;  FConvexVolume_Set_ClipVertices[7].Y = -1.0f; FConvexVolume_Set_ClipVertices[7].Z = 1.0f; FConvexVolume_Set_ClipVertices[7].W = 1.0f;
    }

    FMatrix InvMatrix = Matrix;
    InvMatrix = InvMatrix.Inverse();

    for (INT VertexIndex = 0; VertexIndex < 8; VertexIndex++)
    {
        FPlane Projected = InvMatrix.TransformFPlane(FConvexVolume_Set_ClipVertices[VertexIndex]);
        BoundingVertices[VertexIndex].X = Projected.X / Projected.W;
        BoundingVertices[VertexIndex].Y = Projected.Y / Projected.W;
        BoundingVertices[VertexIndex].Z = Projected.Z / Projected.W;
    }

    BoundingSphere = FSphere(BoundingVertices, 8);

    BoundingPlanes[0].X = Matrix.M[0][3] - Matrix.M[0][0];
    BoundingPlanes[0].Y = Matrix.M[1][3] - Matrix.M[1][0];
    BoundingPlanes[0].Z = Matrix.M[2][3] - Matrix.M[2][0];
    BoundingPlanes[0].W = -(Matrix.M[3][3] - Matrix.M[3][0]);

    BoundingPlanes[1].X = Matrix.M[0][3] + Matrix.M[0][0];
    BoundingPlanes[1].Y = Matrix.M[1][3] + Matrix.M[1][0];
    BoundingPlanes[1].Z = Matrix.M[2][3] + Matrix.M[2][0];
    BoundingPlanes[1].W = -(Matrix.M[3][0] + Matrix.M[3][3]);

    BoundingPlanes[2].X = Matrix.M[0][3] + Matrix.M[0][1];
    BoundingPlanes[2].Y = Matrix.M[1][3] + Matrix.M[1][1];
    BoundingPlanes[2].Z = Matrix.M[2][3] + Matrix.M[2][1];
    BoundingPlanes[2].W = -(Matrix.M[3][1] + Matrix.M[3][3]);

    BoundingPlanes[3].X = Matrix.M[0][3] - Matrix.M[0][1];
    BoundingPlanes[3].Y = Matrix.M[1][3] - Matrix.M[1][1];
    BoundingPlanes[3].Z = Matrix.M[2][3] - Matrix.M[2][1];
    BoundingPlanes[3].W = -(Matrix.M[3][3] - Matrix.M[3][1]);

    BoundingPlanes[4].X = Matrix.M[0][3] - Matrix.M[0][2];
    BoundingPlanes[4].Y = Matrix.M[1][3] - Matrix.M[1][2];
    BoundingPlanes[4].Z = Matrix.M[2][3] - Matrix.M[2][2];
    BoundingPlanes[4].W = -(Matrix.M[3][3] - Matrix.M[3][2]);

    BoundingPlanes[5].X = Matrix.M[0][2];
    BoundingPlanes[5].Y = Matrix.M[1][2];
    BoundingPlanes[5].Z = Matrix.M[2][2];
    BoundingPlanes[5].W = -Matrix.M[3][2];

    for (INT PlaneIndex = 0; PlaneIndex < 6; PlaneIndex++)
    {
        FPlane &Plane = BoundingPlanes[PlaneIndex];
        FLOAT InvLength = 1.0f / Plane.Size();
        Plane.X *= InvLength;
        Plane.Y *= InvLength;
        Plane.Z *= InvLength;
        Plane.W *= InvLength;
    }
}

// ---- 0x140d40: FPerspectiveMatrix::FPerspectiveMatrix ----

struct FPerspectiveMatrix : public FMatrix
{
    __declspec(noinline) FPerspectiveMatrix(FLOAT HalfFOV, FLOAT Width, FLOAT Height, FLOAT MinZ, FLOAT MaxZ);
};

FPerspectiveMatrix::FPerspectiveMatrix(FLOAT HalfFOV, FLOAT Width, FLOAT Height, FLOAT MinZ, FLOAT MaxZ)
    : FMatrix(
        FPlane(1.0f / appTan(HalfFOV), 0.0f, 0.0f, 0.0f),
        FPlane(0.0f, Width / appTan(HalfFOV) / Height, 0.0f, 0.0f),
        FPlane(0.0f, 0.0f, MaxZ / (MaxZ - MinZ), 1.0f),
        FPlane(0.0f, 0.0f, -MinZ * (MaxZ / (MaxZ - MinZ)), 0.0f))
{
}

// ---- 0x140e00: FVector::SafeNormalInPlace (neutral method name) ----

FVector FVector::SafeNormalInPlace()
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum >= 1.e-8f)
    {
        FLOAT Scale = 1.0f / appSqrt(SquareSum);
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        return *this;
    }
    return GZeroVector;
}

// ---- Scaffolding for the LTCG link, not part of the unit ----

void Escape(void *);
void UseMatrix(const FMatrix &M);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

DWORD *Driver_140910(FMemStack *Mem, INT Count, INT Align)
{
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    DWORD *A = New<DWORD>(*Mem, Count, Align);
    DWORD *B = New<DWORD>(*Mem, Count + 1, Align);
    Escape(A);
    return B;
}

DWORD *Driver_140950(FMemStack *Mem, INT Count, INT Align)
{
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    DWORD *A = NewZeroed<DWORD>(*Mem, Count, Align);
    DWORD *B = NewZeroed<DWORD>(*Mem, Count + 1, Align);
    Escape(A);
    return B;
}

void Driver_1409c0(FConvexVolume *V, const FMatrix *M)
{
    Escape(&FConvexVolume_Set_Guard);
    Escape(FConvexVolume_Set_ClipVertices);
    Escape(&FMatrix::Identity);
    V->Set(*M);
    V[1].Set(M[1]);
}

void Driver_140d40(FMatrix *Out, FLOAT HalfFOV, FLOAT Width, FLOAT Height, FLOAT MinZ, FLOAT MaxZ, const FPlane *Planes)
{
    FMatrix M1(Planes[0], Planes[1], Planes[2], Planes[3]);
    UseMatrix(M1);
    Out[0] = FPerspectiveMatrix(HalfFOV, Width, Height, MinZ, MaxZ);
    Out[1] = FPerspectiveMatrix(HalfFOV, Width, Height, MinZ, MaxZ);
}

void Driver_140e00(FVector *V, FVector *Out)
{
    Out[0] = V[0].SafeNormalInPlace();
    Out[1] = V[1].SafeNormalInPlace();
}
