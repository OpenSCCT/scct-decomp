#ifndef VERSUS_CANVAS_H
#define VERSUS_CANVAS_H

#include "versus_build.h"
#include "unreal_object.h"
#include "unreal_math.h"

class UMaterial;
class UFont;
class UViewport;
class FCanvasUtil;

// Engine.Canvas occupies 0x80 bytes in Steam Versus.
class UCanvas : public UObject {
public:
    virtual ~UCanvas();

    UFont *Font;
    FLOAT OrgX, OrgY;
    FLOAT ClipX, ClipY;
    FLOAT CurX, CurY;
    FLOAT Z;
    BYTE Style;
    FLOAT CurYL;
    FColor DrawColor;
    BYTE unk_54[4];
    INT SizeX, SizeY;
    BYTE unk_60[0x78 - 0x60];
    UViewport *Viewport;
    FCanvasUtil *pCanvasUtil;

    DECLARE_NATIVE(execRenderMotionTracking)
    void RenderMotionTracking(INT A0, INT A1, INT A2);
    void StrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL, const TCHAR *Text);
    // Draws one line of glyphs and returns its horizontal advance.
    INT DrawGlyphLine(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT X, INT Y, const TCHAR *Text, DWORD Clip);
    UMaterial *GetStyleMaterial(UMaterial *Material);
    void ClippedPrint(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, UBOOL Centered, const TCHAR *Text);
    void WrappedPrint(UBOOL Draw, INT &XL, INT &YL, UFont *InFont, FLOAT ScaleX,
        FLOAT ScaleY, UBOOL Centered, TCHAR *Text);
    void __cdecl WrappedStrLenf(UFont *InFont, INT &XL, INT &YL, const TCHAR *Format, ...);
    void __cdecl WrappedPrintf(UFont *InFont, DWORD Centered, const TCHAR *Format, ...);
    void __cdecl WrappedPrintf(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, DWORD Centered,
        const TCHAR *Format, ...);
};

#endif
