// Work item 0101: Versus RVA 0x1505e0-0x15085b (UnLevRender.cpp / BSP rendering).
//   0x1505e0: FBspStencilDrawList::Render (VC7.0 /GL, linked /LTCG)
//   0x150820: HBspSurf::IsA (VC7.0)

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int size_t;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned __int64 QWORD;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
inline void *operator new(size_t, void *Mem) { return Mem; }

class FOutputDevice;
extern FOutputDevice *GError;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FSphere : public FPlane
{
    FSphere() {}
    FSphere(const FVector &V, FLOAT W) : FPlane(V, W) {}
};

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255)
        : B(InB), G(InG), R(InR), A(InA) {}
};

extern QWORD GCacheId;
inline QWORD MakeCacheID(INT Type) { return GCacheId++ * 256 + Type; }

class FVertexStream
{
public:
    virtual void V00();
};

class FIndexBuffer
{
public:
    virtual void V00();
};

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

#pragma pack(push, 4)
class FSolidColorTexture : public FBaseTexture
{
public:
    FColor Color;
    INT Revision;
    QWORD CacheId;
    __declspec(noinline) FSolidColorTexture(FColor InColor) : Color(InColor), Revision(1)
    {
        CacheId = MakeCacheID(0xe0);
    }
};
#pragma pack(pop)

class UObject;
struct UClass
{
    BYTE Pad[0x104];
    void (*ClassConstructor)(void *);
};
extern UClass UProxyBitmapMaterial_PrivateStaticClass;
extern UClass UFinalBlend_PrivateStaticClass;

enum EName { NAME_None = 0 };
class FName
{
public:
    FName(EName N) : Index(N) {}
    INT Index;
};

UObject *StaticConstructObject(UClass *Class, UObject *Outer, FName Name, DWORD SetFlags,
                               UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot, void *Extra);
extern UObject *GObjTransientPkg;

template <class T> __forceinline T *ConstructObject(UClass *Class, UObject *Outer = (UObject *)-1,
                                                    FName Name = NAME_None, DWORD SetFlags = 0,
                                                    UObject *Template = 0, FOutputDevice *Error = GError,
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
    __declspec(noinline) void SetTextureInterface(FBaseTexture *InTextureInterface);
};

enum EFrameBufferBlending
{
    FB_Overwrite = 0
};

enum ECompareFunction
{
    CF_LessEqual = 3,
    CF_Equal = 6
};

enum EStencilOp
{
    SO_Keep = 1,
    SO_Replace = 3
};

enum EVertexShader
{
    VS_FixedFunction = 0
};

enum EPrimitiveType
{
    PT_TriangleList = 0
};

class UFinalBlend
{
public:
    BYTE Pad[0x4c];
    UProxyBitmapMaterial *Material;     // 0x4c
    BYTE FrameBufferBlending;           // 0x50
    BYTE Pad51[3];
    DWORD ZWrite : 1;                   // 0x54 bit 0
    DWORD ZTest : 1;                    // 0x54 bit 1
    DWORD AlphaTest : 1;                // 0x54 bit 2
    DWORD TwoSided : 1;                 // 0x54 bit 3
};

struct FStaticRefs
{
    BYTE Pad[0x28];
    TArray<void *> Refs;
};
extern FStaticRefs *GStaticRefs;

class FRenderInterface;

// Interface reached through FRenderInterface+0x14; its calls take the outer
// render interface as their first argument.
class FRenderState
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void EnableLighting(FRenderInterface *RI, INT A, INT B, INT C, INT D, FSphere P);   // 0x14
    virtual void V06();
    virtual void SetVertexStreams(FRenderInterface *RI, INT Shader, FVertexStream **Streams, INT NumStreams); // 0x1c
    virtual void V08();
    virtual void SetMaterial(FRenderInterface *RI, UObject *Material, INT Flags);               // 0x24
};

class FRenderInterface
{
public:
    virtual void PushState();                                                                   // 0x00
    virtual void PopState();                                                                    // 0x04
    virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08(); virtual void V09();
    virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14();
    virtual void V15(); virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void SetStencilOp(INT Test, DWORD Ref, DWORD Mask, INT FailOp, INT ZFailOp, INT PassOp, DWORD WriteMask); // 0x50
    virtual void V21(); virtual void V22(); virtual void V23();
    virtual INT SetDynamicIndexBuffer(FIndexBuffer *IndexBuffer, INT BaseVertexIndex);          // 0x60
    virtual void DrawPrimitive(INT Type, INT BaseIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // 0x64
    INT Pad04, Pad08, Pad0C, Pad10;
    FRenderState *State;                                                                        // 0x14
};

struct FBspSection
{
    FVertexStream Vertices;             // 0x00
    BYTE Pad04[0x34];                   // sizeof(FBspSection) == 0x38
};

class UModel
{
public:
    BYTE Pad00[0xd4];
    TArray<FBspSection> Sections;       // 0xd4
};

class FLevelSceneNode
{
public:
    BYTE Pad00[0x1d0];
    DWORD StencilRef;                   // 0x1d0
};

class FBspStencilDrawList;

#pragma pack(push, 4)
class FBspDynamicIndexBuffer : public FIndexBuffer
{
public:
    FBspStencilDrawList *DrawList;      // 0x04
    QWORD CacheId;                      // 0x08
    _WORD MinIndex;                     // 0x10
    _WORD MaxIndex;                     // 0x12

    __declspec(noinline) FBspDynamicIndexBuffer(FBspStencilDrawList *InDrawList)
        : DrawList(InDrawList)
    {
        CacheId = MakeCacheID(0xe2);
        MinIndex = 0x7fff;
        MaxIndex = 0;
    }
};
#pragma pack(pop)

// Function-local statics of FBspStencilDrawList::Render.
extern FSolidColorTexture RenderBspStencil_GreyTexture;        // 0x10d518c8, local static
extern DWORD RenderBspStencil_GreyTexture_Init;                // 0x10d518dc, its guard
extern UProxyBitmapMaterial *RenderBspStencil_HackMaterial;    // 0x10ccacfc, local static
extern UFinalBlend *RenderBspStencil_FinalBlend;               // 0x10ccacf8, local static
extern FVector *GZeroVector;                                   // 0x10ccacc0

class FBspStencilDrawList
{
public:
    UModel *Model;                      // 0x00
    INT SectionIndex;                   // 0x04
    INT Pad08;                          // 0x08
    INT NumTriangles;                   // 0x0c
    INT Pad10;                          // 0x10
    DWORD StencilMask;                  // 0x14

    __declspec(noinline) void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI);
};

// RVA 0x1505e0
void FBspStencilDrawList::Render(FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    if (NumTriangles > 0)
    {
        RI->PushState();

        if (!(RenderBspStencil_GreyTexture_Init & 1))
        {
            RenderBspStencil_GreyTexture_Init |= 1;
            new(&RenderBspStencil_GreyTexture) FSolidColorTexture(FColor(128, 128, 128));
        }

        if (!RenderBspStencil_HackMaterial)
        {
            RenderBspStencil_HackMaterial = ConstructObject<UProxyBitmapMaterial>(&UProxyBitmapMaterial_PrivateStaticClass);
            GStaticRefs->Refs.AddItem(&RenderBspStencil_HackMaterial);
            RenderBspStencil_HackMaterial->SetTextureInterface(&RenderBspStencil_GreyTexture);
        }

        if (!RenderBspStencil_FinalBlend)
        {
            RenderBspStencil_FinalBlend = ConstructObject<UFinalBlend>(&UFinalBlend_PrivateStaticClass);
            GStaticRefs->Refs.AddItem(&RenderBspStencil_FinalBlend);
            RenderBspStencil_FinalBlend->Material = RenderBspStencil_HackMaterial;
            RenderBspStencil_FinalBlend->FrameBufferBlending = FB_Overwrite;
            RenderBspStencil_FinalBlend->ZWrite = 1;
            RenderBspStencil_FinalBlend->TwoSided = 1;
        }

        FSphere Sphere(*GZeroVector, 0);
        RI->State->EnableLighting(RI, 0, 0, 0, 0, Sphere);
        RI->State->SetMaterial(RI, (UObject *)RenderBspStencil_FinalBlend, 0);

        if (SceneNode->StencilRef)
            RI->SetStencilOp(CF_Equal, SceneNode->StencilRef, SceneNode->StencilRef, SO_Keep, SO_Keep, SO_Replace, StencilMask);
        else
            RI->SetStencilOp(CF_LessEqual, ~StencilMask, ~StencilMask, SO_Keep, SO_Keep, SO_Replace, StencilMask);

        FVertexStream *Streams[1] = { &Model->Sections(SectionIndex).Vertices };
        RI->State->SetVertexStreams(RI, VS_FixedFunction, Streams, 1);

        FBspDynamicIndexBuffer IndexBuffer(this);
        INT BaseIndex = RI->SetDynamicIndexBuffer(&IndexBuffer, 0);
        RI->DrawPrimitive(PT_TriangleList, BaseIndex, NumTriangles, IndexBuffer.MinIndex, IndexBuffer.MaxIndex);

        RI->PopState();
    }
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

// RVA 0x150820: HBspSurf::IsA
// Retail keeps these literals in writable .data, so bind them as extern data.
extern const TCHAR HHitProxy_Name[];   // L"HHitProxy"
extern const TCHAR HBspSurf_Name[];    // L"HBspSurf"

struct HHitProxy
{
    virtual UBOOL IsA(const TCHAR *Str) const { return !_wcsicmp(HHitProxy_Name, Str); }
};

struct HBspSurf : HHitProxy
{
    virtual UBOOL IsA(const TCHAR *Str) const;
};

UBOOL HBspSurf::IsA(const TCHAR *Str) const
{
    return !_wcsicmp(HBspSurf_Name, Str) || HHitProxy::IsA(Str);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
struct FBspStencilListNode
{
    FBspStencilDrawList *Element;
    FBspStencilListNode *Next;
};
void Driver_1505e0(FBspStencilListNode *Head, FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    Escape(&GStaticRefs);
    Escape(&GZeroVector);
    Escape(&GObjTransientPkg);
    Escape(&GError);
    Escape(&GCacheId);
    Escape(&RenderBspStencil_GreyTexture_Init);
    Escape(&RenderBspStencil_GreyTexture);
    for (FBspStencilListNode *It = Head; It; It = It->Next)
        It->Element->Render(SceneNode, RI);
}
