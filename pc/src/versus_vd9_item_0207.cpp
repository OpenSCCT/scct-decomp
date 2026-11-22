// Work item 0207: UScriptedTexture::execDrawTile (RVA 0xe69d0).
// The callees (FCanvasUtil constructor, DrawTile, destructor) were link-time
// optimised in retail: `this` on the stack for the constructor/destructor and
// in EAX for DrawTile, which retail calls on the constructor's returned
// pointer, so the canvas is a temporary. Field names at 0x64/0x68 are neutral
// guesses. Matches with try_ltcg.py, root Driver_e69d0, /O2 /Gy /GX.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#define RESULT_DECL void *Result

class UObject;
struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, RESULT_DECL);
extern Native GNatives[];

class UObject
{
public:
    void *VfTable_Dummy;
};

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_FLOAT(v) FLOAT v = 0.f; Stack.Step(Stack.Object, &v);
#define P_GET_OBJECT(cls, v) cls *v = 0; Stack.Step(Stack.Object, &v);
#define P_GET_STRUCT(typ, v) typ v; Stack.Step(Stack.Object, &v);
#define P_FINISH Stack.Code++;

struct FColor
{
    BYTE B, G, R, A;
};

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
class FRenderTarget;
class FRenderInterface;

// Neutral name: object at 0x68 holding the render interface at 0x140.
struct UnnamedClient_e69d0
{
    BYTE Pad[0x140];
    FRenderInterface *RI;
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
    FCanvasVertexArray();
    ~FCanvasVertexArray();
};

class FCanvasUtil
{
public:
    void *VfTable;
    INT CurrentType;              // 0x04
    UMaterial *CurrentMaterial;   // 0x08
    BYTE Head[0x88];
    void Flush();
    void PutVertex(FLOAT X, FLOAT Y, FLOAT Z, FColor C, FLOAT U, FLOAT V)
    {
        FCanvasVertex *P = &Vertices.Data[Vertices.Add(1, sizeof(FCanvasVertex))];
        if (P) { P->X = X; P->Y = Y; P->Z = Z; P->Color = C; P->U = U; P->V = V; }
    }
    FCanvasVertexArray Vertices;  // 0x94
    BYTE Tail[0x8];
    FCanvasUtil(FRenderTarget *InRenderTarget, FRenderInterface *InRI);
    ~FCanvasUtil();
    void DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
                  FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *Material, FColor Color);
};

class UScriptedTexture : public UObject
{
public:
    BYTE Pad[0x60];
    FRenderTarget *RenderTarget;          // 0x64
    UnnamedClient_e69d0 *Client;          // 0x68
    void execDrawTile(FFrame &Stack, RESULT_DECL);
};

void UScriptedTexture::execDrawTile(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(X);
    P_GET_FLOAT(Y);
    P_GET_FLOAT(XL);
    P_GET_FLOAT(YL);
    P_GET_FLOAT(U);
    P_GET_FLOAT(V);
    P_GET_FLOAT(UL);
    P_GET_FLOAT(VL);
    P_GET_OBJECT(UMaterial, Material);
    P_GET_STRUCT(FColor, Color);
    P_FINISH;

    FCanvasUtil(RenderTarget, Client->RI).DrawTile(X, Y, X + XL, Y + YL, U, V, U + UL, V + VL, 0, Material, Color);
}

// Scaffolding for the link, not part of the unit: stand-in bodies for the
// LTCG callees (retail 0x131ad0 ctor, 0x131f50 DrawTile, 0x131c00 dtor) so the
// linker picks retail's custom conventions at the call sites.
void ExtInit(void *, FRenderTarget *, FRenderInterface *);
void ExtFlush(void *);
__declspec(noinline) FCanvasUtil::FCanvasUtil(FRenderTarget *InRenderTarget, FRenderInterface *InRI) { ExtInit(this, InRenderTarget, InRI); }
__declspec(noinline) FCanvasUtil::~FCanvasUtil() { ExtFlush(this); }

__declspec(noinline) void FCanvasUtil::DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
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
}
void Escape(void *);
void Driver_e69d0(UScriptedTexture *T, FFrame *S, void *R)
{
    Escape(&GNatives);
    void (UScriptedTexture::*P)(FFrame &, void *) = &UScriptedTexture::execDrawTile;
    Escape(&P);
    (T->*P)(*S, R);
}
