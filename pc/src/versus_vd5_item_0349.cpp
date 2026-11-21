// Work item w3_0349: Versus RVA 0x111570-0x111a40 (UnRenderUtil.cpp, LTCG unit).
// FLineBatcher (UE2 UnRenderUtil.h): constructor 0x1116c0, destructor 0x111730,
// Flush 0x111790, DrawLine 0x1119a0. Layout from the accessors:
//   +0 vtable (FVertexStream), +4 TArray<FLineVertex> Vertices, +0x10 QWORD CacheId,
//   +0x18 UBOOL ZTest, +0x1c FRenderInterface* RI.
// The render-interface method names are neutral where the evidence only shows
// their slots and arguments.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int size_t;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

inline void *operator new(size_t, void *Mem) { return Mem; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
class FOutputDevice;
extern FOutputDevice *GError;

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) { GMalloc->Free(Data); Data = 0; ArrayMax = 0; }
    }
    ~FArray()
    {
        if (Data) { GMalloc->Free(Data); Data = 0; }
        ArrayMax = ArrayNum = 0;
    }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++) (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item) { INT Index = Add(1); (*this)(Index) = Item; return Index; }
};
template <class T> inline void *operator new(size_t, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};
struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}
};

struct FLineVertex
{
    FVector Position;
    FColor Color;
    FLineVertex(FVector InPosition, FColor InColor) { Position = InPosition; Color = InColor; }
};

class FVertexStream;
class FRenderInterface;
class UObject;

// Interface reached through FRenderInterface+0x14; its calls take the outer
// render interface as their first argument. Neutral names.
class FRenderState
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void SetTransform(FRenderInterface *RI, INT A, INT B, INT C, INT D, FPlane P);   // 0x14
    virtual void V06(); virtual void V07();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Type, FVertexStream *Stream);    // 0x20
    virtual void SetMaterial(FRenderInterface *RI, UObject *Material, INT Flags);            // 0x24
};

class FRenderInterface
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08(); virtual void V09();
    virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14();
    virtual void V15(); virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22();
    virtual void SetZBias(INT A, INT B);                                                      // 0x5c
    virtual void V24();
    virtual void DrawPrimitive(INT Type, INT BaseIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // 0x64
    virtual void V26();
    virtual void SetFillMode(INT Mode);                                                       // 0x6c
    INT Pad04, Pad08, Pad0C;
    INT FillMode;           // 0x10
    FRenderState *State;    // 0x14
};

class FVertexStream
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
};

extern QWORD GCacheId;   // 0x10c96930
inline QWORD MakeCacheID(INT Type) { return GCacheId++ * 256 + Type; }

class FLineBatcher : public FVertexStream
{
public:
    TArray<FLineVertex> Vertices;
    QWORD CacheId;
    UBOOL ZTest;
    FRenderInterface *RI;

    FLineBatcher(FRenderInterface *InRI, UBOOL InZTest);
    ~FLineBatcher();
    void DrawLine(FVector P1, FVector P2, FColor Color);
    void Flush(DWORD PolyFlags = 0);
};

FLineBatcher::FLineBatcher(FRenderInterface *InRI, UBOOL InZTest)
{
    RI = InRI;
    ZTest = InZTest;
    CacheId = MakeCacheID(0xe1);
}

FLineBatcher::~FLineBatcher()
{
    Flush();
}

// Engine objects used by Flush.
// FSolidColorTexture (0x1129b0, same unit): vtable 0x10c03738, +4 Color,
// +8 Revision, +0xc CacheId.
class FBaseTexture
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06();
    virtual INT GetWidth();      // 0x1c
    virtual INT GetHeight();     // 0x20
    virtual void V09(); virtual void V10();
    virtual BYTE GetFormat();    // 0x2c
    virtual BYTE GetUClamp();    // 0x30
    virtual BYTE GetVClamp();    // 0x34
};
class FSolidColorTexture : public FBaseTexture
{
public:
    FColor Color;
    INT Revision;
    QWORD CacheId;
    FSolidColorTexture(FColor InColor) : Color(InColor), Revision(1)
    {
        CacheId = MakeCacheID(0xe0);
    }
};
struct UClass
{
    BYTE Pad[0x104];
    void (*ClassConstructor)(void *);
};
extern UClass UProxyBitmapMaterial_PrivateStaticClass;   // 0x10cc2a30
extern UClass UFinalBlend_PrivateStaticClass;            // 0x10cc4470
enum EName { NAME_None = 0 };
class FName
{
public:
    FName(EName N) : Index(N) {}
    INT Index;
};
UObject *StaticConstructObject(UClass *Class, UObject *Outer, FName Name, DWORD SetFlags,
                               UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot, void *Extra);
extern UObject *GObjTransientPkg;                        // 0x10c925b4
template <class T> T *ConstructObject(UClass *Class, UObject *Outer = (UObject *)-1, FName Name = NAME_None,
                                      DWORD SetFlags = 0, UObject *Template = 0, FOutputDevice *Error = GError,
                                      UObject *SubobjectRoot = 0)
{
    if (Outer == (UObject *)-1)
        Outer = GObjTransientPkg;
    UObject *Result = StaticConstructObject(Class, Outer, Name, SetFlags, Template, Error, SubobjectRoot, 0);
    if (Result)
        Class->ClassConstructor(Result);
    return (T *)Result;
}
BYTE appCeilLogTwo(DWORD Arg);
class UProxyBitmapMaterial
{
public:
    BYTE Pad[0x4c];
    INT UClamp, VClamp, USize, VSize;   // 0x4c..0x58
    BYTE Format, UClampMode, VClampMode, UBits, VBits;
    BYTE Pad61[3];
    FBaseTexture *TextureInterface;     // 0x64
    void SetTextureInterface(FBaseTexture *InTextureInterface);
};
class UFinalBlend
{
public:
    BYTE Pad[0x4c];
    UProxyBitmapMaterial *Material;   // 0x4c
    BYTE Pad50[4];
    DWORD Bit0 : 1;
    DWORD ZTest : 1;                  // 0x54 bit 1
};
struct FStaticRefs { BYTE Pad[0x28]; TArray<void *> Refs; };
extern FStaticRefs *GStaticRefs;                         // 0x10c92540

// Function-local statics of Flush.
extern FSolidColorTexture Flush_WhiteTexture;            // 0x10d51998, local static
extern DWORD Flush_WhiteTexture_Init;                    // 0x10d519ac, its guard
extern UProxyBitmapMaterial *Flush_HackMaterial;         // 0x10ccad54, local static
extern UFinalBlend *Flush_FinalBlend;                    // 0x10ccad50, local static
extern FVector *GLineFogColor;                           // 0x10ccacc0 (neutral name)

void FLineBatcher::Flush(DWORD PolyFlags)
{
    if (Vertices.Num()) {
        INT OldFillMode = RI->FillMode;
        if (OldFillMode != 4) {
            RI->SetFillMode(0);
            INT BaseVertexIndex = RI->State->SetDynamicStream(RI, 0, this);
            if (!(Flush_WhiteTexture_Init & 1)) {
                Flush_WhiteTexture_Init |= 1;
                new(&Flush_WhiteTexture) FSolidColorTexture(FColor(128, 128, 128));
            }
            {
            }
            if (!Flush_HackMaterial) {
                Flush_HackMaterial = ConstructObject<UProxyBitmapMaterial>(&UProxyBitmapMaterial_PrivateStaticClass);
                GStaticRefs->Refs.AddItem(&Flush_HackMaterial);
                Flush_HackMaterial->SetTextureInterface(&Flush_WhiteTexture);
            }
            if (!Flush_FinalBlend) {
                Flush_FinalBlend = ConstructObject<UFinalBlend>(&UFinalBlend_PrivateStaticClass);
                GStaticRefs->Refs.AddItem(&Flush_FinalBlend);
                Flush_FinalBlend->Material = Flush_HackMaterial;
            }
            Flush_FinalBlend->ZTest = ZTest;
            FPlane Fog(GLineFogColor->X, GLineFogColor->Y, GLineFogColor->Z, 0);
            RI->State->SetTransform(RI, 0, 1, 0, 0, Fog);
            RI->State->SetMaterial(RI, (UObject *)Flush_FinalBlend, 0);
            RI->SetZBias(0, 0);
            RI->DrawPrimitive(4, BaseVertexIndex, Vertices.Num() / 2, 0, Vertices.Num() - 1);
            Vertices.Empty();
            RI->SetFillMode(OldFillMode);
        }
    }
}

void FLineBatcher::DrawLine(FVector P1, FVector P2, FColor Color)
{
    new(Vertices) FLineVertex(P1, Color);
    new(Vertices) FLineVertex(P2, Color);
}

// UProxyBitmapMaterial::SetTextureInterface lives in another unit (0xe4780);
// defined here only so the LTCG link gives it the retail register convention.
void UProxyBitmapMaterial::SetTextureInterface(FBaseTexture *InTextureInterface)
{
    TextureInterface = InTextureInterface;
    Format = TextureInterface->GetFormat();
    UClampMode = TextureInterface->GetUClamp();
    VClampMode = TextureInterface->GetVClamp();
    UClamp = USize = TextureInterface->GetWidth();
    VClamp = VSize = TextureInterface->GetHeight();
    UBits = appCeilLogTwo(USize);
    VBits = appCeilLogTwo(VSize);
}

// Scaffolding for the link, not part of the unit: callers shaped like the
// retail ones (0x12a1f9 builds a batcher on the stack from Viewport->RI with
// ZTest 1, draws, and destroys it; 0x9a67b flushes with a PolyFlags value).
void Escape(void *);
struct FViewportStub { BYTE Pad[0x140]; FRenderInterface *RI; };
void Driver_A(FViewportStub *V, FVector A, FVector C, FColor Col)
{
    Escape(&GMalloc);
    FLineBatcher LB(V->RI, 1);
    LB.DrawLine(A, C, Col);
}
void Driver_B(FRenderInterface *RI, UBOOL Z, FVector A, FVector C, FColor Col, DWORD PolyFlags)
{
    FLineBatcher LB(RI, Z);
    LB.DrawLine(A, C, Col);
    LB.Flush(PolyFlags);
}
// Several construction sites, as in retail (three callers), keep the
// constructor out of line.
void Driver_C(FViewportStub *V, FVector A, FVector C, FColor Col)
{
    for (INT i = 0; i < 8; i++) {
        FLineBatcher *LB = new(&V[i]) FLineBatcher(V[i + 1].RI, i);
        LB->DrawLine(A, C, Col);
    }
    new(&V[20]) FLineBatcher(V[21].RI, 0);
    new(&V[22]) FLineBatcher(V[23].RI, 1);
    new(&V[24]) FLineBatcher(V[25].RI, 0);
    new(&V[26]) FLineBatcher(V[27].RI, 1);
}
