#ifndef VERSUS_CANVAS_MATERIALS_H
#define VERSUS_CANVAS_MATERIALS_H
#include "versus_material.h"
#include "versus_texture_format.h"
#ifndef UNREAL_CONTAINERS_H
#include "versus_arrays.h"
#endif

class FRenderResource;
class UViewport;
struct FMipmap;
struct FColor;

// Engine.RenderedMaterial: 0x4c bytes, 35 virtual functions
class URenderedMaterial : public UMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~URenderedMaterial();
};

// Engine.BitmapMaterial: 0x64 bytes, 37 virtual functions
class UBitmapMaterial : public URenderedMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~UBitmapMaterial();
    virtual FRenderResource *GetRenderInterface();
    virtual UBitmapMaterial *Get(DOUBLE Time, UViewport *Viewport);

    INT USize, VSize;
    INT UClamp, VClamp;
    BYTE Format, UClampMode, VClampMode;
    BYTE unk_5f[5];
};

// Engine.Texture: 0xc0 bytes, 46 virtual functions
class UTexture : public UBitmapMaterial {
public:
    static UClass PrivateStaticClass;
    UTexture();
    virtual ~UTexture();
    ETextureFormat ConvertDXT(INT MipIndex, UBOOL NoDXT1, UBOOL NoData, BYTE **Dest);
    virtual void ClearColor(FColor Color);
    virtual void Clear(DWORD ClearFlags);
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();

    BYTE unk_64[0xc];
    TArray<FMipmap> Mips;
    BYTE unk_7c[0xb4 - 0x7c];
    DWORD : 4;
    DWORD bParametric : 1;
    DWORD bRealtimeChanged : 1;
    DWORD : 26;
    BYTE unk_b8[8];
};

// Engine.Shader: 0x74 bytes, 35 virtual functions
class UShader : public URenderedMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~UShader();

    BYTE unk_4c[0x28];
};

// Engine.LitSpecularMaterial: 0x64 bytes, 35 virtual functions
class ULitSpecularMaterial : public URenderedMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~ULitSpecularMaterial();

    BYTE unk_4c[0x18];
};

// Engine.Combiner: 0x60 bytes, 35 virtual functions
class UCombiner : public UMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~UCombiner();

    BYTE unk_4c[0x14];
};

// Engine.Modifier: 0x50 bytes, 35 virtual functions
class UModifier : public UMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~UModifier();

    UMaterial *Material;
};

// Engine.FinalBlend: 0x5c bytes, 35 virtual functions
class UFinalBlend : public UModifier {
public:
    static UClass PrivateStaticClass;
    virtual ~UFinalBlend();

    BYTE FrameBufferBlending;
    DWORD ZWrite : 1;
    DWORD ZTest : 1;
    DWORD AlphaTest : 1;
    DWORD TwoSided : 1;
    BYTE AlphaRef;
};

#endif
