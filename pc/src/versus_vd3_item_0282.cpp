// Work item 0282: Versus RVA 0x6cc60-0x6cf49. Direct3D 8 deferred render-state
// helpers. Built with VC7.0 /GL and linked /LTCG, so they take `this` in
// registers. The state object starts with a pointer to its owning render
// device; the device holds the IDirect3DDevice8 at +0x46a4. Vtable offsets
// match IDirect3DDevice8 (0xfc = SetTextureStageState: 11 = D3DTSS_TEXCOORDINDEX,
// 24 = D3DTSS_TEXTURETRANSFORMFLAGS; 0x14c = SetStreamSource).
// Class names are neutral: nothing identifies them.

typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned char BYTE;

struct FPlane
{
    FLOAT X, Y, Z, W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
};

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    __declspec(noinline) FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);   // retail 0x4fbc0
    __declspec(noinline) void operator*=(const FMatrix &Other);    // retail 0x4fc30
};
extern FMatrix FMatrix_Identity;    // retail 0x10cc9560

void appMemcpy(void *Dest, const void *Src, INT Count);

struct UnnamedD3DDevice_6cc60
{
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45(); virtual void Slot46(); virtual void Slot47();
    virtual void Slot48(); virtual void Slot49(); virtual void Slot50(); virtual void Slot51();
    virtual void Slot52(); virtual void Slot53(); virtual void Slot54(); virtual void Slot55();
    virtual void Slot56(); virtual void Slot57(); virtual void Slot58(); virtual void Slot59();
    virtual void Slot60(); virtual void Slot61(); virtual void Slot62();
    virtual long __stdcall SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value); // 0xfc
    virtual void Slot64(); virtual void Slot65(); virtual void Slot66(); virtual void Slot67();
    virtual void Slot68(); virtual void Slot69(); virtual void Slot70(); virtual void Slot71();
    virtual void Slot72(); virtual void Slot73(); virtual void Slot74(); virtual void Slot75();
    virtual void Slot76(); virtual void Slot77(); virtual void Slot78(); virtual void Slot79();
    virtual void Slot80(); virtual void Slot81(); virtual void Slot82();
    virtual long __stdcall SetStreamSource(DWORD Stream, void *Data, DWORD Stride); // 0x14c
};

struct UnnamedRenderDevice_6cc60
{
    char Pad0[0x41d0];
    DWORD NumTextureStages;                 // +0x41d0
    char Pad41d4[0x41f8 - 0x41d4];
    INT NumStreams;                         // +0x41f8
    char Pad41fc[0x46a4 - 0x41fc];
    UnnamedD3DDevice_6cc60 *Direct3DDevice; // +0x46a4
};

struct UnnamedStage_6cc60                   // 0x34 bytes
{
    DWORD TexCoordIndex;                    // +0x00
    DWORD Pad04[2];
    DWORD TextureTransformFlags;            // +0x0c
    DWORD Pad10[9];
};

struct UnnamedBinding_6cd00
{
    void *Buffer;
    DWORD Stride;
};

struct UnnamedState_6cc60
{
    UnnamedRenderDevice_6cc60 *RenderDevice;    // +0x000
    char Pad004[0x4d4 - 0x4];
    UnnamedBinding_6cd00 Other[16];             // +0x4d4
    char Pad554[0x958 - 0x554];
    UnnamedStage_6cc60 Stages[8];               // +0x958
    char PadAF8[0xdac - 0xaf8];
    UnnamedBinding_6cd00 Streams[16];           // +0xdac

    void ResetTexCoords();
    void UnbindBuffer(void *Buffer);
};

// RVA 0x6cc60
void UnnamedState_6cc60::ResetTexCoords()
{
    for (DWORD i = 0; i < RenderDevice->NumTextureStages; i++)
    {
        if (Stages[i].TexCoordIndex != i)
        {
            RenderDevice->Direct3DDevice->SetTextureStageState(i, 11, i);
            Stages[i].TexCoordIndex = i;
        }
        if (Stages[i].TextureTransformFlags != 0)
        {
            RenderDevice->Direct3DDevice->SetTextureStageState(i, 24, 0);
            Stages[i].TextureTransformFlags = 0;
        }
    }
}

// RVA 0x6cd00
void UnnamedState_6cc60::UnbindBuffer(void *Buffer)
{
    for (INT i = 0; i < (RenderDevice->NumStreams < 16 ? RenderDevice->NumStreams : 16); i++)
    {
        if (Streams[i].Buffer == Buffer)
        {
            Streams[i].Buffer = 0;
            Streams[i].Stride = 0;
            RenderDevice->Direct3DDevice->SetStreamSource(i, 0, 0);
        }
        if (Other[i].Buffer == Buffer)
        {
            Other[i].Buffer = 0;
            Other[i].Stride = 0;
        }
    }
}

// RVA 0x6ccd0
struct UnnamedTransforms_6ccd0
{
    char Pad0[0x208];
    FMatrix Matrices[11];                   // +0x208

    DWORD DirtyMask;                        // +0x4c8
    __declspec(noinline) void SetMatrix(INT Index, const FMatrix *M);
};

void UnnamedTransforms_6ccd0::SetMatrix(INT Index, const FMatrix *M)
{
    appMemcpy(&Matrices[Index], M, sizeof(FMatrix));
    DirtyMask |= 1 << Index;
}

// RVA 0x6cd70
struct UnnamedRecord_6cd70
{
    DWORD A, B, C, D;           // +0x00
    FMatrix Matrix;             // +0x10
    BYTE  E50, E51;             // +0x50
    DWORD E54;                  // +0x54
    BYTE  E58;                  // +0x58
    DWORD E5C, E60, E64, E68;   // +0x5c
    BYTE  E6C;                  // +0x6c
    DWORD E70, E74, E78, E7C, E80;
    __declspec(noinline) void Init();
};

void UnnamedRecord_6cd70::Init()
{
    A = 0; B = 0; C = 0; D = 0;
    Matrix = FMatrix_Identity;
    E50 = 0; E51 = 0;
    E54 = 0;
    E58 = 0;
    E5C = 1; E60 = 1;
    E64 = 0; E68 = 0;
    E6C = 0;
    E70 = 0; E74 = 0; E78 = 0; E7C = 0; E80 = 0;
}

// RVA 0x6ce90
struct UnnamedLight_6ce90                   // 0x7c bytes
{
    DWORD A;                    // +0x00
    DWORD B, C, D;              // +0x04 = 3
    FLOAT E;                    // +0x10 = -1000
    DWORD F, G;                 // +0x14 = 2
    DWORD H, I, J, K, L;        // +0x1c = 1
    DWORD M, N, O;              // +0x30 = 0
    FMatrix Matrix;             // +0x3c
};

struct UnnamedLightState_6ce90
{
    DWORD A, B;                 // +0x00
    BYTE  C;                    // +0x08
    DWORD D, E, F, G, H, I, J, K, L;    // +0x0c..+0x2c
    DWORD M;                    // +0x30
    UnnamedLight_6ce90 Lights[8];       // +0x34
    DWORD N, O;                 // +0x414
    UnnamedLightState_6ce90();
};

UnnamedLightState_6ce90::UnnamedLightState_6ce90()
{
    UnnamedLight_6ce90 *L = Lights;
    for (INT i = 8; i; i--, L++)
    {
        appMemcpy(&L->Matrix, &FMatrix_Identity, sizeof(FMatrix));
        L->B = 3; L->C = 3; L->D = 3;
        L->F = 2; L->G = 2;
        L->O = 0; L->M = 0; L->N = 0;
        L->E = -1000.f;
        L->A = 0;
        L->H = 1; L->I = 1; L->J = 1; L->K = 1; L->L = 1;
    }
    D = 1; E = 1; G = 2; I = 2; J = 1;
    A = 0; B = 0; C = 0;
    F = 0; H = 0; M = 0; K = 0;
    N = 0; O = 0;
}

// RVA 0x6cdd0
struct UnnamedTransform_6cdd0
{
    DWORD Dirty;            // +0x00
    DWORD Pad04[3];
    FMatrix Matrix;         // +0x10
    void Scale(FLOAT S);
};

void UnnamedTransform_6cdd0::Scale(FLOAT S)
{
    Dirty = 1;
    Matrix *= FMatrix(FPlane(S, 0, 0, 0), FPlane(0, S, 0, 0), FPlane(0, 0, 1, 0), FPlane(0, 0, 0, 1));
}

// Out-of-line FMatrix members from another unit (retail 0x4fbc0 and 0x4fc30),
// defined here so the link gives them their retail register conventions.
FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
{
    M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
    M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
    M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
    M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}

void FMatrix::operator*=(const FMatrix &Other)
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
    *this = Result;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_6cc60(UnnamedState_6cc60 *S) { S->ResetTexCoords(); }
void Driver_6cd00(UnnamedState_6cc60 *S, void *B) { S->UnbindBuffer(B); }
void Driver_6ccd0(UnnamedTransforms_6ccd0 *T, INT I, const FMatrix *M) { T->SetMatrix(I, M); }
void Driver_6cd70(UnnamedRecord_6cd70 *R) { Escape(&FMatrix_Identity); R->Init(); }
UnnamedLightState_6ce90 *Driver_6ce90(void *Mem) { Escape(&FMatrix_Identity); return new (Mem) UnnamedLightState_6ce90; }
void Driver_6cdd0(UnnamedTransform_6cdd0 *T, FLOAT S) { T->Scale(S); }
