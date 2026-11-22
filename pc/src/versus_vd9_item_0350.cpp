// Work item 0350 (wave 3): Versus RVA 0x111ad0-0x111f44, FCanvasUtil
// (UnRenderUtil.cpp, Engine): constructor (0x111ad0), destructor (0x111c00),
// Flush (0x111c60) and DrawLine (0x111d80). LTCG unit: the constructor and
// destructor take `this` on the stack, Flush takes it in ESI, DrawLine in EDI.
// Layout and names follow the neighbouring units (w3_item_0293, 0300).
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;
#define NULL 0

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

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
struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(FPlane InX, FPlane InY, FPlane InZ, FPlane InW);       // 0x4fbc0
    FMatrix operator*(const FMatrix &Other) const;                 // 0x7b110
    FMatrix Inverse() const;                                       // 0x53af0
};
struct FScaleMatrix : public FMatrix { FScaleMatrix(const FVector &Scale); };          // 0x81910
struct FTranslationMatrix : public FMatrix { FTranslationMatrix(const FVector &Delta); }; // 0x819b0
struct FColor
{
    BYTE R, G, B, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
};
extern FMatrix GIdentityMatrix;
extern FVector *GAmbientLight;

class FRenderInterface;
class FVertexStream;
class UMaterial;

class FRenderState
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10();
    virtual void SetLight(FRenderInterface *RI, INT Index, INT A, INT B, INT C, FPlane Color); // +0x14
    virtual void SetTransform(FRenderInterface *RI, INT Type, const FMatrix *Matrix);        // +0x18
    virtual void Slot1c();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Index, FVertexStream *Stream);     // +0x20
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *Material, INT Flags);          // +0x24
};

class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual void Slot08();
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height); // +0x0c
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18();
    virtual void SetCullMode(INT Mode);                            // +0x1c
    virtual void Slot20();
    virtual void Clear(INT A, INT B, INT C, FColor Color);         // +0x24
    virtual void Slot28(); virtual void Slot2c(); virtual void Slot30(); virtual void Slot34();
    virtual void Slot38(); virtual void Slot3c(); virtual void Slot40(); virtual void Slot44();
    virtual void Slot48(); virtual void Slot4c(); virtual void Slot50(); virtual void Slot54();
    virtual void Slot58();
    virtual void EnableLighting(INT A, INT B);                     // +0x5c
    virtual void Slot60();
    virtual void DrawPrimitive(INT Type, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // +0x64
    BYTE Pad04[0x14 - 0x04];
    FRenderState *State;                                           // +0x14
    void SetLight(INT Index, INT A, INT B, INT C, FPlane Color) { State->SetLight(this, Index, A, B, C, Color); }
    void SetTransform(INT Type, const FMatrix *Matrix) { State->SetTransform(this, Type, Matrix); }
    INT SetDynamicStream(INT Index, FVertexStream *Stream) { return State->SetDynamicStream(this, Index, Stream); }
    void SetMaterial(UMaterial *Material, INT Flags) { State->SetMaterial(this, Material, Flags); }
};

class FRenderTarget
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06();
    virtual INT GetWidth();                                        // +0x1c
    virtual INT GetHeight();                                       // +0x20
};

// Objects and classes (UE2): UClass::ClassConstructor is at +0x104.
class UObject;
class UClass
{
public:
    BYTE Pad00[0x104];
    void (*ClassConstructor)(void *);                              // +0x104
};
class UObject
{
public:
    BYTE Pad00[0x2c];
};
class UMaterial : public UObject {};

class FOutputDevice;
extern FOutputDevice *GError;                                      // 0x10c71aa8
extern UObject *GTransientPackage;                                 // 0x10c925b4 (neutral name)
enum EName { NAME_None = 0 };
class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
};
UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                              UObject *Template, FOutputDevice *Error, UObject *Ptr, UObject *SubobjectRoot); // 0x1d380
__forceinline UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags = 0,
                                             UObject *Template = NULL, FOutputDevice *Error = GError,
                                             UObject *SubobjectRoot = NULL)
{
    UObject *Result = StaticAllocateObject(Class, InOuter, Name, SetFlags, Template, Error, NULL, SubobjectRoot);
    if (Result)
        (*Class->ClassConstructor)(Result);
    return Result;
}
template <class T> __forceinline T *ConstructObject(UClass *Class, UObject *Outer, FName Name = NAME_None)
{
    return (T *)StaticConstructObject(Class, Outer, Name);
}

extern const TCHAR CanvasUtil_AllocTag[];                          // L"FArray::Empty"
extern const TCHAR CanvasUtil_ReallocTag[];                        // L"FArray"
class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                           // 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);            // 0x119c0
    void Realloc(INT ElementSize)
    {
        if (Data == NULL)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, CanvasUtil_AllocTag);
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, CanvasUtil_ReallocTag);
    }
    void Empty(INT ElementSize, INT Slack)
    {
        ArrayNum = 0;
        if (ArrayMax != Slack) {
            ArrayMax = Slack;
            Realloc(ElementSize);
        }
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = NULL;
        ArrayNum = ArrayMax = 0;
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

// Holder of a list of object references kept alive (retail 0x10981a50
// adds one; the object is the global at 0x10c92540). Names neutral.
class UnnamedRefHolder_1a50
{
public:
    BYTE Pad[0x28];
    FArray Refs;                                                   // +0x28
    void AddRef(void *Ref)
    {
        INT Index = Refs.Add(1, sizeof(void *));
        ((void **)Refs.Data)[Index] = Ref;
    }
};
extern UnnamedRefHolder_1a50 *GUnnamedRefHolder_1a50;

extern QWORD GCacheCounter;                                        // 0x10c96930
enum ECacheIDBase { CID_RenderTexture = 0xe0, CID_RenderVertices = 0xe1 };
inline QWORD MakeCacheID(ECacheIDBase Base)
{
    return GCacheCounter++ * 256 + Base;
}

// FTexture interface (UE2 UnRenDev.h); only the slots used here are named.
class FTexture
{
public:
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10(); virtual void Slot14();
    virtual void Slot18();
    virtual INT GetWidth();                                        // +0x1c
    virtual INT GetHeight();                                       // +0x20
    virtual void Slot24(); virtual void Slot28();
    virtual BYTE GetFormat();                                      // +0x2c
    virtual BYTE GetUClamp();                                      // +0x30
    virtual BYTE GetVClamp();                                      // +0x34
};

// A one-texel texture of a solid colour (retail constructor 0x1129b0).
class FSolidColorTexture : public FTexture
{
public:
    FColor Color;                                                  // +0x04
    INT Revision;                                                  // +0x08
    QWORD CacheId;                                                 // +0x0c
    FSolidColorTexture(FColor InColor);
};

BYTE FLogTwo(DWORD Value);                                         // 0x12050

// UProxyBitmapMaterial (UE2): a bitmap material wrapping an FTexture.
class UProxyBitmapMaterial : public UMaterial
{
public:
    BYTE Pad2c[0x4c - 0x2c];
    INT UClamp, VClamp;                                            // +0x4c
    INT USize, VSize;                                              // +0x54
    BYTE Format, UClampMode, VClampMode, UBits, VBits;             // +0x5c
    BYTE Pad61[3];
    FTexture *TextureInterface;                                    // +0x64
    static UClass PrivateStaticClass;                              // 0x10cc2a30
    void SetTextureInterface(FTexture *InTextureInterface);       // 0xe4780
};

class UFinalBlend : public UMaterial
{
public:
    BYTE Pad2c[0x4c - 0x2c];
    UMaterial *Material;                                           // +0x4c
    static UClass PrivateStaticClass;                              // 0x10cc4470
};

struct FCanvasVertex { FLOAT X, Y, Z; DWORD Color; FLOAT U, V; };

class FVertexStream
{
public:
    virtual QWORD GetCacheId();
};


class FCanvasUtil : public FVertexStream
{
public:
    INT PrimitiveType;                                             // +0x04
    UMaterial *Material;                                           // +0x08
    INT NumPrimitives;                                             // +0x0c
    FRenderInterface *RI;                                          // +0x10
    FMatrix CanvasToScreen;                                        // +0x14
    FMatrix ScreenToClip;                                          // +0x54
    TArray<FCanvasVertex> Vertices;                                // +0x94
    QWORD CacheId;                                                 // +0xa0

    FCanvasUtil(FRenderTarget *RenderTarget, FRenderInterface *InRI);
    ~FCanvasUtil();
    void Flush();
    void BeginPrimitive(INT InType, UMaterial *InMaterial, INT NumVertices)
    {
        if (PrimitiveType != InType || Material != InMaterial || Vertices.ArrayNum + NumVertices > 1362) {
            Flush();
            PrimitiveType = InType;
            Material = InMaterial;
        }
    }
    void DrawLine(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FColor Color);
    // 0x103f00. Retail treats it as unable to throw (it has no EH frame), so the
    // constructor reuses its `this` argument slot as a temporary before the call.
    void Init(FRenderInterface *InRI, FLOAT Width, FLOAT Height) throw();
};

// Function-local statics of DrawLine that need no guard (0x10ccad4c, 0x10ccad48).
extern UProxyBitmapMaterial *DrawLine_LineTexture;
extern UFinalBlend *DrawLine_LineMaterial;
// DrawLine's guarded local static `WhiteTexture` (0x10d51980) and the
// compiler's guard flags for it (0x10d51994), spelled out because the
// verifier cannot bind private data.
extern FSolidColorTexture DrawLine_WhiteTexture;
extern DWORD DrawLine_WhiteTexture_Guard;
inline void *operator new(unsigned int, void *Where) { return Where; }

// RVA 0x111ad0.
FCanvasUtil::FCanvasUtil(FRenderTarget *RenderTarget, FRenderInterface *InRI)
{
    CacheId = MakeCacheID(CID_RenderVertices);
    PrimitiveType = 4;
    Material = NULL;
    NumPrimitives = 0;
    Vertices.Empty(sizeof(FCanvasVertex), 1362);
    Init(InRI, (FLOAT)RenderTarget->GetWidth(), (FLOAT)RenderTarget->GetHeight());
}

// RVA 0x111c60.
void FCanvasUtil::Flush()
{
    if (NumPrimitives > 0) {
        RI->PushState();
        RI->Clear(0, 0, 0, FColor(0, 0, 0));
        RI->SetTransform(0, &GIdentityMatrix);
        RI->SetTransform(1, &GIdentityMatrix);
        RI->SetTransform(2, &ScreenToClip);
        INT FirstVertex = RI->SetDynamicStream(0, this);
        RI->SetLight(0, 1, 0, 0, FPlane(*GAmbientLight, 0));
        RI->SetMaterial(Material, 0);
        RI->EnableLighting(0, 0);
        RI->SetCullMode(2);
        RI->DrawPrimitive(PrimitiveType, FirstVertex, NumPrimitives, 0, Vertices.ArrayNum - 1);
        RI->PopState();
        Vertices.ArrayNum = 0;
        NumPrimitives = 0;
    }
}

// RVA 0x111c00.
__declspec(noinline) FCanvasUtil::~FCanvasUtil()
{
    Flush();
}

// RVA 0x111d80.
void FCanvasUtil::DrawLine(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FColor Color)
{
    // static FSolidColorTexture WhiteTexture(FColor(255, 255, 255, 255));
    if (!(DrawLine_WhiteTexture_Guard & 1)) {
        DrawLine_WhiteTexture_Guard |= 1;
        new (&DrawLine_WhiteTexture) FSolidColorTexture(FColor(255, 255, 255, 255));
    }
    if (!DrawLine_LineTexture) {
        DrawLine_LineTexture = ConstructObject<UProxyBitmapMaterial>(&UProxyBitmapMaterial::PrivateStaticClass, GTransientPackage);
        GUnnamedRefHolder_1a50->AddRef(&DrawLine_LineTexture);
        DrawLine_LineTexture->SetTextureInterface(&DrawLine_WhiteTexture);
    }
    if (!DrawLine_LineMaterial) {
        DrawLine_LineMaterial = ConstructObject<UFinalBlend>(&UFinalBlend::PrivateStaticClass, GTransientPackage);
        GUnnamedRefHolder_1a50->AddRef(&DrawLine_LineMaterial);
        DrawLine_LineMaterial->Material = DrawLine_LineTexture;
    }
    BeginPrimitive(4, DrawLine_LineMaterial, 2);
    DWORD C = *(DWORD *)&Color;
    FCanvasVertex *V;
    V = &Vertices(Vertices.Add(1, sizeof(FCanvasVertex)));
    if (V) { V->X = X1; V->Y = Y1; V->Z = 0; V->Color = C; V->U = 0; V->V = 0; }
    V = &Vertices(Vertices.Add(1, sizeof(FCanvasVertex)));
    if (V) { V->X = X2; V->Y = Y2; V->Z = 0; V->Color = C; V->U = 0; V->V = 0; }
    NumPrimitives++;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for callees
// retail calls with LTCG conventions (so the linker gives them the retail
// conventions), and a driver.
__declspec(noinline) FSolidColorTexture::FSolidColorTexture(FColor InColor)
{
    Color = InColor;
    Revision = 1;
    CacheId = GCacheCounter * 256 + 0xe0;
    GCacheCounter++;
}

__declspec(noinline) void UProxyBitmapMaterial::SetTextureInterface(FTexture *InTextureInterface)
{
    TextureInterface = InTextureInterface;
    Format = TextureInterface->GetFormat();
    UClampMode = TextureInterface->GetUClamp();
    VClampMode = TextureInterface->GetVClamp();
    UClamp = USize = TextureInterface->GetWidth();
    VClamp = VSize = TextureInterface->GetHeight();
    UBits = FLogTwo(USize);
    VBits = FLogTwo(VSize);
}

void Escape(void *);
__declspec(noinline) FScaleMatrix::FScaleMatrix(const FVector& Scale)
    : FMatrix(FPlane(Scale.X, 0, 0, 0), FPlane(0, Scale.Y, 0, 0), FPlane(0, 0, Scale.Z, 0), FPlane(0, 0, 0, 1)) {}
__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
    : FMatrix(FPlane(1, 0, 0, 0), FPlane(0, 1, 0, 0), FPlane(0, 0, 1, 0), FPlane(Delta.X, Delta.Y, Delta.Z, 1)) {}
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix& Other) const
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
FLOAT Determinant(const FMatrix* M);
__declspec(noinline) FMatrix FMatrix::Inverse() const
{
    if (Determinant(this) == 0.0f)
        return GIdentityMatrix;
    FMatrix R;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            R.M[i][j] = M[j][i];
    return R;
}
__declspec(noinline) void FCanvasUtil::Init(FRenderInterface *InRI, FLOAT Width, FLOAT Height) throw()
{
    RI = InRI;
    ScreenToClip = FTranslationMatrix(FVector(-Width / 2.0f - 0.5f, -Height / 2.0f - 0.5f, 0.0f))
                 * FScaleMatrix(FVector(2.0f / Width, -2.0f / Height, 1.0f));
    CanvasToScreen = ScreenToClip.Inverse();
}

void Driver_111ad0(FRenderTarget *RT, FRenderInterface *RI, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FColor C)
{
    Escape(&GMalloc); Escape(&DrawLine_LineTexture); Escape(&DrawLine_LineMaterial);
    Escape(&GUnnamedRefHolder_1a50); Escape(&GTransientPackage); Escape(&GError); Escape(&GAmbientLight);
    FCanvasUtil U(RT, RI);
    U.DrawLine(X1, Y1, X2, Y2, C);
    U.DrawLine(Y1, X1, Y2, X2, C);
}
