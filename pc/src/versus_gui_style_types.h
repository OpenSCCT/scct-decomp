#ifndef VERSUS_GUI_STYLE_TYPES_H
#define VERSUS_GUI_STYLE_TYPES_H

class UGUIFont;

// GUI.u declares five entries for each menu state array.
class UGUIStyles : public UGUI {
public:
    FString KeyName;
    BYTE RStyles[5];
    UMaterial *Images[5];
    BYTE ImgStyle[5];
    FColor FontColors[5], ImgColors[5];
    UGUIFont *Fonts[5];
    INT BorderOffsets[4];
    FString FontNames[5];
    DWORD CatchCorners : 1;
    DWORD CheckTRCButton : 1;
    DWORD bRegistered : 1;
    FScriptDelegate __OnDraw__Delegate, __OnDrawText__Delegate;

    UBOOL delegateOnDraw(UCanvas *Canvas, BYTE State, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height);
    UBOOL delegateOnDrawText(UCanvas *Canvas, BYTE State, FLOAT X, FLOAT Y, FLOAT Width,
        FLOAT Height, BYTE Align, const FString &Text);
    void Draw(UCanvas *Canvas, BYTE State, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height);
    void DrawText(UCanvas *Canvas, BYTE State, FLOAT X, FLOAT Y, FLOAT Width,
        FLOAT Height, BYTE Align, const TCHAR *Text);
    void execDraw(FFrame &Stack, void *const Result);
    void execDrawText(FFrame &Stack, void *const Result);
};

#endif
