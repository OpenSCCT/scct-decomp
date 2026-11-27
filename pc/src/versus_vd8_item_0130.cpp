// Work item 0130: Versus RVA 0x158b50-0x158e8e
// UGUIStyles::DrawText, UGUIStyles::TextSize, UGUIComponent::PreDraw, UGUIMultiPageLabel::Draw

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appRound(FLOAT F)
{
    return (INT)floor(F + 0.5f);
}

enum EName
{
    NAME_None = 0,
    GUI_OnPreDraw = 0xce72,
    GUI_OnDrawText = 0xd196,
    GUI_GetFont = 0xd19c,
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FColor
{
    BYTE B, G, R, A;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
};

template <class T>
class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class UObject;
class UFunction;
class UFont;
class UCanvas;
class UGUIController;
class UGUIStyles;
class UGUIFont;

struct FScriptDelegate
{
    UObject *Object;
    FName FunctionName;
};

class UObject
{
public:
    virtual void VSlot0();
    virtual void VSlot1();
    virtual void VSlot2();
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result = 0);
    virtual void VSlot6();
    virtual void VSlot7();
    virtual void VSlot8();
    virtual void VSlot9();
    virtual void VSlot10();
    virtual UBOOL IsPendingKill();
    virtual void VSlot12();
    virtual void VSlot13();
    virtual void VSlot14();
    virtual void VSlot15();
    virtual void VSlot16();
    virtual void VSlot17();
    virtual void VSlot18();
    virtual void VSlot19();
    virtual void VSlot20();
    virtual void VSlot21();

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    BYTE unk_04[0x24];
};

class UViewport
{
public:
    BYTE unk_00[0xa0];
    INT SizeX;
    INT SizeY;
};

class UClient
{
public:
    BYTE unk_00[0x2c];
    TArray<UViewport *> Viewports;
};

class UInteractionMaster
{
public:
    BYTE unk_00[0x28];
    UClient *Client;
};

class UGUIController
{
public:
    BYTE unk_00[0x30];
    UInteractionMaster *Master;
};

class UCanvas : public UObject
{
public:
    UFont *Font;               // +0x28
    BYTE unk_2c[0x10];
    FLOAT CurX;                // +0x3c
    FLOAT CurY;                // +0x40
    FLOAT CurZ;                // +0x44
    BYTE Style;                // +0x48
    BYTE unk_49[0x7];
    FColor DrawColor;          // +0x50
    BYTE unk_54[0x4];
    INT SizeX;                 // +0x58

    void StrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL, const TCHAR *Text);
    void __cdecl DrawTextJustified(BYTE Justification, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, const TCHAR *Fmt, ...);
};

class UGUI : public UObject
{
public:
    UGUIController *Controller; // +0x28
};

struct UGUIFont_eventGetFont_Parms
{
    INT XRes;
    UFont *ReturnValue;
};

class UGUIFont : public UGUI
{
public:
    UFont *eventGetFont(INT XRes);
};

// Real body of UGUIFont::eventGetFont (RVA 0x1644d0) so LTCG sees its custom
// calling convention (this in ESI, XRes in EAX) when kept out of line.
UFont *UGUIFont::eventGetFont(INT XRes)
{
    UGUIFont_eventGetFont_Parms Parms;
    Parms.XRes = XRes;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunctionChecked(GUI_GetFont), &Parms);
    return Parms.ReturnValue;
}

class UGUIStyles : public UGUI
{
public:
    BYTE unk_2c[0x0c];
    BYTE RStyles[6];            // +0x38
    BYTE unk_3e[0x5c - 0x3e];
    FColor FontColors[6];       // +0x5c
    BYTE unk_74[0x84 - 0x74];
    UGUIFont *Fonts[6];         // +0x84
    BYTE unk_9c[0xe4 - 0x9c];
    UBOOL unk_e4_bit0 : 1;      // +0xe4 bit 0
    UBOOL unk_e4_bit1 : 1;      // +0xe4 bit 1
    BYTE unk_e8[0xf0 - 0xe8];
    FScriptDelegate __OnDrawText__Delegate; // +0xf0

    UBOOL delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Align, const FString &Text);
    void DrawText(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Just, const TCHAR *Text);
    void TextSize(UCanvas *Canvas, BYTE State, const TCHAR *Test, INT &XL, INT &YL);
};

struct UGUIComponent_eventOnPreDraw_Parms
{
    UCanvas *Canvas;
    UBOOL ReturnValue;
};

class UGUIComponent : public UGUI
{
public:
    virtual void PreDraw(UCanvas *Canvas);   // slot 22 (+0x58)
    virtual void Draw(UCanvas *Canvas);      // slot 23 (+0x5c)
    virtual void VSlot24();                  // slot 24 (+0x60)
    virtual void UpdateBounds();             // slot 25 (+0x64)
    virtual FLOAT ActualWidth();             // slot 26 (+0x68)
    virtual FLOAT ActualHeight();            // slot 27 (+0x6c)
    virtual FLOAT ActualLeft();              // slot 28 (+0x70)
    virtual FLOAT ActualTop();               // slot 29 (+0x74)

    UGUIComponent *MenuOwner;                // +0x2c
    BYTE MenuState;                          // +0x30
    BYTE unk_31[0x5c - 0x31];
    UBOOL bBoundToParent : 1;                // +0x5c bit 0
    UBOOL bScaleToParent : 1;                // +0x5c bit 1
    UBOOL unk_5c_bit2 : 1;                   // +0x5c bit 2
    UBOOL bVisible : 1;                      // +0x5c bit 3
    BYTE unk_60[0x9c - 0x60];
    UGUIStyles *Style;                       // +0x9c
    BYTE unk_a0[0xe8 - 0xa0];
    FScriptDelegate __OnPreDraw__Delegate;   // +0xe8

    UBOOL delegateOnPreDraw(UCanvas *Canvas)
    {
        UGUIComponent_eventOnPreDraw_Parms Parms;
        Parms.ReturnValue = 0;
        Parms.Canvas = Canvas;
        ProcessDelegate(GUI_OnPreDraw, &__OnPreDraw__Delegate, &Parms, 0);
        return Parms.ReturnValue;
    }
};

class UGUIMultiPageLabel : public UGUIComponent
{
public:
    virtual void Draw(UCanvas *Canvas);
};

extern const TCHAR Text_W[];

// 0x158b50: UGUIStyles::DrawText
void UGUIStyles::DrawText(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Just, const TCHAR *Text)
{
    BYTE OldStyle = Canvas->Style;
    FColor OldColor = Canvas->DrawColor;
    UFont *OldFont = Canvas->Font;

    Left = (FLOAT)appRound(Left);
    Top = (FLOAT)appRound(Top);
    Width = (FLOAT)appRound(Width);
    Height = (FLOAT)appRound(Height);

    if (State > 5 || !Fonts[State])
        return;

    if (delegateOnDrawText(Canvas, State, Left, Top, Width, Height, Just, Text))
        return;

    Canvas->Style = RStyles[State];
    Canvas->DrawColor = FontColors[State];
    Canvas->Font = Fonts[State]->eventGetFont(Canvas->SizeX);

    if (unk_e4_bit1)
        Just += 10;

    if (Canvas->Font)
    {
        Canvas->DrawTextJustified(Just, Left, Top, Left + Width, Top + Height, Text);
    }

    Canvas->Style = OldStyle;
    Canvas->DrawColor = OldColor;
    Canvas->Font = OldFont;
}

// 0x158d20: UGUIStyles::TextSize
void UGUIStyles::TextSize(UCanvas *Canvas, BYTE State, const TCHAR *Test, INT &XL, INT &YL)
{
    Canvas->Font = Fonts[State]->eventGetFont(Canvas->SizeX);
    if (Canvas->Font)
    {
        if (*Test == 0)
        {
            Canvas->StrLen(Canvas->Font, 1.0f, 1.0f, XL, YL, Text_W);
            XL = 0;
        }
        else
        {
            Canvas->StrLen(Canvas->Font, 1.0f, 1.0f, XL, YL, Test);
        }
    }
}

// 0x158db0: UGUIComponent::PreDraw
void UGUIComponent::PreDraw(UCanvas *Canvas)
{
    UpdateBounds();
    if (__OnPreDraw__Delegate.Object && !__OnPreDraw__Delegate.Object->IsPendingKill())
    {
        delegateOnPreDraw(Canvas);
    }
}

// 0x158e10: UGUIMultiPageLabel::Draw
void UGUIMultiPageLabel::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    Canvas->CurX = ActualLeft();
    Canvas->CurY = ActualTop();

    if (Style)
    {
        Canvas->DrawColor = Style->FontColors[MenuState];
        Canvas->Style = Style->RStyles[MenuState];
        if (Style->Fonts[MenuState])
            Canvas->Font = Style->Fonts[MenuState]->eventGetFont(Controller->Master->Client->Viewports(0)->SizeX);
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);

struct FFontCharacter
{
    INT StartU, StartV, USize, VSize;
    BYTE TextureIndex;
    BYTE unk_11[3];
};

struct FFontRemapPair
{
    INT HashNext;
    TCHAR Key;
    TCHAR Value;
};

class UFont : public UObject
{
public:
    FFontCharacter *CharactersData; // +0x28
    INT CharactersNum;              // +0x2c
    INT CharactersMax;              // +0x30
    BYTE unk_34[0x0c];
    FFontRemapPair *CharRemapPairs; // +0x40
    BYTE unk_44[0x08];
    INT *CharRemapHash;             // +0x4c
    INT CharRemapHashCount;         // +0x50
    UBOOL IsRemapped;               // +0x54
    INT Kerning;                    // +0x58
};

void UCanvas::StrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL, const TCHAR *Text)
{
    XL = 0;
    YL = 0;
    if (!InFont)
    {
        InFont = Font;
        if (!InFont)
            return;
    }
    if (!*Text)
        return;
    for (const TCHAR *P = Text; *P; ++P)
    {
        TCHAR Ch = *P;
        if (InFont->IsRemapped)
        {
            INT Idx = InFont->CharRemapHash[Ch & (InFont->CharRemapHashCount - 1)];
            TCHAR *Found = 0;
            while (Idx != -1)
            {
                if (InFont->CharRemapPairs[Idx].Key == Ch)
                {
                    Found = &InFont->CharRemapPairs[Idx].Value;
                    break;
                }
                Idx = InFont->CharRemapPairs[Idx].HashNext;
            }
            Ch = Found ? *Found : 0x20;
        }
        INT W = 0, H = 0;
        if ((INT)Ch < InFont->CharactersNum)
        {
            W = InFont->CharactersData[Ch].USize;
            H = InFont->CharactersData[Ch].VSize;
        }
        if (P[1])
            W += InFont->Kerning;
        INT SW = (INT)(W * ScaleX);
        INT SH = (INT)(H * ScaleY);
        XL += SW;
        if (YL < SH)
            YL = SH;
    }
}

void Driver_158d20(UGUIStyles *S, UCanvas *C, BYTE St, const TCHAR *T, INT *XL, INT *OutY,
                   UCanvas *C2, UFont *F2, FLOAT SX, FLOAT SY, INT *XL2, INT *YL2)
{
    INT YL = 0;
    Escape(&YL);
    for (INT i = 0; i < 4; ++i)
    {
        S->TextSize(C, (BYTE)(St + i), T + i, *XL, YL);
        OutY[i] = *XL + YL;
    }
    C2->StrLen(F2, SX, SY, *XL2, *YL2, T);
    C2->StrLen(F2, SY, SX, *YL2, *XL2, T + 1);
    C2->StrLen(C2->Font, 1.0f, 1.0f, *XL2, *YL2, T + 2);
    C2->StrLen(0, 1.0f, 1.0f, *XL2, *YL2, T + 3);
}

struct UGUIStyles_eventOnDrawText_Parms
{
    UCanvas *Canvas;
    BYTE MenuState;
    FLOAT Left;
    FLOAT Top;
    FLOAT Width;
    FLOAT Height;
    BYTE Align;
    FString Text;
    UBOOL ReturnValue;
};

UBOOL UGUIStyles::delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height, BYTE Align, const FString &Text)
{
    UGUIStyles_eventOnDrawText_Parms Parms;
    Parms.Canvas = Canvas;
    Parms.MenuState = MenuState;
    Parms.Left = Left;
    Parms.Top = Top;
    Parms.Width = Width;
    Parms.Height = Height;
    Parms.Align = Align;
    Parms.Text = Text;
    Parms.ReturnValue = 0;
    ProcessDelegate(GUI_OnDrawText, &__OnDrawText__Delegate, &Parms, 0);
    return Parms.ReturnValue;
}

extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, char *);
void Sink_DrawTextJustified(UCanvas *, UFont *, BYTE, FLOAT, FLOAT, FLOAT, FLOAT, TCHAR *);

void __cdecl UCanvas::DrawTextJustified(BYTE Justification, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, const TCHAR *Fmt, ...)
{
    TCHAR TempStr[4096];
    _vsnwprintf(TempStr, 4096, Fmt, (char *)&Fmt + sizeof(Fmt));
    Sink_DrawTextJustified(this, Font, Justification, x1, y1, x2, y2, TempStr);
    Sink_DrawTextJustified(this, Font, Justification, x2, y2, x1, y1, TempStr);
}

void Driver_158b50(UGUIStyles **Styles, UCanvas *C, BYTE St, FLOAT L, FLOAT T, FLOAT W, FLOAT H, BYTE J, const TCHAR *Txt)
{
    for (INT i = 0; i < 4; ++i)
    {
        Styles[i]->DrawText(C, (BYTE)(St + i), L, T, W, H, J, Txt + i);
    }
    FString S(Txt);
    Styles[0]->delegateOnDrawText(C, St, L, T, W, H, J, S);
    C->DrawTextJustified(J, L, T, W, H, Txt);
}
