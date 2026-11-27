#include "versus_build.h"
#include "versus_canvas.h"
#include "versus_canvas_font.h"
#include "versus_arrays.h"
#include "unreal_script.h"

void UCanvas::StrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL, const TCHAR *Text)
{
    XL = 0;
    YL = 0;
    if (!InFont) {
        InFont = Font;
        if (!InFont)
            return;
    }

    for (INT i = 0; Text[i]; ++i) {
        INT Width, Height;
        InFont->GetCharSize(Text[i], Width, Height);
        INT ScaledWidth;
        if (Text[i + 1])
            ScaledWidth = (INT)((Width + InFont->Kerning) * ScaleX);
        else
            ScaledWidth = (INT)(Width * ScaleX);
        INT ScaledHeight = (INT)(Height * ScaleY);
        XL += ScaledWidth;
        if (YL < ScaledHeight)
            YL = ScaledHeight;
    }
}

static FLOAT *ReadTextSizeOutput(FFrame &Stack, FLOAT &Temporary)
{
    GPropAddr = 0;
    Stack.Step(Stack.Object, &Temporary);
    if (GPropObject)
        GPropObject->NetDirty(GProperty);
    return GPropAddr ? (FLOAT *)GPropAddr : &Temporary;
}

void UCanvas::execTextSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    FLOAT TempX = 0.0f;
    FLOAT *XL = ReadTextSizeOutput(Stack, TempX);
    FLOAT TempY = 0.0f;
    FLOAT *YL = ReadTextSizeOutput(Stack, TempY);
    P_FINISH;
    if (!Font) {
        Stack.Logf(L"TextSize: No font");
        return;
    }

    INT Width, Height;
    const TCHAR *Characters = Text.ArrayNum ? static_cast<const TCHAR *>(Text.Data) : L"";
    StrLen(Font, 1.f, 1.f, Width, Height, Characters);
    *XL = (FLOAT)Width;
    *YL = (FLOAT)Height;
}
