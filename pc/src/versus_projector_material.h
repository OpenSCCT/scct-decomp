#ifndef VERSUS_PROJECTOR_MATERIAL_H
#define VERSUS_PROJECTOR_MATERIAL_H

#include "versus_canvas_materials.h"
#include "versus_canvas_matrix.h"

// Engine.HeatTextureModifier: 0x5c bytes, 35 virtual functions
class UHeatTextureModifier : public UModifier {
public:
    static UClass PrivateStaticClass;
    virtual ~UHeatTextureModifier();

    BYTE unk_50[0xc];
};

// Engine.EMFTextureModifier: 0x58 bytes, 35 virtual functions
class UEMFTextureModifier : public UModifier {
public:
    static UClass PrivateStaticClass;
    virtual ~UEMFTextureModifier();

    BYTE unk_50[0x8];
};

// Engine.SpecialVisionTextureModifier: 0x60 bytes, 35 virtual functions
class USpecialVisionTextureModifier : public UModifier {
public:
    static UClass PrivateStaticClass;
    virtual ~USpecialVisionTextureModifier();

    BYTE unk_50[0x10];
};

// Engine.ProjectorMaterial: 0xe0 bytes, 35 virtual functions
class UProjectorMaterial : public URenderedMaterial {
public:
    static UClass PrivateStaticClass;
    virtual ~UProjectorMaterial();

    FMatrix Matrix;
    FMatrix GradientMatrix;
    UBitmapMaterial *Gradient;
    UMaterial *Projected;
    UMaterial *BaseMaterial;
    BYTE BaseMaterialBlending;
    BYTE FrameBufferBlending;
    DWORD bProjected : 1;
    DWORD bProjectOnUnlit : 1;
    DWORD bGradient : 1;
    DWORD bProjectOnAlpha : 1;
    DWORD bProjectOnBackfaces : 1;
    DWORD bStaticProjector : 1;
    DWORD bBorderClampMode : 1;
    DWORD bTwoSided : 1;
};

#endif
