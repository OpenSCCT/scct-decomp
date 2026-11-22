// w4_item_0139.cpp -- Versus GUI PreDraw and Draw methods (RVA 0x15b720-0x15ba2b)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appRound(FLOAT F)
{
    return (INT)floor(F + 0.5f);
}

inline INT appFloor(FLOAT F)
{
    return (INT)floor(F);
}

struct FGuid;
struct FStateFrame;
class UClass;
class UFunction;
class UCanvas;
class UFont;
class UMaterial;

enum EName {
    NAME_None      = 0,
    GUI_OnDraw     = 0xce74,
    GUI_OnDrawText = 0xce75,
    GUI_GetFont    = 0xd19c
};

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FColor {
    BYTE B, G, R, A;
};

enum eMenuState {
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4
};

enum eTextAlign {
    TXTA_Left   = 0,
    TXTA_Center = 1,
    TXTA_Right  = 2
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const TCHAR *In);
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : (const TCHAR *)L""; }
};

class UObject;

struct FScriptDelegate {
    UObject *Object;
    FName    FunctionName;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result = 0);
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    INT          Index;
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0xc];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x4];
    UClass      *Class;
};

class UMaterial : public UObject {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual INT MaterialUSize();
    virtual INT MaterialVSize();
};

class UCanvas : public UObject {
public:
    UFont *Font;
    BYTE   unk_2c[0x10];
    FLOAT  CurX;
    FLOAT  CurY;
    FLOAT  CurZ;
    BYTE   Style;
    BYTE   unk_49[0x7];
    FColor DrawColor;
    BYTE   unk_54[0x4];
    INT    SizeX;

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileScaleBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void __cdecl DrawTextJustified(BYTE Justification, FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
                                   const TCHAR *Fmt, ...);
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

class UGUIFont : public UGUI {
public:
    UFont *eventGetFont(INT XRes);
};

class UGUIStyles : public UGUI {
public:
    BYTE            unk_2c[0x0c];
    BYTE            RStyles[6];
    BYTE            unk_3e[0x2];
    UMaterial      *Images[5];
    BYTE            ImgStyle[5];
    BYTE            unk_59[0x3];
    FColor          FontColors[5];
    FColor          ImgColors[5];
    UGUIFont       *Fonts[5];
    BYTE            unk_98[0x4c];
    BITFIELD        bFlag0 : 1;
    BITFIELD        bStyleFlag1 : 1;
    FScriptDelegate __OnDraw__Delegate;
    FScriptDelegate __OnDrawText__Delegate;

    UBOOL delegateOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    UBOOL delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height,
                             BYTE Align, const FString &Text);
    void Draw(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    void DrawText(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height,
                  BYTE Just, const TCHAR *Text);
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual FLOAT ActualWidth();
    virtual FLOAT ActualHeight();
    virtual FLOAT ActualLeft();
    virtual FLOAT ActualTop();
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

    BYTE        unk_2c[0x4];
    BYTE        MenuState;
    BYTE        unk_31[0x3];
    FString     unk_34;
    FString     unk_40;
    BYTE        unk_4c[0x10];
    BITFIELD    unk_5c_0 : 1;
    BITFIELD    unk_5c_1 : 1;
    BITFIELD    unk_5c_2 : 1;
    BITFIELD    bVisible : 1;
    BYTE        unk_60[0x4];
    FString     unk_64;
    FLOAT       WinTop;
    FLOAT       WinLeft;
    FLOAT       WinWidth;
    FLOAT       WinHeight;
    BYTE        unk_80[0x1c];
    UGUIStyles *Style;
    BYTE        unk_a0[0xf0];
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();
    virtual void PreDraw(UCanvas *Canvas);

    TArray<UGUIComponent *> Controls;
    BYTE                    unk_19c[0x4];
};

class UGUISessionInfoBox : public UGUIMultiComponent {
public:
    virtual ~UGUISessionInfoBox();
    virtual void PreDraw(UCanvas *Canvas);
};

class UGUIMOTDInfoBox : public UGUIMultiComponent {
public:
    virtual ~UGUIMOTDInfoBox();
    virtual void PreDraw(UCanvas *Canvas);
};

class UGUIButton : public UGUIComponent {
public:
    virtual ~UGUIButton();
    virtual void Draw(UCanvas *Canvas);

    BYTE    unk_190[0x4];
    FString Caption;
    BYTE    unk_1a0[0x10];
};

// UGUISessionInfoBox::PreDraw (RVA 0x15b720)
void UGUISessionInfoBox::PreDraw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    UGUIMultiComponent::PreDraw(Canvas);

    Controls(0)->WinTop    = ActualTop();
    Controls(0)->WinLeft   = ActualLeft();
    Controls(0)->WinWidth  = ActualWidth();
    Controls(0)->WinHeight = ActualHeight();

    Controls(1)->WinTop    = ActualTop();
    Controls(1)->WinLeft   = ActualLeft();
    Controls(1)->WinWidth  = ActualWidth();
    Controls(1)->WinHeight = 0.04f;
}

// UGUIMOTDInfoBox::PreDraw (RVA 0x15b7e0)
void UGUIMOTDInfoBox::PreDraw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    UGUIMultiComponent::PreDraw(Canvas);

    Controls(0)->WinLeft   = ActualLeft();
    Controls(0)->WinTop    = ActualTop();
    Controls(0)->WinWidth  = ActualWidth();
    Controls(0)->WinHeight = ActualHeight();

    Controls(1)->WinLeft   = ActualLeft();
    Controls(1)->WinTop    = ActualTop();
    Controls(1)->WinWidth  = ActualWidth();
    Controls(1)->WinHeight = 0.04f;

    Controls(2)->WinLeft   = ActualLeft() + 2.0f;
    Controls(2)->WinTop    = ActualTop() + Controls(1)->ActualHeight() + 2.0f;
    Controls(2)->WinWidth  = ActualWidth() - 4.0f;
    Controls(2)->WinHeight = ActualHeight() - Controls(1)->ActualHeight() - 4.0f;
}

// UGUIButton::Draw (RVA 0x15b930)
void UGUIButton::Draw(UCanvas *Canvas)
{
    if (!bVisible || !Style)
        return;

    UGUIComponent::Draw(Canvas);

    if (MenuState == MSAT_Watched || MenuState == MSAT_Focused)
        Style->Draw(Canvas, MSAT_Blurry, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());
    else
        Style->Draw(Canvas, MenuState, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());

    Style->DrawText(Canvas, MenuState, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight(),
                    TXTA_Center, *Caption);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void ExtPrepare(UCanvas *, UMaterial *);
void ExtTile(UCanvas *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);

struct UGUIFont_eventGetFont_Parms {
    INT    XRes;
    UFont *ReturnValue;
};

struct UGUIStyles_eventOnDraw_Parms {
    UCanvas *Canvas;
    BYTE     MenuState;
    FLOAT    Left;
    FLOAT    Top;
    FLOAT    Width;
    FLOAT    Height;
    UBOOL    ReturnValue;
};

struct UGUIStyles_eventOnDrawText_Parms {
    UCanvas *Canvas;
    BYTE     MenuState;
    FLOAT    Left;
    FLOAT    Top;
    FLOAT    Width;
    FLOAT    Height;
    BYTE     Align;
    FString  Text;
    UBOOL    ReturnValue;
};

#pragma auto_inline(off)
void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color)
{
    ExtPrepare(this, Material);
    ExtTile(this, X, Y, XL, YL, U, V, UL, VL, Z, Color);
    ExtPrepare(this, 0);
}

void UCanvas::DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight)
{
    CurX = Left;
    CurY = Top;
    if (!Mat || !Style)
        return;

    FLOAT mW = (FLOAT)Mat->MaterialUSize();
    FLOAT mH = (FLOAT)Mat->MaterialVSize();
    FLOAT MidX = (FLOAT)appFloor(mW * 0.5f);
    FLOAT MidY = (FLOAT)appFloor(mH * 0.5f);
    FLOAT SmallTileW = AWidth - mW;
    FLOAT SmallTileH = AHeight - mH;
    FLOAT fX, fY;

    if (mW < AWidth) {
        fX = MidX;
        if (mH > AHeight)
            fY = AHeight * 0.5f;
        else
            fY = MidY;
        DrawTile(Mat, CurX + fX, CurY, SmallTileW, fY, fX, 0, 1.f, fY, 0, DrawColor);
        DrawTile(Mat, CurX + fX, CurY + AHeight - fY, SmallTileW, fY, fX, mH - fY, 1.f, fY, 0, DrawColor);
    } else
        fX = AWidth * 0.5f;

    if (mH < AHeight) {
        fY = MidY;
        DrawTile(Mat, CurX, CurY + fY, fX, SmallTileH, 0, fY, fX, 1.f, 0, DrawColor);
        DrawTile(Mat, CurX + AWidth - fX, CurY + fY, fX, SmallTileH, mW - fX, fY, fX, 1.f, 0, DrawColor);
    } else
        fY = AHeight * 0.5f;

    if (mH < AHeight && mW < AWidth)
        DrawTile(Mat, CurX + fX, CurY + fY, SmallTileW, SmallTileH, fX, fY, 1.f, 1.f, 0, DrawColor);

    DrawTile(Mat, CurX, CurY, fX, fY, 0, 0, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX + AWidth - fX, CurY, fX, fY, mW - fX, 0, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX, CurY + AHeight - fY, fX, fY, 0, mH - fY, fX, fY, 0, DrawColor);
    DrawTile(Mat, CurX + AWidth - fX, CurY + AHeight - fY, fX, fY, mW - fX, mH - fY, fX, fY, 0, DrawColor);
}

void UCanvas::DrawTileScaleBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style) {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}

UFont *UGUIFont::eventGetFont(INT XRes)
{
    UGUIFont_eventGetFont_Parms Parms;
    Parms.XRes = XRes;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunctionChecked(GUI_GetFont), &Parms);
    return Parms.ReturnValue;
}

UBOOL UGUIStyles::delegateOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    UGUIStyles_eventOnDraw_Parms Parms;
    Parms.Canvas = Canvas;
    Parms.MenuState = MenuState;
    Parms.Left = Left;
    Parms.Top = Top;
    Parms.Width = Width;
    Parms.Height = Height;
    Parms.ReturnValue = 0;
    ProcessDelegate(GUI_OnDraw, &__OnDraw__Delegate, &Parms);
    return Parms.ReturnValue;
}

UBOOL UGUIStyles::delegateOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height,
                                     BYTE Align, const FString &Text)
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
    ProcessDelegate(GUI_OnDrawText, &__OnDrawText__Delegate, &Parms);
    return Parms.ReturnValue;
}

void UGUIStyles::Draw(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (State > 5)
        return;
    if (delegateOnDraw(Canvas, State, Left, Top, Width, Height))
        return;
    if (!Images[State])
        return;

    FColor Color;
    Color.A = 255;
    if (State == 4) {
        Color.R = Color.G = Color.B = 64;
    } else {
        Color.R = Color.G = Color.B = 128;
    }
    Canvas->DrawColor = Color;

    UMaterial *Img = Images[State];
    if (!Img)
        return;
    FLOAT mW = (FLOAT)Img->MaterialUSize();
    FLOAT mH = (FLOAT)Img->MaterialVSize();
    Canvas->Style = RStyles[State];
    Canvas->DrawColor = ImgColors[State];
    switch (ImgStyle[State]) {
    case 0: {
        FColor C;
        C.B = C.G = C.R = 128;
        C.A = 255;
        Canvas->DrawTile(Img, Left, Top, mW, mH, 0.0f, 0.0f, mW, mH, 0.0f, C);
        break;
    }
    case 1:
        Canvas->DrawTileStretched(Img, Left, Top, Width, Height);
        break;
    case 2:
        Canvas->DrawTileScaleBound(Img, Left, Top, Width, Height);
        break;
    }
}

void UGUIStyles::DrawText(UCanvas *Canvas, BYTE State, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height,
                          BYTE Just, const TCHAR *Text)
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

    if (bStyleFlag1)
        Just += 10;

    if (Canvas->Font)
        Canvas->DrawTextJustified(Just, Left, Top, Left + Width, Top + Height, Text);

    Canvas->Style = OldStyle;
    Canvas->DrawColor = OldColor;
    Canvas->Font = OldFont;
}
#pragma auto_inline(on)

void Driver_15b930()
{
    UGUIButton Btn;
    Escape(&Btn);
}
