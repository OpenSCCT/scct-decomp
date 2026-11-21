// Work item 0157: polygon clipping against the view frustum (RVA 0xc7e00-0xc82b1).
// Names are neutral guesses from the code: a clipper owns a list of source
// vertices (0x20 bytes, indexed with negative indices) and a TArray of clip
// vertices (0x34 bytes); each clip vertex records the two vertices it was
// interpolated from and the plane (outcode bit) it was clipped against.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FPlane : FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
};

struct FVector2D { FLOAT U, V; };

struct FArray
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};

// Base vertex shared by source and clip vertices (0x20 bytes).
struct FClipVertBase
{
    FVector Point;      // 0x00
    FVector Screen;     // 0x0c
    FLOAT   W;          // 0x18
    BYTE    Outcode;    // 0x1c
};

struct FClipVert : FClipVertBase
{
    FLOAT U, V;         // 0x20
    INT   VertA, VertB; // 0x28
    BYTE  Plane;        // 0x30
};

struct UnnamedUVHolder_b0 { INT Pad; FVector2D *UVs; };
struct UnnamedMesh_100 { BYTE Pad[0xb0]; UnnamedUVHolder_b0 *UVData; };
struct UnnamedOwner_4 { BYTE Pad[0x100]; UnnamedMesh_100 *Mesh; };

struct FClipper
{
    UBOOL           HasUVs;     // 0x00
    UnnamedOwner_4 *Owner;      // 0x04
    FClipVertBase  *SourceVerts;// 0x08
    INT             Pad0c[2];   // 0x0c
    FArray          Verts;      // 0x14 (FClipVert)
    INT             Pad20[4];   // 0x20
    FLOAT           NearZ;      // 0x30
    FLOAT           FarZ;       // 0x34
};

extern FVector *GNearNormal;   // 0x10ccabf4
extern FVector *GFarNormal;    // 0x10ccacbc
extern FVector *GZeroNormal;   // 0x10ccacc0
FVector __fastcall SafeNormal(const FVector &V); // 0x10950d30 (guess)

// 0xc7e00
void __fastcall ComputeOutcode(FClipVertBase *V, FClipper *C)
{
    V->Outcode = 0;
    if (V->Screen.X < -0.001f)
        V->Outcode = 1;
    FLOAT Limit = V->Screen.Z + 0.001f;
    if (Limit < V->Screen.X)
        V->Outcode |= 2;
    if (V->Screen.Y < -0.001f)
        V->Outcode |= 4;
    if (Limit < V->Screen.Y)
        V->Outcode |= 8;
    if (V->Screen.Z < C->NearZ - 0.001f)
        V->Outcode |= 0x10;
    if (C->FarZ + 0.001f < V->Screen.Z)
        V->Outcode |= 0x20;
}

static inline FClipVertBase *GetVert(FClipper *C, INT Index)
{
    if (Index < 0)
        return C->SourceVerts - (Index + 1);
    return (FClipVert *)C->Verts.Data + Index;
}

// 0xc7e80 (not matching yet: retail materialises an FPlane temporary per switch case and has a
// smaller frame, 0x68 vs 0x90; body logic and instruction selection otherwise agree)
INT __stdcall AddClipVert(FClipper *C, INT A, INT B, BYTE Plane)
{
    INT Result = C->Verts.ArrayNum;
    FClipVert *New = (FClipVert *)C->Verts.Data + C->Verts.Add(1, sizeof(FClipVert));
    if (!New)
        return Result;
    New->VertA = A;
    New->VertB = B;
    New->Plane = Plane;

    FClipVertBase *VA = GetVert(C, A);
    FClipVertBase *VB = GetVert(C, B);
    FVector DPoint  = VB->Point - VA->Point;
    FVector DScreen = VB->Screen - VA->Screen;
    FLOAT   DW      = VB->W - VA->W;

    FPlane P;
    switch (Plane)
    {
    case 1:    P = FPlane(SafeNormal(FVector(-1.f, 0.f, 0.f)), 0.f); break;
    case 2:    P = FPlane(SafeNormal(FVector( 1.f, 0.f, -1.f)), 0.f); break;
    case 4:    P = FPlane(SafeNormal(FVector(0.f, -1.f, 0.f)), 0.f); break;
    case 8:    P = FPlane(SafeNormal(FVector(0.f,  1.f, -1.f)), 0.f); break;
    case 0x10: P = FPlane(*GNearNormal, -C->NearZ); break;
    case 0x20: P = FPlane(*GFarNormal, C->FarZ); break;
    default:   P = FPlane(*GZeroNormal, 0.f); break;
    }

    FLOAT DistA = P.PlaneDot(VA->Screen);
    FLOAT DistB = P.PlaneDot(VB->Screen);
    FLOAT T = (-1.f / (DistB - DistA)) * DistA;

    New->Point  = VA->Point + DPoint * T;
    New->Screen = VA->Screen + DScreen * T;
    New->W      = VA->W + T * DW;
    ComputeOutcode(New, C);

    if (C->HasUVs)
    {
        FLOAT UA, VA_, UB, VB_;
        if (A < 0)
        {
            FVector2D *UV = C->Owner->Mesh->UVData->UVs - (A + 1);
            UA = UV->U; VA_ = UV->V;
        }
        else
        {
            FClipVert *V = (FClipVert *)C->Verts.Data + A;
            UA = V->U; VA_ = V->V;
        }
        if (B < 0)
        {
            FVector2D *UV = C->Owner->Mesh->UVData->UVs - (B + 1);
            UB = UV->U; VB_ = UV->V;
        }
        else
        {
            FClipVert *V = (FClipVert *)C->Verts.Data + B;
            UB = V->U; VB_ = V->V;
        }
        New->U = UA + (UB - UA) * T;
        New->V = VA_ + (VB_ - VA_) * T;
    }
    return Result;
}
