#ifndef VERSUS_CLIENT_TYPES_H
#define VERSUS_CLIENT_TYPES_H

class UEnum;
class UEngine;
class UViewport;

class UClient : public UObject {
public:
    void StaticConstructor();

    UEngine *Engine;
    TArray<UViewport *> Viewports;
    UBOOL CaptureMouse;
    UBOOL NoLighting;
    UBOOL NoFractalAnim;
    UBOOL DecoLayers;
    UBOOL ScreenFlashes;
    UBOOL Decals;
    UBOOL Coronas;
    UBOOL Projectors;
    UBOOL ReportDynamicUploads;
    INT WindowedViewportX;
    INT WindowedViewportY;
    FLOAT MinDesiredFrameRate;
    INT FullscreenViewportX;
    INT FullscreenViewportY;
    FLOAT Brightness;
    FLOAT Contrast;
    FLOAT Gamma;
    BYTE unk_7c[0x4];
    BYTE TextureDetailWorld;
    BYTE unk_81[0x3];
    BYTE TextureDetailPlayerSkin;
    BYTE unk_85[0x3];
    BYTE TextureDetailWeaponSkin;
    BYTE unk_89[0x3];
    BYTE TextureDetailTerrain;
    BYTE unk_8d[0x3];
    BYTE TextureDetailInterface;
    BYTE unk_91[0x3];
    BYTE TextureDetailRenderMap;
    BYTE unk_95[0x3];
    BYTE TextureDetailLightmap;
    BYTE unk_99[0x7];
    UEnum *TextureDetailEnum;
};

#endif
