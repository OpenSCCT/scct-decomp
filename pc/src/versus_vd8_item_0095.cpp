// Work item 0095: Versus RVA 0x14e750 (661 bytes).
// Projector polygon vertex generator (vtable at 0x10c033cc; class/method name guessed).

#include "versus_projector_primitives.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);

template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

template<class T> inline T Clamp(const T X, const T MinVal, const T MaxVal)
{
    return X < MinVal ? MinVal : X < MaxVal ? X : MaxVal;
}

inline INT appFloor(FLOAT F)
{
    return (INT)floor(F);
}

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
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
    inline FVector Vector() const;
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;

    FCoords operator/(const FRotator &Rot) const;
};

struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

inline FVector FRotator::Vector() const
{
    return (GMath.UnitCoords / *this).XAxis;
}

struct FMatrix
{
    FLOAT M[4][4];

    FPlane TransformFPlane(const FPlane &P) const;
    FVector TransformFVector(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f));
    }
};

struct FColor
{
    BYTE B, G, R, A;

    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}
};

enum EProjectorFlags
{
    PRF_Perspective         = 0x00000001,
    PRF_Gradient            = 0x00000004,
    PRF_ProjectOnBackfaces  = 0x00000010,
};

struct AProjector
{
    BYTE unk_00[0x80];
    FVector Location;           // +0x80
    BYTE unk_8c[0x54];
    FRotator Rotation;          // +0xe0
    BYTE unk_ec[0x374];
    INT MaxTraceDistance;       // +0x460
};

class FProjectorRenderInfo
{
public:
    AProjector *Projector;      // +0x00
    INT unk_04;                 // +0x04
    DOUBLE LastRenderTime;      // +0x08
    DOUBLE Expires;             // +0x10
    BYTE unk_18[0x0c];          // +0x18
    FMatrix Matrix;             // +0x24
    BYTE unk_64[0xf8];          // +0x64
    DWORD ProjectorFlags;       // +0x15c
};

struct FProjectorVertex
{
    FVector Position;           // +0x00
    FColor Color;               // +0x0c
    FVector TexCoord;           // +0x10
};

// The BSP draw list constructs this primitive for a clipped projector polygon.
class FProjectorPolygonStream : public FProjectorPrimitive
{
public:
    UBOOL bExtraUV;                     // +0x0c
    FProjectorRenderInfo *RenderInfo;   // +0x10
    FVector *Vertices;                  // +0x14
    FVector Normal;                     // +0x18

    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex);
    virtual void GetVertices(void *Dest);
};

// RVA 0x14e750
void FProjectorPolygonStream::GetVertices(void *Dest)
{
    FVector ProjectorDirection = RenderInfo->Projector->Rotation.Vector();
    FLOAT InvMaxTraceDistance = 1.0f / RenderInfo->Projector->MaxTraceDistance;

    for (INT VertexIndex = 0; VertexIndex < NumVertices; VertexIndex++)
    {
        FProjectorVertex *DestVertex = (FProjectorVertex *)Dest;
        DestVertex->Position = Vertices[VertexIndex];
        DestVertex->TexCoord = RenderInfo->Matrix.TransformFVector(Vertices[VertexIndex]);

        FLOAT Fade = RenderInfo->Expires == 0.0
            ? 1.0
            : Clamp<FLOAT>(RenderInfo->Expires - RenderInfo->LastRenderTime, 0.0f, 1.0f);

        FLOAT DirectionalAttenuation = 1.0f;
        if (!(RenderInfo->ProjectorFlags & PRF_ProjectOnBackfaces))
            DirectionalAttenuation = Max(Normal | -ProjectorDirection, 0.0f);

        FLOAT DistanceAttenuation = 1.0f;
        if (RenderInfo->ProjectorFlags & PRF_Gradient)
            DistanceAttenuation = Clamp(
                1.0f - ((Vertices[VertexIndex] - RenderInfo->Projector->Location)
                    | ProjectorDirection) * InvMaxTraceDistance,
                0.0f, 1.0f);

        BYTE Attenuation = (BYTE)Clamp(
            appFloor(DistanceAttenuation * DirectionalAttenuation * Fade * 255.0f),
            0, 255);
        DestVertex->Color = FColor(Attenuation, Attenuation, Attenuation, Attenuation);
        Dest = DestVertex + 1;

        if (bExtraUV)
        {
            FLOAT *ExtraUV = (FLOAT *)Dest;
            ExtraUV[0] = 0.0f;
            ExtraUV[1] = 0.0f;
            Dest = ExtraUV + 2;
        }
    }
}

void FProjectorPolygonStream::GetIndices(_WORD *Dest, _WORD BaseVertex)
{
    for (INT Vertex = 2; Vertex < NumVertices; ++Vertex) {
        *Dest++ = BaseVertex;
        *Dest++ = BaseVertex + Vertex - 1;
        *Dest++ = BaseVertex + Vertex;
    }
}

struct FStaticProjectorPoint {
    FVector Position;
    FLOAT Attenuation;
};

struct FProjectorUV {
    FLOAT U, V;
};

void FStaticProjectorPrimitive::GetVertices(void *Dest)
{
    for (INT i = 0; i < ProjectorInfo->Vertices.Num(); ++i) {
        FStaticProjectorPoint &Vertex = ProjectorInfo->Vertices(i);
        FProjectorVertex *Out = static_cast<FProjectorVertex *>(Dest);
        Out->Position = Vertex.Position;
        FVector Projected = ProjectorInfo->RenderInfo->Matrix.TransformFVector(Vertex.Position);
        if (!(ProjectorInfo->RenderInfo->ProjectorFlags & PRF_Perspective))
            Projected.Z = 1.f;
        Out->TexCoord = Projected;

        FProjectorRenderInfo *Info = ProjectorInfo->RenderInfo;
        FLOAT Fade = Clamp<FLOAT>(Info->Expires == 0.0 ? 1.0 : Info->Expires - Info->LastRenderTime, 0.f, 1.f);
        BYTE Intensity = (BYTE)Clamp<INT>((INT)floor(Fade * Vertex.Attenuation * 255.f), 0, 255);
        Out->Color = FColor(Intensity, Intensity, Intensity, Intensity);
        Dest = Out + 1;

        if (ProjectorInfo->BaseMaterial) {
            FProjectorUV *UV = static_cast<FProjectorUV *>(Dest);
            UV->U = ProjectorInfo->BaseUVs(i).U;
            UV->V = ProjectorInfo->BaseUVs(i).V;
            Dest = UV + 1;
        }
    }
}
