// Item 0300: RVA 0x7bc90-0x7bf9a. Direct3D render-interface helpers.
// Names are neutral guesses (UnnamedRenderInterface etc.), following item 0295.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

struct UnnamedD3DDevice {
    virtual void __stdcall Slot00(); virtual void __stdcall Slot01(); virtual void __stdcall Slot02(); virtual void __stdcall Slot03();
    virtual void __stdcall Slot04(); virtual void __stdcall Slot05(); virtual void __stdcall Slot06(); virtual void __stdcall Slot07();
    virtual void __stdcall Slot08(); virtual void __stdcall Slot09(); virtual void __stdcall Slot10(); virtual void __stdcall Slot11();
    virtual void __stdcall Slot12(); virtual void __stdcall Slot13(); virtual void __stdcall Slot14(); virtual void __stdcall Slot15();
    virtual void __stdcall Slot16(); virtual void __stdcall Slot17(); virtual void __stdcall Slot18(); virtual void __stdcall Slot19();
    virtual void __stdcall Slot20(); virtual void __stdcall Slot21(); virtual void __stdcall Slot22(); virtual void __stdcall Slot23();
    virtual void __stdcall Slot24(); virtual void __stdcall Slot25(); virtual void __stdcall Slot26(); virtual void __stdcall Slot27();
    virtual void __stdcall Slot28(); virtual void __stdcall Slot29(); virtual void __stdcall Slot30(); virtual void __stdcall Slot31();
    virtual void __stdcall Slot32(); virtual void __stdcall Slot33(); virtual void __stdcall Slot34(); virtual void __stdcall Slot35();
    virtual void __stdcall Slot36(); virtual void __stdcall Slot37(); virtual void __stdcall Slot38(); virtual void __stdcall Slot39();
    virtual void __stdcall Slot40(); virtual void __stdcall Slot41(); virtual void __stdcall Slot42(); virtual void __stdcall Slot43();
    virtual void __stdcall Slot44(); virtual void __stdcall Slot45(); virtual void __stdcall Slot46(); virtual void __stdcall Slot47();
    virtual void __stdcall Slot48(); virtual void __stdcall Slot49(); virtual void __stdcall Slot50(); virtual void __stdcall Slot51();
    virtual void __stdcall Slot52(); virtual void __stdcall Slot53(); virtual void __stdcall Slot54(); virtual void __stdcall Slot55();
    virtual void __stdcall Slot56(); virtual void __stdcall Slot57(); virtual void __stdcall Slot58(); virtual void __stdcall Slot59();
    virtual void __stdcall Slot60(); virtual void __stdcall Slot61(); virtual void __stdcall Slot62();
    virtual long __stdcall SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value); // +0xfc
};

typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

struct UnnamedPixelShader;

// RenDev+0x30ea8: shader source generator state (neutral name).
struct UnnamedRenderDevice;
struct UnnamedShaderGenerator {
    UnnamedRenderDevice *RenDev;
    DWORD GenerateShader(DWORD Flags);
};

struct UnnamedRenderDevice {
    char Pad0[0x40b4];
    UnnamedPixelShader *FirstShader;    // +0x40b4
    char Pad1a[0x40dc - 0x40b8];
    INT UseHardware;                    // +0x40dc
    char Pad1[0x46a4 - 0x40e0];
    UnnamedD3DDevice *Direct3DDevice;   // +0x46a4
    char Pad2[0x30d20 - 0x46a8];
    INT StageDirty[4];                  // +0x30d20
    char Pad3[0x30ea8 - 0x30d30];
    UnnamedShaderGenerator Generator;   // +0x30ea8
    UnnamedPixelShader *Shaders[1];     // +0x30eac, indexed by shader flags
};

// RVA 0x6ae90 (not part of this item): builds shader code for Flags.
// Defined here with a stand-in body only so the LTCG linker gives it the
// retail register convention (Flags in EAX, Generator on the stack).
// Stand-in declarations for GenerateShader's body (not part of this item).
extern "C" __declspec(dllimport) int __cdecl sprintf(char *Dest, const char *Format, ...);
extern char *GShaderCursor;
inline void ShaderAppend(const char *Text) { while (*Text) *GShaderCursor++ = *Text++; }
extern char GShaderLine[];
extern char GShaderBuffer[];
extern const char GShaderFmt0[], GShaderFmt1[], GShaderFmt2[], GShaderFmt3[], GShaderFmt4[];
extern const char GShaderA[], GShaderB[], GShaderC[], GShaderD[], GShaderE[];
extern DWORD GShaderVersion;
long __stdcall UnnamedAssembleShader(char *Source, DWORD Usage, DWORD Version, DWORD *Handle);
// RVA 0x5f7e0 (not part of this item); stand-in body.
__declspec(noinline) void CreateShaderFromSource(char *Source, UnnamedRenderDevice *RenDev, DWORD Usage, DWORD Version, DWORD *Handle)
{
    if (UnnamedAssembleShader(Source, Usage, Version, Handle) < 0)
        RenDev->UseHardware = 0;
}
__declspec(noinline) DWORD UnnamedShaderGenerator::GenerateShader(DWORD Flags)
{
    ShaderAppend(GShaderA);
    ShaderAppend(GShaderB);
    if (Flags & 8) {
        sprintf(GShaderLine, GShaderFmt0, 0x1c);
        ShaderAppend(GShaderLine);
        ShaderAppend(GShaderC);
    } else {
        sprintf(GShaderLine, GShaderFmt1, 0x1d);
        ShaderAppend(GShaderLine);
        ShaderAppend(GShaderD);
    }
    INT Count = 0;
    if (Flags & 4) {
        sprintf(GShaderLine, GShaderFmt2, 0, 0xc);
        ShaderAppend(GShaderLine);
        Count = 1;
    }
    if (Flags & 2) {
        sprintf(GShaderLine, GShaderFmt3, Count, Flags);
        ShaderAppend(GShaderLine);
        Count++;
    }
    if (Flags & 1) {
        sprintf(GShaderLine, GShaderFmt3, Count);
        ShaderAppend(GShaderLine);
        Count++;
    }
    if (Flags & 0x10) {
        sprintf(GShaderLine, GShaderFmt4, Count, Count * 4 + 0xc);
        ShaderAppend(GShaderLine);
    }
    ShaderAppend(GShaderA);
    sprintf(GShaderLine, GShaderFmt0, 0x1e);
    ShaderAppend(GShaderLine);
    ShaderAppend(GShaderB);
    ShaderAppend(GShaderC);
    *GShaderCursor = 0;
    GShaderCursor = GShaderBuffer;
    DWORD Handle = (DWORD)-1;
    CreateShaderFromSource(GShaderBuffer, RenDev, RenDev->UseHardware ? 0 : 0x10, GShaderVersion, &Handle);
    return Handle;
}

void __stdcall UnnamedShaderBlockInit(void *Block); // RVA 0x6ac30

// 0x460-byte pixel shader object (neutral name).
struct UnnamedPixelShader {
    INT RefCount;                       // +0x00
    char Block[0x444];                  // +0x04
    INT Field448, Field44c, Field450;   // +0x448
    DWORD Code;                         // +0x454
    UnnamedRenderDevice *RenDev;        // +0x458
    UnnamedPixelShader *NextShader;     // +0x45c

    // RVA 0x6a790 (not part of this item).
    __declspec(noinline) UnnamedPixelShader(UnnamedRenderDevice *InRenDev, DWORD InCode)
    {
        UnnamedShaderBlockInit(Block);
        Field448 = Field44c = Field450 = 0;
        RefCount = 1;
        RenDev = InRenDev;
        Code = InCode;
        NextShader = InRenDev->FirstShader;
        InRenDev->FirstShader = this;
    }
};

struct UnnamedRenderInterface {
    char Pad0[0x108];
    UnnamedRenderDevice *RenDev;        // +0x108

    UnnamedPixelShader *GetPixelShader(INT Unused, DWORD Flags);
};

// RVA 0x7bc90 (LTCG: this in EBX)
UnnamedPixelShader *UnnamedRenderInterface::GetPixelShader(INT Unused, DWORD Flags)
{
    UnnamedPixelShader *Shader = RenDev->Shaders[Flags];
    if (!Shader) {
        Shader = new(L"new") UnnamedPixelShader(RenDev, RenDev->Generator.GenerateShader(Flags));
        RenDev->Shaders[Flags] = Shader;
    }
    return Shader;
}

// RVA 0x7bd30
void __stdcall ResetTextureStages(UnnamedRenderInterface *RI)
{
    UnnamedRenderDevice *RenDev;
    RenDev = RI->RenDev;
    if (RenDev->StageDirty[0]) {
        RenDev->Direct3DDevice->SetTextureStageState(0, 15, 0);
        RenDev->StageDirty[0] = 0;
    }
    RenDev = RI->RenDev;
    if (RenDev->StageDirty[1]) {
        RenDev->Direct3DDevice->SetTextureStageState(1, 15, 0);
        RenDev->StageDirty[1] = 0;
    }
    RenDev = RI->RenDev;
    if (RenDev->StageDirty[2]) {
        RenDev->Direct3DDevice->SetTextureStageState(2, 15, 0);
        RenDev->StageDirty[2] = 0;
    }
    RenDev = RI->RenDev;
    if (RenDev->StageDirty[3]) {
        RenDev->Direct3DDevice->SetTextureStageState(3, 15, 0);
        RenDev->StageDirty[3] = 0;
    }
}


// ---------------------------------------------------------------------------
// RVA 0x7bde0: projector matrix update (LTCG: this in ECX, source in EAX,
// owner on the stack). Unreal math types follow UnMath.h.

typedef unsigned char BYTE;
extern "C" double __cdecl acos(double);
extern "C" double __cdecl tan(double);
#pragma intrinsic(acos, tan)

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };
struct FPlane : public FVector {
    FLOAT W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};
struct D3DXMATRIX;
struct FMatrix {
    FLOAT M[4][4];
    static FMatrix Identity;
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FMatrix operator*(const FMatrix &Other) const;
    INT operator==(const FMatrix &Other) const;
};
struct FCoords {
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords operator/(const FRotator &R) const;     // RVA 0x411a0
    FCoords operator/(const FVector &Point) const;
    FMatrix Matrix() const;
};
extern const FCoords GMath_UnitCoords;              // GMath.UnitCoords

D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX *Out, const D3DXMATRIX *M1, const D3DXMATRIX *M2);
D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX *Out, FLOAT *Determinant, const D3DXMATRIX *M);

// Out-of-line UnMath helpers (RVAs 0x7c470, 0x50830, 0x4fbc0, 0x7b110, 0x74860;
// not part of this item). Retail did not inline them.
__declspec(noinline) FCoords FCoords::operator/(const FVector &Point) const
{
    FCoords Result;
    Result.Origin.X = Origin.X + Point.X;
    Result.Origin.Y = Origin.Y + Point.Y;
    Result.Origin.Z = Origin.Z + Point.Z;
    Result.XAxis = XAxis;
    Result.YAxis = YAxis;
    Result.ZAxis = ZAxis;
    return Result;
}
__declspec(noinline) FMatrix FCoords::Matrix() const
{
    FMatrix R;
    R.M[0][0] = XAxis.X; R.M[0][1] = YAxis.X; R.M[0][2] = ZAxis.X; R.M[0][3] = 0.f;
    R.M[1][0] = XAxis.Y; R.M[1][1] = YAxis.Y; R.M[1][2] = ZAxis.Y; R.M[1][3] = 0.f;
    R.M[2][0] = XAxis.Z; R.M[2][1] = YAxis.Z; R.M[2][2] = ZAxis.Z; R.M[2][3] = 0.f;
    R.M[3][0] = -(Origin.X * XAxis.X + Origin.Y * XAxis.Y + Origin.Z * XAxis.Z);
    R.M[3][1] = -(Origin.X * YAxis.X + Origin.Y * YAxis.Y + Origin.Z * YAxis.Z);
    R.M[3][2] = -(Origin.X * ZAxis.X + Origin.Y * ZAxis.Y + Origin.Z * ZAxis.Z);
    R.M[3][3] = 1.f;
    return R;
}
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
{
    M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
    M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
    M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
    M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];
    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];
    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];
    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    return Result;
}
__declspec(noinline) INT FMatrix::operator==(const FMatrix &Other) const
{
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            if (M[i][j] != Other.M[i][j])
                return 0;
    return 1;
}

// Neutral names: the actor-like object the projector follows.
struct UnnamedProjectedActor {
    char Pad0[0x80];
    FVector Location;                   // +0x80
    char Pad1[0xe0 - 0x8c];
    FRotator Rotation;                  // +0xe0
    char Pad2[0x2d7 - 0xec];
    BYTE Angle;                         // +0x2d7
};
struct UnnamedProjectorSource {
    UnnamedProjectedActor *Actor;       // +0x00
    char Pad0[0x30 - 4];
    FLOAT Range;                        // +0x30
};
struct UnnamedTransformState2 {
    char Pad0[0x78];
    FMatrix View;                       // +0x78
};
struct UnnamedRenderInterface2 {
    char Pad0[0x7c];
    struct UnnamedProjector {
        DWORD Field0;
        UnnamedProjectorSource *Source; // +0x04
        FMatrix Matrix;                 // +0x08
        void SetSource(UnnamedProjectorSource *NewSource, UnnamedRenderInterface2 *Owner);
    } Projector;                        // +0x7c
    char Pad1[0x2af10 - 0x7c - 0x48];
    UnnamedTransformState2 *State;      // +0x2af10
};

// RVA 0x7bde0
void UnnamedRenderInterface2::UnnamedProjector::SetSource(UnnamedProjectorSource *NewSource, UnnamedRenderInterface2 *Owner)
{
    if (Source == NewSource)
        return;
    Source = NewSource;
    if (!NewSource)
        return;

    FCoords Coords = GMath_UnitCoords / NewSource->Actor->Rotation / NewSource->Actor->Location;
    FMatrix ViewMatrix = Coords.Matrix();

    FLOAT C = 1.f - Source->Actor->Angle / 256.f;
    FLOAT T = 0.5f / (FLOAT)tan(acos(C * C));
    FMatrix Projection(
        FPlane(T, 0.f, 0.f, 0.f),
        FPlane(0.f, -T, 0.f, 0.f),
        FPlane(0.5f, 0.5f, 1.f, 1.f / Source->Range),
        FPlane(0.f, 0.f, 0.f, 0.f));
    FMatrix Result = ViewMatrix * Projection;

    FMatrix Inverse;
    D3DXMatrixInverse((D3DXMATRIX *)&Inverse, 0, (D3DXMATRIX *)&Owner->State->View);
    if (!(Result == FMatrix::Identity))
        D3DXMatrixMultiply((D3DXMATRIX *)&Matrix, (D3DXMATRIX *)&Inverse, (D3DXMATRIX *)&Result);
    else
        Matrix = Inverse;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_7bc90(UnnamedRenderInterface *RI, INT A, DWORD Flags)
{
    Escape(&GMalloc);
    Escape(&GShaderCursor);
    Escape(RI->GetPixelShader(A, Flags));
}
void Driver_7bde0(UnnamedRenderInterface2 *RI, UnnamedProjectorSource *NewSource)
{
    Escape((void *)&GMath_UnitCoords);
    Escape(&FMatrix::Identity);
    RI->Projector.SetSource(NewSource, RI);
}
