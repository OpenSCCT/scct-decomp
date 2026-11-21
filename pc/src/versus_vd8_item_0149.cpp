// Work item 0149: Versus RVA 0x15e9f0-0x15ef3f (UGUITabControl, UGUIMenuOption).
// Types follow versus_gui_classes.h, versus_gui_bounds.c, versus_gui_layout.c,
// and versus_vd5_item_0295.cpp.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned char BYTE;
typedef float FLOAT;

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

template<class T>
class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class FString : protected TArray<TCHAR>
{
};

enum EMenuState
{
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4,
};

enum ETextAlign
{
    TXTA_Left   = 0,
    TXTA_Center = 1,
    TXTA_Right  = 2,
};

class UMaterial
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64();
    virtual INT MaterialUSize();   // 0x68
    virtual INT MaterialVSize();   // 0x6c
};

class UObject
{
public:
    virtual ~UObject();
    virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54();

    BYTE unk_04[0x24];
};

class UCanvas : public UObject
{
public:
    BYTE unk_28[0x4];
    FLOAT OrgX;       // 0x2c
    FLOAT OrgY;       // 0x30
    FLOAT ClipX;      // 0x34
    FLOAT ClipY;      // 0x38
    FLOAT CurX;       // 0x3c
    FLOAT CurY;       // 0x40
    FLOAT Z;          // 0x44
    BYTE Style;       // 0x48
    FLOAT CurYL;      // 0x4c
    FColor DrawColor; // 0x50

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void DrawTileStretched(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTileFull(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
};

class UGUIComponent;

class UGUIController : public UObject
{
public:
    BYTE unk_28[0xd14 - 0x28];
    UGUIComponent *ActiveControl; // 0xd14
};

class UGUI : public UObject
{
public:
    virtual ~UGUI();

    UGUIController *Controller; // 0x28
};

class UGUIStyles : public UGUI
{
public:
    BYTE unk_2c[0x38 - 0x2c];
    BYTE RStyles[5];          // 0x38
    BYTE unk_3d[3];
    UMaterial *Images[5];     // 0x40
    BYTE ImgStyle[5];         // 0x54
    BYTE unk_59[0x70 - 0x59];
    FColor ImgColors[5];      // 0x70

    UBOOL OnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    void Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
};

class UGUIComponent : public UGUI
{
public:
    virtual ~UGUIComponent();
    virtual void PreDraw(UCanvas *Canvas);                          // 0x58 (22)
    virtual void Draw(UCanvas *Canvas);                             // 0x5c (23)
    virtual void Vf60();                                            // 0x60 (24)
    virtual void Vf64();                                            // 0x64 (25)
    virtual FLOAT ActualWidth();                                    // 0x68 (26)
    virtual FLOAT ActualHeight();                                   // 0x6c (27)
    virtual FLOAT ActualLeft();                                     // 0x70 (28)
    virtual FLOAT ActualTop();                                      // 0x74 (29)
    virtual void SaveCanvasState(UCanvas *Canvas);                  // 0x78 (30)
    virtual void RestoreCanvasState(UCanvas *Canvas);               // 0x7c (31)
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY); // 0x80 (32)
    virtual void Vf84();                                            // 0x84 (33)
    virtual void Vf88();                                            // 0x88 (34)
    virtual void Vf8c();                                            // 0x8c (35)
    virtual void Vf90();                                            // 0x90 (36)
    virtual void Vf94();                                            // 0x94 (37)
    virtual void Vf98();                                            // 0x98 (38)
    virtual void Vf9c();                                            // 0x9c (39)
    virtual void Vfa0();                                            // 0xa0 (40)
    virtual void Vfa4();                                            // 0xa4 (41)
    virtual void Vfa8();                                            // 0xa8 (42)
    virtual INT GetTextWidth(UCanvas *Canvas);                      // 0xac (43), guess

    UGUIComponent *MenuOwner; // 0x2c
    BYTE MenuState;           // 0x30
    FString StyleName;        // 0x34
    FString Hint;             // 0x40
    BYTE unk_4c[0x10];        // 0x4c
    BITFIELD bFocusOnWatch:1; // 0x5c bit 0
    BITFIELD bNeverFocus:1;   // 0x5c bit 1
    BITFIELD bRepeatClick:1;  // 0x5c bit 2
    BITFIELD bVisible:1;      // 0x5c bit 3
    BYTE unk_60[0x10];        // 0x60
    FLOAT WinTop;             // 0x70
    FLOAT WinLeft;            // 0x74
    FLOAT WinWidth;           // 0x78
    FLOAT WinHeight;          // 0x7c
    FLOAT CenterOffsetX;      // 0x80, guess
    BYTE unk_84[0x10c];       // 0x84
};

class UGUILabel : public UGUIComponent
{
public:
    FString Caption;          // 0x190
    BYTE unk_19c[0x10];       // 0x19c
    FString unk_1ac;          // 0x1ac
    BYTE unk_1b8[0xc];        // 0x1b8
};

class UGUIButton : public UGUIComponent
{
public:
    BYTE unk_190[0x4];        // 0x190
    FString Caption;          // 0x194
    BYTE unk_1a0[0x10];       // 0x1a0
};

class UGUIMultiComponent : public UGUIComponent
{
public:
    virtual void PreDraw(UCanvas *Canvas);
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY);

    TArray<UGUIComponent *> Controls; // 0x190
    UGUIComponent *FocusedControl;    // 0x19c
};

class UGUIPanel : public UGUIMultiComponent
{
public:
    BYTE unk_1a0[0x8];
};

class UGUITabPanel : public UGUIPanel
{
public:
    BYTE unk_1a8[0x8];
};

class UGUITabButton : public UGUIButton
{
public:
    BYTE unk_1b0[0x4];        // 0x1b0
    UGUITabPanel *MyPanel;    // 0x1b4
};

class UGUITabControl : public UGUIMultiComponent
{
public:
    typedef UGUIMultiComponent Super;

    virtual void Draw(UCanvas *Canvas);
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY);

    BYTE unk_1a0[0x4];              // 0x1a0
    TArray<UGUITabButton *> TabStack; // 0x1a4
    UGUITabButton *ActiveTab;       // 0x1b0
    FString BackgroundStyleName;    // 0x1b4
    UGUIStyles *BackgroundStyle;    // 0x1c0
    UMaterial *BackgroundImage;     // 0x1c4
    BYTE unk_1c8[0x8];              // 0x1c8
};

class UGUIMenuOption : public UGUIMultiComponent
{
public:
    typedef UGUIMultiComponent Super;

    virtual void PreDraw(UCanvas *Canvas);

    UGUILabel *MyLabel;              // 0x1a0
    UGUIComponent *MyComponent;      // 0x1a4
    BYTE unk_1a8[0x4];               // 0x1a8
    FString ComponentClassName;      // 0x1ac
    FString Caption;                 // 0x1b8
    BYTE unk_1c4[0x4];               // 0x1c4
    FString LabelFont;               // 0x1c8
    BYTE LabelJustification;         // 0x1d4
    BYTE ComponentJustification;     // 0x1d5
    FLOAT CaptionWidth;              // 0x1d8
    FLOAT ComponentWidth;            // 0x1dc
    BITFIELD bAutoSizeCaption:1;     // 0x1e0 bit 0 (0x01)
    BITFIELD unk_1e0_1:1;            // 0x1e0 bit 1 (0x02)
    BITFIELD bFlipped:1;             // 0x1e0 bit 2 (0x04)
    BITFIELD bSquare:1;              // 0x1e0 bit 3 (0x08)
    BITFIELD bVerticalLayout:1;      // 0x1e0 bit 4 (0x10)
    BITFIELD unk_1e0_5:1;            // 0x1e0 bit 5 (0x20)
    BITFIELD bCaptionBelow:1;        // 0x1e0 bit 6 (0x40), guess
};

// UGUITabControl::Draw (RVA 0x15e9f0)
void UGUITabControl::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    if (BackgroundStyle)
    {
        if (MenuState == MSAT_Focused && !FocusedControl)
            BackgroundStyle->Draw(Canvas, MenuState, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());
        else
            BackgroundStyle->Draw(Canvas, MSAT_Blurry, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());
    }

    if (BackgroundImage)
        Canvas->DrawTileFull(BackgroundImage, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());

    for (INT i = 0; i < TabStack.Num(); i++)
    {
        if (TabStack(i) != ActiveTab)
        {
            TabStack(i)->MenuState = (TabStack(i) == Controller->ActiveControl) ? MSAT_Watched : MSAT_Blurry;
            TabStack(i)->SaveCanvasState(Canvas);
            TabStack(i)->Draw(Canvas);
            TabStack(i)->RestoreCanvasState(Canvas);
        }
    }

    if (ActiveTab)
    {
        ActiveTab->MenuState = FocusedControl ? MSAT_Pressed : MSAT_Focused;
        ActiveTab->SaveCanvasState(Canvas);
        ActiveTab->Draw(Canvas);
        ActiveTab->RestoreCanvasState(Canvas);
        ActiveTab->MyPanel->Draw(Canvas);
        ActiveTab->MenuState = MenuState;
    }
}

// UGUITabControl::UnderCursor (RVA 0x15eba0)
UGUIComponent *UGUITabControl::UnderCursor(FLOAT MouseX, FLOAT MouseY)
{
    UGUIComponent *tComp;

    if (ActiveTab)
    {
        tComp = ActiveTab->UnderCursor(MouseX, MouseY);
        if (tComp)
            return tComp;
        if (ActiveTab->MyPanel)
        {
            tComp = ActiveTab->MyPanel->UnderCursor(MouseX, MouseY);
            if (tComp)
                return tComp;
        }
    }

    for (INT i = TabStack.Num(); i > 0; i--)
    {
        tComp = TabStack(i - 1)->UnderCursor(MouseX, MouseY);
        if (tComp)
            return tComp;
    }

    return Super::UnderCursor(MouseX, MouseY);
}

// UGUIMenuOption::PreDraw (RVA 0x15ec50)
void UGUIMenuOption::PreDraw(UCanvas *Canvas)
{
    Super::PreDraw(Canvas);

    if (!MyLabel || !MyComponent)
        return;

    if (bVerticalLayout)
    {
        if (CaptionWidth <= 1.0f)
            MyLabel->WinHeight = ActualHeight() * CaptionWidth;
        else
            MyLabel->WinHeight = CaptionWidth;

        MyLabel->WinTop = ActualTop();
        MyLabel->WinLeft = ActualLeft();
        MyLabel->WinWidth = ActualWidth();

        MyComponent->WinHeight = ActualHeight() - MyLabel->WinHeight;
        MyComponent->WinTop = ActualTop() + MyLabel->WinHeight;
        MyComponent->WinLeft = MyLabel->WinLeft;
        MyComponent->WinWidth = MyLabel->WinWidth;
        return;
    }

    if (CaptionWidth <= 1.0f)
        MyLabel->WinWidth = ActualWidth() * CaptionWidth;
    else
        MyLabel->WinWidth = CaptionWidth;

    MyLabel->WinHeight = ActualHeight();
    if (bCaptionBelow)
        MyLabel->WinTop = ActualTop() + ActualHeight();
    else
        MyLabel->WinTop = ActualTop();

    MyComponent->WinHeight = ActualHeight();

    if (ComponentWidth > 0.0f)
        MyComponent->WinWidth = ComponentWidth;
    else if (!bSquare)
        MyComponent->WinWidth = ActualWidth() - MyLabel->WinWidth;
    else
        MyComponent->WinWidth = MyComponent->WinHeight;

    MyComponent->WinTop = ActualTop();

    if (bFlipped)
    {
        MyLabel->WinLeft = ActualLeft() + MyComponent->WinWidth;
        if (ComponentJustification == TXTA_Left)
            MyComponent->WinLeft = ActualLeft();
        else
            MyComponent->WinLeft = MyLabel->WinLeft - MyComponent->WinWidth;

        if (ComponentJustification == TXTA_Center)
        {
            MyComponent->WinLeft = ActualLeft();
            INT TextWidth = MyComponent->GetTextWidth(Canvas);
            MyComponent->CenterOffsetX = (MyComponent->WinWidth - TextWidth) * 0.5f;
        }
    }
    else
    {
        MyLabel->WinLeft = ActualLeft();
        if (ComponentJustification == TXTA_Left)
            MyComponent->WinLeft = ActualLeft() + MyLabel->WinWidth;
        else
            MyComponent->WinLeft = ActualLeft() + ActualWidth() - MyComponent->WinWidth;

        if (ComponentJustification == TXTA_Center)
        {
            MyComponent->WinLeft = ActualLeft() + MyLabel->WinWidth;
            INT TextWidth = MyComponent->GetTextWidth(Canvas);
            MyComponent->CenterOffsetX = (MyComponent->WinWidth - TextWidth) * 0.5f;
        }
    }
}

// Scaffolding for the link, not part of the unit: stand-in bodies for the two
// LTCG callees so LINK /LTCG assigns them retail's register calling conventions.
void ExtPrepare(UCanvas *, UMaterial *);
void ExtTile(UCanvas *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);

#pragma auto_inline(off)
void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color)
{
    ExtPrepare(this, Material);
    ExtTile(this, X, Y, XL, YL, U, V, UL, VL, Z, Color);
    ExtPrepare(this, 0);
}

void UCanvas::DrawTileFull(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
    {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}

void UGUIStyles::Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (MenuState > 5)
        return;
    if (OnDraw(Canvas, MenuState, Left, Top, Width, Height))
        return;
    if (!Images[MenuState])
        return;

    FColor C;
    C.A = 255;
    if (MenuState == MSAT_Disabled)
        C.R = C.G = C.B = 64;
    else
        C.R = C.G = C.B = 128;
    Canvas->DrawColor = C;

    UMaterial *Mat = Images[MenuState];
    if (Mat)
    {
        FLOAT U = (FLOAT)Mat->MaterialUSize();
        FLOAT V = (FLOAT)Mat->MaterialVSize();
        Canvas->Style = RStyles[MenuState];
        Canvas->DrawColor = ImgColors[MenuState];
        switch (ImgStyle[MenuState])
        {
        case 0:
            {
                FColor W = { 128, 128, 128, 255 };
                Canvas->DrawTile(Mat, Left, Top, U, V, 0, 0, U, V, 0, W);
            }
            break;
        case 1:
            Canvas->DrawTileStretched(Mat, Left, Top, Width, Height);
            break;
        case 2:
            Canvas->DrawTileFull(Mat, Left, Top, Width, Height);
            break;
        }
    }
}
#pragma auto_inline(on)
