#include "versus_build.h"
#include "versus_canvas.h"
#include "versus_canvas_font.h"
#include "versus_canvas_util.h"
#include "versus_canvas_viewport.h"
#include <stdarg.h>

extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *Dest, unsigned int Count,
    const TCHAR *Format, va_list Args);

#define FORMAT_TEXT(Buffer, Format) \
    va_list Args; \
    va_start(Args, Format); \
    _vsnwprintf(Buffer, sizeof(Buffer) / sizeof(Buffer[0]), Format, Args); \
    va_end(Args)

void UCanvas::WrappedStrLenf(UFont *InFont, INT &XL, INT &YL, const TCHAR *Format, ...)
{
    TCHAR Text[4096];
    FORMAT_TEXT(Text, Format);
    WrappedPrint(0, XL, YL, InFont, 1.f, 1.f, 0, Text);
}

void UCanvas::WrappedPrintf(UFont *InFont, DWORD Centered, const TCHAR *Format, ...)
{
    TCHAR Text[4096];
    FORMAT_TEXT(Text, Format);
    INT XL = 0, YL = 0;
    WrappedPrint(1, XL, YL, InFont, 1.f, 1.f, Centered, Text);
}

void UCanvas::WrappedPrintf(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, DWORD Centered, const TCHAR *Format, ...)
{
    TCHAR Text[4096];
    FORMAT_TEXT(Text, Format);
    INT XL = 0, YL = 0;
    WrappedPrint(1, XL, YL, InFont, ScaleX, ScaleY, Centered, Text);
}

void UCanvas::WrappedPrint(UBOOL Draw, INT &XL, INT &YL, UFont *InFont, FLOAT ScaleX,
    FLOAT ScaleY, UBOOL Centered, TCHAR *Text)
{
    if (ClipX < 0.f || ClipY < 0.f)
        return;
    XL = YL = 0;
    do {
        INT Break = 0;
        INT StartX = (INT)CurX;
        INT LineWidth = StartX, WidthAtBreak = 0;
        INT LineHeight = 0, HeightAtBreak = 0;
        UBOOL FoundWord = 0;
        for (INT i = 0; Text[i] && Text[i] != '\n'; ) {
            INT Width, Height;
            InFont->GetCharSize(Text[i], Width, Height);
            LineWidth += (INT)((Width + InFont->Kerning) * ScaleX);
            INT ScaledHeight = (INT)(Height * ScaleY);
            if (LineHeight < ScaledHeight)
                LineHeight = ScaledHeight;
            if (LineWidth > ClipX)
                break;
            ++i;
            UBOOL AtBoundary = Text[i] == ' ' || Text[i] == '\n' || !Text[i];
            if (AtBoundary || !FoundWord) {
                Break = i;
                WidthAtBreak = LineWidth;
                HeightAtBreak = LineHeight;
                FoundWord = FoundWord || AtBoundary;
            }
        }
        if (Break == 0)
            break;
        if (Draw && OrgY + CurY < Viewport->SizeY && OrgY + CurY + HeightAtBreak > 0.f) {
            INT X = Centered ? (INT)(CurX + (ClipX - WidthAtBreak) * 0.5f) : StartX;
            TCHAR Last = Text[Break];
            Text[Break] = 0;
            X += DrawGlyphLine(InFont, ScaleX, ScaleY, X, (INT)CurY, Text, 0);
            Text[Break] = Last;
            CurX = (FLOAT)X;
        }
        CurX = 0.f;
        CurY += HeightAtBreak;
        YL += HeightAtBreak;
        XL = XL >= WidthAtBreak ? XL : WidthAtBreak;
        Text += Break;
        while (*Text == ' ')
            ++Text;
    } while (*Text);
}

extern "C" __declspec(dllimport) DOUBLE __cdecl floor(DOUBLE Value);

static INT RoundCanvasPixel(FLOAT Value)
{
    return (INT)floor(Value + 0.5f);
}

static FLOAT RoundCanvasExtent(FLOAT Value)
{
    return (FLOAT)floor(Value + 0.5f);
}

static inline void DrawGlyphTile(UCanvas *Canvas, UMaterial *Texture, FLOAT X, FLOAT Y,
                                         FLOAT ScreenWidth, FLOAT ScreenHeight, FLOAT U, FLOAT V,
                                         FLOAT TextureWidth, FLOAT TextureHeight)
{
    FLOAT Left = (FLOAT)RoundCanvasPixel(X);
    FLOAT Top = (FLOAT)RoundCanvasPixel(Y);
    FLOAT Width = RoundCanvasExtent(ScreenWidth);
    FLOAT Height = RoundCanvasExtent(ScreenHeight);
    FLOAT StartU = (FLOAT)RoundCanvasPixel(U);
    FLOAT StartV = (FLOAT)RoundCanvasPixel(V);
    FLOAT USize = RoundCanvasExtent(TextureWidth);
    FLOAT VSize = RoundCanvasExtent(TextureHeight);

    Canvas->pCanvasUtil->DrawTile(Left, Top, Left + (INT)Width, Top + (INT)Height,
                                 StartU, StartV, StartU + (INT)USize, StartV + (INT)VSize,
                                 0.f, Canvas->GetStyleMaterial(Texture), Canvas->DrawColor);
}

// Each glyph advances the pen by its original width, even when the clip removes the tile.
INT UCanvas::DrawGlyphLine(UFont *Font, FLOAT ScaleX, FLOAT ScaleY,
                           INT X, INT Y, const TCHAR *Text, DWORD Clip)
{
    INT LineWidth = 0;
    for (INT Index = 0; Text[Index]; ++Index) {
        TCHAR Ch = Font->RemapChar(Text[Index]);
        if (Ch >= Font->Characters.ArrayNum)
            continue;
        const FFontCharacter &Glyph = static_cast<const FFontCharacter *>(Font->Characters.Data)[Ch];
        if (Glyph.TextureIndex >= Font->Textures.ArrayNum)
            continue;
        UMaterial *Texture = static_cast<UMaterial **>(Font->Textures.Data)[Glyph.TextureIndex];
        if (!Texture)
            continue;

        const INT GlyphWidth = Glyph.USize;
        INT Left = LineWidth + X, Top = Y;
        INT U = Glyph.StartU, V = Glyph.StartV;
        INT Width = GlyphWidth, Height = Glyph.VSize;
        if (!Clip || (Left + Width > 0 && Left <= ClipX
                      && Top + Height > 0 && Top <= ClipY)) {
            if (Clip) {
                if (Left < 0) {
                    U -= Left;
                    Width += Left;
                    Left = 0;
                }
                if (Top < 0) {
                    V -= Top;
                    Height += Top;
                    Top = 0;
                }
                if (Left + Width > ClipX)
                    Width = (INT)(ClipX - Left);
                if (Top + Height > ClipY)
                    Height = (INT)(ClipY - Top);
            }

            FLOAT ScreenX = OrgX + Left;
            FLOAT ScreenY = OrgY + Top;
            DrawGlyphTile(this, Texture, ScreenX, ScreenY,
                          Width * ScaleX, Height * ScaleY, (FLOAT)U, (FLOAT)V,
                          (FLOAT)Width, (FLOAT)Height);
        }
        LineWidth += (INT)((GlyphWidth + Font->Kerning) * ScaleX);
    }
    return LineWidth;
}

void UCanvas::ClippedPrint(UFont *Font, FLOAT ScaleX, FLOAT ScaleY, UBOOL Center, const TCHAR *Text)
{
    DrawGlyphLine(Font, ScaleX, ScaleY, (INT)CurX, (INT)CurY, Text, 1);
}
