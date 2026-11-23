// campaign_canvas.h -- UMaterial, UCanvas and UECanvas as the Campaign executable builds them
#ifndef CAMPAIGN_CANVAS_H
#define CAMPAIGN_CANVAS_H

#include "unreal_object.h"
#include "unreal_math.h"

// Engine.Material: 0x48 bytes, 53 virtual functions
class UMaterial : public UObject {
public:
    virtual ~UMaterial();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();

    BYTE     unk_28[0xc];
    UObject *unk_34;            // what DrawTile draws when it is given no source
    BYTE     unk_38[0x10];

    void DrawTile(class UCanvas *Canvas, UObject *InSource, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL,
                  FLOAT VL);
};

// Engine.Canvas: 0xa0 bytes, 45 virtual functions
class UCanvas : public UObject {
public:
    virtual ~UCanvas();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VideoStop(INT Option);        // named after execVideoStop, its caller
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void SetDrawColor(BYTE R, BYTE G, BYTE B, BYTE A);
    virtual void DrawText(const TCHAR *Text, UBOOL CR);
    virtual void TextSize(const TCHAR *Text, FLOAT *XL, FLOAT *YL);

    BYTE   unk_28[0x28];
    FLOAT  CurX, CurY;          // pen position
    BYTE   unk_58[0xc];
    FColor Color;               // draw colour
    BYTE   unk_68[0x14];
    class UViewport *Viewport;  // the viewport the canvas draws to
    BYTE   unk_80[0x20];

    DECLARE_NATIVE(execDrawText)
    DECLARE_NATIVE(execTextSize)
    DECLARE_NATIVE(execSetDrawColor)
    DECLARE_NATIVE(execVideoStop)
};

// Echelon.ECanvas: 0xb0 bytes, 45 virtual functions
class UECanvas : public UCanvas {
public:
    virtual ~UECanvas();

    BYTE unk_a0[0x10];

    void DrawLine(INT X, INT Y, INT XL, INT YL, const FColor &InColor, INT Alpha, UMaterial *Material);
    void DrawRectangle(INT X, INT Y, INT XL, INT YL, INT Thickness, const FColor &Color, INT Alpha,
                       UMaterial *Material);

    DECLARE_NATIVE(execBeginScene)
    DECLARE_NATIVE(execDrawActorPortal)
    DECLARE_NATIVE(execDrawCameraPortal)
    DECLARE_NATIVE(execCreateDepthMask)
    DECLARE_NATIVE(execDrawRectangle)
    DECLARE_NATIVE(execDrawLine)
    DECLARE_NATIVE(execViewportSizeX)
    DECLARE_NATIVE(execViewportSizeY)
};

#endif // CAMPAIGN_CANVAS_H
