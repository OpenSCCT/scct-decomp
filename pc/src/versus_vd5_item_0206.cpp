// Work item 0206: Versus RVA 0xe65c0-0xe69c1, UScriptedTexture (UnScriptedTexture.cpp, Engine).
//   0xe65c0 UScriptedTexture::Destroy
//   0xe6600 UScriptedTexture::execSetSize
//   0xe6690 UScriptedTexture::execDrawText
//   0xe6800 UScriptedTexture::execTextSize
// The unit is link-time optimised (VC7.0 /GL, /LTCG): appCeilLogTwo takes its
// argument in EDX and the FCanvasUtil methods take `this` on the stack.
// Field names follow UE2 UBitmapMaterial / UScriptedTexture where the offsets
// agree; RenderTarget/Client at +0x64/+0x68 are named from their use.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
#define RESULT_DECL void *const Result

class UObject;
class UProperty;
class UFont;
class URenderDevice;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
inline void appFree(void *Ptr) { GMalloc->Free(Ptr); }

BYTE appCeilLogTwo(DWORD Arg);                        // RVA 0x12050

extern const TCHAR EmptyString[];                     // L"" (VA 0x10c10928)

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
};

struct FColor {
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
};

class UObject {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);                                 // +0x54
    void Destroy();                                                              // RVA 0x15ce0
    BYTE ObjectPad[0x28 - 4];
};

struct FFontCharacter {
    INT StartU, StartV, USize, VSize;
};

class UFont : public UObject {
public:
    FFontCharacter *Characters;       // +0x28 (TArray data)
};

struct FScriptedClient {
    BYTE Pad[0x140];
    URenderDevice *RenDev;            // +0x140
};

struct FFrame {
    void *VfTable;
    void *Node;                 // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    // Steps an out parameter: GPropAddr is cleared once the opcode is fetched.
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

class FCanvasUtil {
public:
    virtual void Flush();
    void *Target;
    URenderDevice *RenDev;
    BYTE Pad[0x94 - 0xc];
    FString Lines;              // +0x94
    BYTE Pad2[0xa8 - 0xa0];
    FCanvasUtil(void *InRenderTarget, URenderDevice *InRenDev);   // RVA 0xa11ad0
    ~FCanvasUtil();                                                 // RVA 0xa11c00
    INT DrawString(INT X, INT Y, const TCHAR *Text, UFont *Font, FColor Color); // RVA 0xa12420
};

class UScriptedTexture : public UObject {
public:
    BYTE Pad28[0x4c - 0x28];
    INT USize;                  // +0x4c
    INT VSize;                  // +0x50
    INT UClamp;                 // +0x54
    INT VClamp;                 // +0x58
    BYTE Pad5c[3];
    BYTE UBits;                 // +0x5f
    BYTE VBits;                 // +0x60
    BYTE Pad61[3];
    void *RenderTarget;         // +0x64
    FScriptedClient *Client;    // +0x68
    INT Pad6c;
    INT Revision;               // +0x70

    void Destroy();
    void execSetSize(FFrame &Stack, RESULT_DECL);
    void execDrawText(FFrame &Stack, RESULT_DECL);
    void execTextSize(FFrame &Stack, RESULT_DECL);
};

#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_STRUCT(typ, var) typ var; Stack.Step(Stack.Object, &var);
#define P_GET_INT_REF(var) INT var##T = 0; Stack.StepRef(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    INT *var = GPropAddr ? (INT *)GPropAddr : &var##T;
#define P_FINISH Stack.Code++;

void UScriptedTexture::Destroy()
{
    UObject::Destroy();
    if (RenderTarget)
        appFree(RenderTarget);
}

void UScriptedTexture::execSetSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Width);
    P_GET_INT(Height);
    P_FINISH;
    UClamp = USize = Width;
    UBits = appCeilLogTwo(USize);
    VClamp = VSize = Height;
    VBits = appCeilLogTwo(VSize);
    Revision++;
}

void UScriptedTexture::execDrawText(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(X);
    P_GET_INT(Y);
    P_GET_STR(Text);
    P_GET_OBJECT(UFont, Font);
    P_GET_STRUCT(FColor, Color);
    P_FINISH;
    if (!Font)
        return;
    FCanvasUtil(RenderTarget, Client->RenDev).DrawString(X, Y, *Text, Font, Color);
}

void UScriptedTexture::execTextSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    P_GET_OBJECT(UFont, Font);
    P_GET_INT_REF(XL);
    P_GET_INT_REF(YL);
    P_FINISH;
    if (!Font)
        return;
    *XL = FCanvasUtil(RenderTarget, Client->RenDev).DrawString(0, 0, *Text, Font, FColor(0, 0, 0, 0));
    *YL = Font->Characters[0].VSize;
}

// Scaffolding for the LTCG link, not part of the unit. The callees are defined
// here only so the linker gives them the register conventions retail uses.
extern const BYTE GLogs[256];   // VA 0x10c78bc8
__declspec(noinline) BYTE appCeilLogTwo(DWORD Arg)
{
    if (--Arg == (DWORD)-1)
        return 0;
    BYTE Shift = Arg <= 0x10000 ? (Arg > 0x100 ? 8 : 0) : (Arg > 0x1000000 ? 24 : 16);
    return GLogs[Arg >> Shift] + Shift;
}
void Escape(void *);
// FCanvasUtil (RVA 0xa11ad0 constructor, 0xa11c00 destructor) has a vtable and
// an array member at +0x94, so both carry exception frames; the linker then
// passes `this` on the stack. DrawString walks Text first, so Text arrives in EAX.
void CanvasFlush(FCanvasUtil *Canvas);
__declspec(noinline) FCanvasUtil::FCanvasUtil(void *InRenderTarget, URenderDevice *InRenDev)
{
    CanvasFlush(this);
    Target = InRenderTarget;
    CanvasFlush(this);
    RenDev = InRenDev;
    CanvasFlush(this);
}
__declspec(noinline) FCanvasUtil::~FCanvasUtil()
{
    CanvasFlush(this);
}
__declspec(noinline) INT FCanvasUtil::DrawString(INT X, INT Y, const TCHAR *Text, UFont *Font, FColor Color)
{
    INT W = 0, H = 0, Count = 0;
    for (const TCHAR *P = Text; *P; P++)
    {
        FFontCharacter &C = Font->Characters[*P];
        CanvasFlush(this);
        W += C.USize + X;
        H += C.VSize + Y;
        Count += Color.R;
    }
    return W + H + Count;
}
void Driver_e65c0() { void (UScriptedTexture::*F)() = &UScriptedTexture::Destroy; Escape(&F); Escape(&GMalloc); }
void Driver_e6600(Native *Out) { *Out = (Native)&UScriptedTexture::execSetSize; Escape(GNatives); }
void Driver_e6690(Native *Out) { *Out = (Native)&UScriptedTexture::execDrawText; Escape(GNatives); }
void Driver_e6800(Native *Out) { *Out = (Native)&UScriptedTexture::execTextSize; Escape(&GPropAddr); Escape(&GPropObject); Escape(&GProperty); Escape(GNatives); }
