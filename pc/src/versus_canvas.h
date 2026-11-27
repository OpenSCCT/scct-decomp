#ifndef VERSUS_CANVAS_H
#define VERSUS_CANVAS_H

#include "versus_build.h"
#if !defined(VERSUS_NATIVE_CLASS_TYPES_H) && !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_object.h"
#endif
#include "unreal_math.h"

class UMaterial;
class UFont;
class UViewport;
class FCanvasUtil;

// Engine.Canvas occupies 0x80 bytes in Steam Versus.
class UCanvas : public UObject {
public:
    virtual ~UCanvas();
    void Update();

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
    UFont *TinyFont, *SmallFont, *MedFont;
    FName TinyFontName, SmallFontName, MedFontName;
    UViewport *Viewport;
    FCanvasUtil *pCanvasUtil;

    void execTextSize(FFrame &Stack, void *const Result);
    void execRenderMotionTracking(FFrame &Stack, void *const Result);
    void RenderMotionTracking(INT A0, INT A1, INT A2);
    void StrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL, const TCHAR *Text);
    // Draws one line of glyphs and returns its horizontal advance.
    INT DrawGlyphLine(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT X, INT Y, const TCHAR *Text, DWORD Clip);
    UMaterial *GetStyleMaterial(UMaterial *Material);
    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
        FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
        FLOAT Z, FColor Color);
    void DrawTileStretched(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height);
    void DrawTileScaled(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height);
    void ClippedPrint(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, UBOOL Centered, const TCHAR *Text);
    void WrappedPrint(UBOOL Draw, INT &XL, INT &YL, UFont *InFont, FLOAT ScaleX,
        FLOAT ScaleY, UBOOL Centered, TCHAR *Text);
    void __cdecl WrappedStrLenf(UFont *InFont, INT &XL, INT &YL, const TCHAR *Format, ...);
    void __cdecl WrappedPrintf(UFont *InFont, DWORD Centered, const TCHAR *Format, ...);
    void __cdecl WrappedPrintf(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, DWORD Centered,
        const TCHAR *Format, ...);
};

#endif
