#ifndef VERSUS_RENDER_INTERFACE_H
#define VERSUS_RENDER_INTERFACE_H

struct FColor;
class FRenderTarget;

class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual UBOOL SetRenderTarget(FRenderTarget *RenderTarget);
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height); // +0x0c
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth,
                       UBOOL UseStencil, DWORD Stencil);           // +0x10
    virtual void PushHit(const BYTE *Data, INT Count); virtual void PopHit(INT Count, UBOOL Force); virtual void SetCullMode(INT Mode);
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void SetSectionLights(struct FDynamicLightList *Lights); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual void Slot60(); virtual void DrawPrimitive(INT Type, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); virtual void Slot68(); virtual void Slot6c();
    virtual void Slot70(); virtual void Slot74();
    virtual void UpdateEffects();                                  // +0x78
    virtual void Slot7c();
    virtual void Effect80(INT SizeX, INT SizeY);                   // +0x80
    virtual void Effect84(INT SizeX, INT SizeY, FLOAT Amount);     // +0x84
    virtual void BeginFade(INT SizeX, INT SizeY);                  // +0x88
    virtual void BeginFlash(INT SizeX, INT SizeY);                 // +0x8c
    virtual void Effect90(INT SizeX, INT SizeY, class UTexture *Texture);     // +0x90
    virtual void Effect94(INT SizeX, INT SizeY, class UTexture *Texture);     // +0x94
    virtual void Effect98();                                       // +0x98
    INT  Fading;                                                   // +0x04
    INT  Flashing;                                                 // +0x08
    BYTE EffectAlpha;                                              // +0x0c
    BYTE unk_d[0x10 - 0xd];
    INT CurrentPass;
    class FRenderTransformTarget *TransformTarget;
};

#endif
