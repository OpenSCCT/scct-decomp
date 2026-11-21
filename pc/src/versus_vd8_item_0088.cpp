// Work item 0088: Versus RVA 0x14a9c0 and 0x14aba0.
// Static projector rendering and projector vertex stream construction (Engine,
// UnProjector.cpp / UnRenderUtil.cpp). Both functions are VC7.0 /GL /LTCG.
// Class and helper names follow Unreal Engine 2 conventions (UProjectorMaterial,
// FVertexStream, FIndexBuffer, FRenderInterface); unexported batch/state struct
// names (FStaticProjectorInfo, FProjectorBatchVertexStream, FRenderState,
// FStaticObjectList) are descriptive neutral names from retail layout and calls.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#define NULL 0

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(const FPlane &P) : FVector(P), W(P.W) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

enum EName { NAME_None = 0 };
struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

class FOutputDevice;
class UObject;
class UClass;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Add(INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray
{
public:
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        ((T *)Data)[Index] = Item;
        return Index;
    }
};

class UClass
{
public:
    BYTE unk_0[0x104];
    void (*ClassConstructor)(void *); // +0x104
};

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21();
    virtual void Slot22(); virtual void Slot23(); virtual void Slot24(); virtual void Slot25();
    virtual void Slot26(); virtual void Slot27(); virtual void Slot28(); virtual void Slot29();
    virtual BYTE RequiredUVStreams(); // +0x78 (slot 30)

    static UObject *StaticAllocateObject(
        UClass *Class,
        UObject *InOuter,
        FName Name,
        DWORD SetFlags,
        UObject *InTemplate,
        FOutputDevice *Error,
        UObject *SubobjectRoot,
        INT UnknownArg
    );

    static inline UObject *StaticConstructObject(
        UClass *Class,
        UObject *InOuter,
        FName Name = NAME_None,
        DWORD SetFlags = 0,
        UObject *InTemplate = NULL,
        FOutputDevice *Error = NULL,
        UObject *SubobjectRoot = NULL)
    {
        UObject *Result = StaticAllocateObject(Class, InOuter, Name, SetFlags, InTemplate, Error, SubobjectRoot, 0);
        if (Result) {
            (*Class->ClassConstructor)(Result);
        }
        return Result;
    }
};

class UMaterial : public UObject {};
class URenderedMaterial : public UMaterial {};

class UProjectorMaterial : public URenderedMaterial
{
public:
    static UClass PrivateStaticClass;

    BYTE unk_4[0xd0 - 0x04];
    UMaterial *Projected;              // +0xd0
    UMaterial *BaseMaterial;           // +0xd4
    BYTE FrameBufferBlendingOp;        // +0xd8
    BYTE MaterialBlendingOp;           // +0xd9
    BYTE unk_da[2];                    // +0xda
    BITFIELD bBit0 : 1;                // 0x01
    BITFIELD bBit1 : 1;                // 0x02
    BITFIELD bBit2 : 1;                // 0x04
    BITFIELD bBit3 : 1;                // 0x08
    BITFIELD bBit4 : 1;                // 0x10
    BITFIELD bProjected : 1;           // 0x20
    BITFIELD bFade : 1;                // 0x40
    BITFIELD bGradient : 1;            // 0x80
};

struct FStaticObjectList
{
    BYTE unk_0[0x28];
    TArray<UObject **> Pointers;       // +0x28
};

extern UObject *GObjTransientPkg;
extern FOutputDevice *GError;
extern FStaticObjectList *GStaticObjects;
extern FVector *GZeroVector;
extern UProjectorMaterial *GStaticProjectorMaterial; // local static in retail (0x10ccad0c)
extern QWORD GNextCacheID;

inline QWORD MakeCacheID(DWORD Base)
{
    return (GNextCacheID++ * 0x100) + Base;
}

struct FVertexComponent
{
    DWORD Type;
    DWORD Function;
};

class FRenderResource
{
public:
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
};

class FVertexStream : public FRenderResource
{
public:
    virtual INT GetStride();
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual INT GetComponents(FVertexComponent *Components);
    virtual void GetStreamData(void *Dest);
};

class FIndexBuffer : public FRenderResource
{
public:
    virtual INT GetSize();
    virtual void GetContents(void *Data);
};

class FRenderInterface;

class FRenderState
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10();
    virtual void SetLight(FRenderInterface *RI, INT Index, INT A, INT B, INT C, FPlane Color); // +0x14
    virtual void Slot18();
    virtual void Slot1c();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Index, FVertexStream *Stream);      // +0x20
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *Material, INT Flags);            // +0x24
};

class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54();
    virtual void SetZBias(INT ZBias);                              // +0x58
    virtual void Slot5c();
    virtual INT SetDynamicIndexBuffer(FIndexBuffer *IndexBuffer, INT BaseVertexIndex);         // +0x60
    virtual void DrawPrimitive(INT Type, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // +0x64

    BYTE unk_4[0x14 - 0x04];
    FRenderState *State;                                           // +0x14

    void SetLight(INT Index, INT A, INT B, INT C, FPlane Color)
    {
        State->SetLight(this, Index, A, B, C, Color);
    }
    void SetMaterial(UMaterial *Material, INT Flags = 0)
    {
        State->SetMaterial(this, Material, Flags);
    }
    INT SetDynamicStream(INT Index, FVertexStream *Stream)
    {
        return State->SetDynamicStream(this, Index, Stream);
    }
};

class FLevelSceneNode;

// Helper for 0x109c52d0: takes UMaterial* in EAX under LTCG (checks IsA without
// modifying globals, matching retail interprocedural side effects).
extern UClass *GBaseMaterialClass;
__declspec(noinline) UMaterial *GetBaseMaterial(UMaterial *InMaterial)
{
    if (!InMaterial)
        return NULL;
    return ((UClass *)InMaterial == GBaseMaterialClass) ? InMaterial : NULL;
}

class FStaticProjectorInfo;

class FStaticProjectorVertexStream : public FVertexStream
{
public:
    FStaticProjectorInfo *Info;        // +0x04
    INT Size;                          // +0x08
    INT Stride;                        // +0x0c

    FStaticProjectorVertexStream(FStaticProjectorInfo *InInfo);
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual INT GetComponents(FVertexComponent *Components);
    virtual void GetStreamData(void *Dest);
};

class FStaticProjectorIndexBuffer : public FIndexBuffer
{
public:
    FStaticProjectorInfo *Info;        // +0x04
    INT Size;                          // +0x08

    FStaticProjectorIndexBuffer(FStaticProjectorInfo *InInfo);
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetSize();
    virtual void GetContents(void *Data);
};

class FStaticProjectorInfo
{
public:
    BYTE unk_0[0x0c];
    UMaterial *BaseMaterial;           // +0x0c
    UMaterial *ProjectedMaterial;      // +0x10
    INT FrameBufferBlendingOp;         // +0x14
    INT MaterialBlendingOp;            // +0x18
    UBOOL bGradient;                   // +0x1c
    UBOOL bFade;                       // +0x20
    INT VertexStride;                  // +0x24
    INT VertexDataSize;                // +0x28
    DWORD IndexDataSize;               // +0x2c

    __declspec(noinline) void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI);
};

inline FStaticProjectorVertexStream::FStaticProjectorVertexStream(FStaticProjectorInfo *InInfo)
    : Info(InInfo)
    , Size(InInfo->VertexDataSize)
{
    Stride = Info->BaseMaterial ? 0x24 : 0x1c;
}

inline FStaticProjectorIndexBuffer::FStaticProjectorIndexBuffer(FStaticProjectorInfo *InInfo)
    : Info(InInfo)
    , Size((INT)InInfo->IndexDataSize)
{
}

// Retail RVA 0x14a9c0
void FStaticProjectorInfo::Render(FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    if (!GStaticProjectorMaterial) {
        GStaticProjectorMaterial = (UProjectorMaterial *)UObject::StaticConstructObject(
            &UProjectorMaterial::PrivateStaticClass,
            GObjTransientPkg,
            NAME_None,
            0,
            NULL,
            GError,
            NULL);
        GStaticObjects->Pointers.AddItem((UObject **)&GStaticProjectorMaterial);
        GStaticProjectorMaterial->bProjected = 1;
    }

    GStaticProjectorMaterial->Projected = ProjectedMaterial;
    GStaticProjectorMaterial->BaseMaterial = GetBaseMaterial(BaseMaterial);
    GStaticProjectorMaterial->FrameBufferBlendingOp = (BYTE)FrameBufferBlendingOp;
    GStaticProjectorMaterial->MaterialBlendingOp = (BYTE)MaterialBlendingOp;
    GStaticProjectorMaterial->bProjected = 1;
    GStaticProjectorMaterial->bFade = bFade;
    GStaticProjectorMaterial->bGradient = bGradient;

    RI->PushState();
    RI->SetLight(0, 1, 0, 0, FPlane(*GZeroVector, 0.0f));
    RI->SetMaterial(GStaticProjectorMaterial, 0);
    RI->SetZBias(1);

    FStaticProjectorVertexStream VertexStream(this);
    FStaticProjectorIndexBuffer IndexBuffer(this);

    INT BaseVertexIndex = RI->SetDynamicStream(0, &VertexStream);
    INT BaseIndex = RI->SetDynamicIndexBuffer(&IndexBuffer, BaseVertexIndex);
    RI->DrawPrimitive(0, BaseIndex, (INT)(IndexDataSize / 6), 0, VertexDataSize / VertexStride - 1);
    RI->PopState();
}

// Retail RVA 0x14aba0
class FProjectorBatchVertexStream : public FVertexStream
{
public:
    QWORD CacheId;      // +0x08
    INT Size;           // +0x10
    INT NumUVs;         // +0x14
    INT Stride;         // +0x18
    INT Revision;       // +0x1c

    __declspec(noinline) FProjectorBatchVertexStream(UMaterial *InMaterial);
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual INT GetComponents(FVertexComponent *Components);
    virtual void GetStreamData(void *Dest);
};

FProjectorBatchVertexStream::FProjectorBatchVertexStream(UMaterial *InMaterial)
{
    CacheId = MakeCacheID(0xe1);
    Size = 0;
    BYTE UVMask = InMaterial->RequiredUVStreams();
    BYTE Mask = 0xff;
    for (INT i = 0; i < 8; i++, Mask <<= 1) {
        if (!(UVMask & Mask)) {
            NumUVs = i;
            break;
        }
    }
    Revision = 1;
    Stride = 0x1c + NumUVs * 8;
}

// Scaffolding for the link, not part of the units.
void Escape(void *);
inline void *operator new(unsigned int, void *Ptr) { return Ptr; }

struct FProjectorListNode
{
    FStaticProjectorInfo *Info;
    FProjectorListNode *Next;
};
extern FProjectorListNode *GProjectorList;

void Driver_14a9c0(FLevelSceneNode *SceneNode, FRenderInterface *RI)
{
    Escape(&GObjTransientPkg);
    Escape(&GError);
    Escape(&GStaticObjects);
    Escape(&GZeroVector);
    for (FProjectorListNode *Node = GProjectorList; Node; Node = Node->Next) {
        Node->Info->Render(SceneNode, RI);
    }
}

FProjectorBatchVertexStream *Driver_14aba0(void *Mem, UMaterial *InMaterial)
{
    return new (Mem) FProjectorBatchVertexStream(InMaterial);
}
