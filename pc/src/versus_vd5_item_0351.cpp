// Work item 0351: FCanvasUtil members, RVA 0x111f50-0x112415 (LTCG unit).
// Layout follows w3_item_0207 (FCanvasUtil: type 0x04, material 0x08,
// primitive count 0x0c, render interface 0x10, projection 0x54, vertices 0x94).
// Retail passes `this` in EAX (DrawTile variants) or ESI (the batch helpers).
// Names of the render-interface slots and of the 0x112180/0x112240/0x1122a0
// members are neutral guesses.
// try_ltcg.py /O2 /Gy with all four Driver_* roots: DrawTile (0x111f50) and
// FlushBatch (0x112240) MATCH; BeginBatch (0x112180) and DrawBlendTile
// (0x1122a0) are near misses (FPlane temp / zero-register allocation, and the
// register LTCG picks for the 0x112ab0 Points argument).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}
};
struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
};
struct FMatrix { FLOAT M[4][4]; };
extern FMatrix FMatrix_Identity;            // 0x10cc9560
extern FVector *GUnnamedVector_ccacc0;      // 0x10ccacc0, neutral name

class UMaterial
{
public:
    virtual void Pad00(); virtual void Pad04(); virtual void Pad08(); virtual void Pad0c();
    virtual void Pad10(); virtual void Pad14(); virtual void Pad18(); virtual void Pad1c();
    virtual void Pad20(); virtual void Pad24(); virtual void Pad28(); virtual void Pad2c();
    virtual void Pad30(); virtual void Pad34(); virtual void Pad38(); virtual void Pad3c();
    virtual void Pad40(); virtual void Pad44(); virtual void Pad48(); virtual void Pad4c();
    virtual void Pad50(); virtual void Pad54(); virtual void Pad58(); virtual void Pad5c();
    virtual void Pad60(); virtual void Pad64();
    virtual INT MaterialUSize();
    virtual INT MaterialVSize();
};

// Neutral: the static blend material built by 0x1122a0 (UFinalBlend-like).
class UnnamedBlend_1122a0 : public UMaterial
{
public:
    BYTE Pad[0x48];
    UMaterial *Material;        // 0x4c
    BYTE FrameBufferBlending;   // 0x50
    BYTE Pad51[3];
    DWORD ZWrite : 1;           // 0x54 bit 0
    DWORD TwoSided : 1;         // bit 1
    DWORD ZTest : 1;            // bit 2
    DWORD AlphaTest : 1;        // bit 3
    BYTE AlphaRef;              // 0x58
};
class UClass;
class UObject;
class FOutputDevice;
UObject *StaticConstructObject(UClass *Class, UObject *Outer, INT Name, DWORD Flags,
                               UObject *Template, FOutputDevice *Error, UObject *A, UObject *B);
extern UClass UnnamedBlend_1122a0_Class;    // 0x10cc4470
extern UObject *GTransientPackage;          // 0x10c925b4
extern FOutputDevice *GError;               // 0x10c71aa8
extern void (*GUnnamedHook_cc4574)(UObject *);  // 0x10cc4574
extern UnnamedBlend_1122a0 *FCanvasUtil_BlendMaterial;  // 0x10c9231c, was a local static

struct FArray
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};
struct FUnnamedRoots { BYTE Pad[0x28]; FArray Roots; };
extern FUnnamedRoots *GUnnamedRoots_c92540;  // 0x10c92540

class FRenderInterface;
class FCanvasUtil;
class FRenderInterfaceSub
{
public:
    virtual void Pad00(); virtual void Pad04(); virtual void Pad08(); virtual void Pad0c();
    virtual void Pad10();
    virtual void SetLight(FRenderInterface *RI, INT A, INT B, INT C, INT D, FPlane Color);  // 0x14
    virtual void SetTransform(FRenderInterface *RI, INT Type, const FMatrix &M);         // 0x18
    virtual void Pad1c();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Type, FCanvasUtil *Stream);   // 0x20
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *M, INT A);                 // 0x24
};
class FRenderInterface
{
public:
    virtual void PushState();                                   // 0x00
    virtual void PopState();                                    // 0x04
    virtual void Pad08(); virtual void Pad0c();
    virtual void Pad10(); virtual void Pad14(); virtual void Pad18();
    virtual void SetCullMode(INT Mode);                         // 0x1c
    virtual void Pad20();
    virtual void Clear(UBOOL A, UBOOL B, UBOOL C, FColor Color);    // 0x24
    virtual void Pad28(); virtual void Pad2c();
    virtual void Pad30(); virtual void Pad34(); virtual void Pad38(); virtual void Pad3c();
    virtual void Pad40(); virtual void Pad44(); virtual void Pad48(); virtual void Pad4c();
    virtual void Pad50(); virtual void Pad54(); virtual void Pad58();
    virtual void SetZBias(INT A, INT B);                        // 0x5c
    virtual void Pad60();
    virtual void DrawPrimitive(INT Type, INT BaseIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // 0x64
    BYTE Pad[0x10];
    FRenderInterfaceSub *Sub;   // 0x14
};

struct FCanvasVertex
{
    FLOAT X, Y, Z;
    FColor Color;
    FLOAT U, V;
};
struct FCanvasVertexArray
{
    FCanvasVertex *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};

class FCanvasUtil
{
public:
    void *VfTable;
    INT CurrentType;              // 0x04
    UMaterial *CurrentMaterial;   // 0x08
    INT NumPrimitives;            // 0x0c
    FRenderInterface *RI;         // 0x10
    BYTE Pad14[0x40];
    FMatrix Projection;           // 0x54
    FCanvasVertexArray Vertices;  // 0x94

    void PutVertex(FLOAT X, FLOAT Y, FLOAT Z, FColor C, FLOAT U, FLOAT V)
    {
        FCanvasVertex *P = &Vertices.Data[Vertices.Add(1, sizeof(FCanvasVertex))];
        if (P) { P->X = X; P->Y = Y; P->Z = Z; P->Color = C; P->U = U; P->V = V; }
    }
    void PutVertex(const FVector &P, FColor C, FLOAT U, FLOAT V)
    {
        FCanvasVertex *Vtx = &Vertices.Data[Vertices.Add(1, sizeof(FCanvasVertex))];
        if (Vtx) { *(FVector *)&Vtx->X = P; Vtx->Color = C; Vtx->U = U; Vtx->V = V; }
    }
    void Flush();                     // 0x111c60
    void BeginBatch();                // 0x112180
    void FlushBatch();                // 0x112240
    void DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
                  FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *Material, FColor Color);  // 0x111f50
    void DrawBlendTile(const FVector *Points, FLOAT A2, FLOAT A3, FLOAT A4, FLOAT A5, UMaterial *Material,
                       FColor A7, FColor A8, FColor A9, FColor A10, BYTE Blending,
                       UBOOL ZWrite, UBOOL ZTest);   // 0x1122a0
    void UnnamedDraw_112ab0(const FVector *Points, FLOAT A2, FLOAT A3, FLOAT A4, FLOAT A5,
                            FColor A7, FColor A8, FColor A9, FColor A10);
};

void FCanvasUtil::DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
                           FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *Material, FColor Color)
{
    if (CurrentType != 0 || CurrentMaterial != Material || Vertices.ArrayNum + 6 > 0x552)
    {
        Flush();
        CurrentType = 0;
        CurrentMaterial = Material;
    }
    INT USize, VSize;
    if (Material) { USize = Material->MaterialUSize(); VSize = Material->MaterialVSize(); }
    else { USize = 1; VSize = 1; }
    FLOAT UScale = 1.f / USize, VScale = 1.f / VSize;
    PutVertex(X1, Y1, Z, Color, U1 * UScale, V1 * VScale);
    PutVertex(X2, Y1, Z, Color, U2 * UScale, V1 * VScale);
    PutVertex(X2, Y2, Z, Color, U2 * UScale, V2 * VScale);
    PutVertex(X1, Y1, Z, Color, U1 * UScale, V1 * VScale);
    PutVertex(X2, Y2, Z, Color, U2 * UScale, V2 * VScale);
    PutVertex(X1, Y2, Z, Color, U1 * UScale, V2 * VScale);
    NumPrimitives += 2;
}

void FCanvasUtil::BeginBatch()
{
    RI->PushState();
    RI->Clear(0, 0, 0, FColor(0, 0, 0, 255));
    RI->Sub->SetTransform(RI, 0, FMatrix_Identity);
    RI->Sub->SetTransform(RI, 1, FMatrix_Identity);
    RI->Sub->SetTransform(RI, 2, Projection);
    const FVector &V = *GUnnamedVector_ccacc0;
    RI->Sub->SetLight(RI, 0, 1, 0, 0, FPlane(V.X, V.Y, V.Z, 0.f));
    RI->SetZBias(0, 0);
    RI->SetCullMode(2);
}

void FCanvasUtil::FlushBatch()
{
    if (NumPrimitives > 0)
    {
        INT BaseIndex = RI->Sub->SetDynamicStream(RI, 0, this);
        RI->Sub->SetMaterial(RI, CurrentMaterial, 0);
        RI->DrawPrimitive(CurrentType, BaseIndex, NumPrimitives, 0, Vertices.ArrayNum - 1);
        Vertices.ArrayNum = 0;
        NumPrimitives = 0;
    }
}

void FCanvasUtil::DrawBlendTile(const FVector *Points, FLOAT A2, FLOAT A3, FLOAT A4, FLOAT A5, UMaterial *Material,
                                FColor A7, FColor A8, FColor A9, FColor A10, BYTE Blending,
                                UBOOL ZWrite, UBOOL ZTest)
{
    if (!FCanvasUtil_BlendMaterial)
    {
        UObject *Obj = StaticConstructObject(&UnnamedBlend_1122a0_Class, GTransientPackage, 0, 0, 0, GError, 0, 0);
        if (Obj)
            GUnnamedHook_cc4574(Obj);
        FCanvasUtil_BlendMaterial = (UnnamedBlend_1122a0 *)Obj;
        FArray &Roots = GUnnamedRoots_c92540->Roots;
        ((void **)Roots.Data)[Roots.Add(1, 4)] = &FCanvasUtil_BlendMaterial;
        FCanvasUtil_BlendMaterial->AlphaTest = 0;
        FCanvasUtil_BlendMaterial->TwoSided = 1;
        FCanvasUtil_BlendMaterial->AlphaRef = 0;
    }
    if (CurrentMaterial == FCanvasUtil_BlendMaterial &&
        (FCanvasUtil_BlendMaterial->Material != Material ||
         FCanvasUtil_BlendMaterial->ZWrite != ZWrite ||
         FCanvasUtil_BlendMaterial->ZTest != ZTest ||
         FCanvasUtil_BlendMaterial->FrameBufferBlending != Blending))
        FlushBatch();
    FCanvasUtil_BlendMaterial->Material = Material;
    FCanvasUtil_BlendMaterial->ZWrite = ZWrite;
    FCanvasUtil_BlendMaterial->ZTest = ZTest;
    FCanvasUtil_BlendMaterial->FrameBufferBlending = Blending;
    if (CurrentType != 0 || CurrentMaterial != FCanvasUtil_BlendMaterial || Vertices.ArrayNum + 6 > 0x552)
    {
        FlushBatch();
        CurrentType = 0;
        CurrentMaterial = FCanvasUtil_BlendMaterial;
    }
    UnnamedDraw_112ab0(Points, A2, A3, A4, A5, A7, A8, A9, A10);
}

// Scaffolding for the link, not part of the unit: stand-in bodies for the
// LTCG callees (retail 0x111c60 Flush, 0x112ab0) and drivers.
void ExtFlush(void *);
void ExtDraw(void *, const FVector *, FColor, FColor);
__declspec(noinline) void FCanvasUtil::Flush()
{
    if (NumPrimitives > 0)
    {
        RI->PushState();
        RI->Clear(0, 0, 0, FColor(0, 0, 0, 255));
        RI->Sub->SetTransform(RI, 0, FMatrix_Identity);
        RI->Sub->SetTransform(RI, 1, FMatrix_Identity);
        RI->Sub->SetTransform(RI, 2, Projection);
        INT BaseIndex = RI->Sub->SetDynamicStream(RI, 0, this);
        const FVector &V = *GUnnamedVector_ccacc0;
        RI->Sub->SetLight(RI, 0, 1, 0, 0, FPlane(V.X, V.Y, V.Z, 0.f));
        RI->Sub->SetMaterial(RI, CurrentMaterial, 0);
        RI->SetZBias(0, 0);
        RI->SetCullMode(2);
        RI->DrawPrimitive(CurrentType, BaseIndex, NumPrimitives, 0, Vertices.ArrayNum - 1);
        RI->PopState();
        Vertices.ArrayNum = 0;
        NumPrimitives = 0;
    }
}
__declspec(noinline) void FCanvasUtil::UnnamedDraw_112ab0(const FVector *Points, FLOAT A2, FLOAT A3, FLOAT A4, FLOAT A5,
                                                         FColor A7, FColor A8, FColor A9, FColor A10)
{
    PutVertex(Points[0], A7, A2, A3);
    PutVertex(Points[2], A8, A4, A3);
    PutVertex(Points[1], A9, A4, A5);
    PutVertex(Points[0], A7, A2, A3);
    PutVertex(Points[1], A9, A4, A5);
    PutVertex(Points[3], A10, A2, A5);
    NumPrimitives += 2;
}
void Escape(void *);
FCanvasUtil *MakeCanvas();
void Driver_111f50(FLOAT *F, UMaterial *M, FColor Col)
{
    MakeCanvas()->DrawTile(F[0], F[1], F[2], F[3], F[4], F[5], F[6], F[7], F[8], M, Col);
}
struct UnnamedOwner_10c5a0 { BYTE Pad[0x7c]; FCanvasUtil *Canvas; };
void ExtBetween(UnnamedOwner_10c5a0 *);
void Driver_112180(UnnamedOwner_10c5a0 *O)
{
    O->Canvas->BeginBatch();
    ExtBetween(O);
    O->Canvas->FlushBatch();
    O->Canvas->RI->PopState();
}
void Driver_112240(FCanvasUtil *C) { C->FlushBatch(); }
void Driver_1122a0(const FVector *P, FLOAT *F, FColor *Col, UMaterial *M, BYTE B, UBOOL W, UBOOL T)
{
    Escape(&FCanvasUtil_BlendMaterial); Escape(&GUnnamedRoots_c92540);
    MakeCanvas()->DrawBlendTile(P, F[1], F[2], F[3], F[4], M, Col[0], Col[1], Col[2], Col[3], B, W, T);
}
