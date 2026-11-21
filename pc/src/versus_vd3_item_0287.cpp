// Work item 0287: Versus RVA 0x74740-0x7485f.
// FMatrix::Coords and two Direct3D 8 render-device helpers. All were built
// with VC7.0 /GL and linked /LTCG, so they take `this` and arguments in
// registers. The render device holds the IDirect3DDevice8 at +0x46a4 (see
// item 0282); vtable 0xfc is IDirect3DDevice8::SetTextureStageState.
// Device and state class names are neutral: nothing identifies them.

typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
};

struct FMatrix
{
    FLOAT M[4][4];
    FCoords Coords();
};

// RVA 0x74740
FCoords FMatrix::Coords()
{
    FCoords Result;
    Result.XAxis = FVector(M[0][0], M[1][0], M[2][0]);
    Result.YAxis = FVector(M[0][1], M[1][1], M[2][1]);
    Result.ZAxis = FVector(M[0][2], M[1][2], M[2][2]);
    Result.Origin = FVector(M[3][0], M[3][1], M[3][2]);
    return Result;
}

struct UnnamedD3DDevice_747e0
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
};

struct UnnamedRenderDevice_747e0
{
    char Pad0[0x46a4];
    UnnamedD3DDevice_747e0 *Direct3DDevice;     // +0x46a4
    char Pad46a8[0x30d20 - 0x46a8];
    DWORD StageState15[8];                      // +0x30d20, cached stage state 15

    void SetStageState15(DWORD Stage, DWORD Value);
};

// RVA 0x747e0
__declspec(noinline) void UnnamedRenderDevice_747e0::SetStageState15(DWORD Stage, DWORD Value)
{
    if (StageState15[Stage] != Value)
    {
        Direct3DDevice->SetTextureStageState(Stage, 15, Value);
        StageState15[Stage] = Value;
    }
}

struct UnnamedState_74840
{
    DWORD Pad00[5];
    DWORD A;        // +0x14
    DWORD B;        // +0x18
    DWORD Pad1c[2];
    DWORD C;        // +0x24
    DWORD D;        // +0x28

    void Reset(DWORD Unused1, DWORD Unused2);
};

// RVA 0x74840
__declspec(noinline) void UnnamedState_74840::Reset(DWORD Unused1, DWORD Unused2)
{
    D = 0;
    B = 2;
    C = 1;
    A = 3;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_74740(FMatrix *M, FCoords *Out) { *Out = M->Coords(); }
void Driver_747e0(UnnamedRenderDevice_747e0 *D, DWORD S, DWORD V) { D->SetStageState15(S, V); }
void Driver_74840(UnnamedState_74840 *S, DWORD A, DWORD B) { S->Reset(A, B); }
