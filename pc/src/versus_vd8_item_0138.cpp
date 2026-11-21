// Work item 0138: Versus RVA 0x15b170-0x15b71e
// - 0x15b170: UGUILabelPad::Draw(UCanvas *)          (vtable UGUILabelPad[23])
// - 0x15b280: UGUICadre::Draw(UCanvas *)             (vtable UGUICadre[23], UGUIHorzScrollZone[23])
// - 0x15b2f0: UGUISearchFilterBox::PreDraw(UCanvas *) (vtable UGUISearchFilterBox[22])

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);
inline INT appFloor(FLOAT F) { return (INT)floor(F); }

struct FColor
{
    BYTE B, G, R, A;
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;

    T &operator()(INT i) { return Data[i]; }
    const T &operator()(INT i) const { return Data[i]; }
};

class UObject
{
public:
    virtual ~UObject();
    virtual void V01();
    virtual void V02();
    virtual void V03();
    virtual void V04();
    virtual void V05();
    virtual void V06();
    virtual void V07();
    virtual void V08();
    virtual void V09();
    virtual void V10();
    virtual void V11();
    virtual void V12();
    virtual void V13();
    virtual void V14();
    virtual void V15();
    virtual void V16();
    virtual void V17();
    virtual void V18();
    virtual void V19();
    virtual void V20();
    virtual void V21();

    BYTE unk_04[0x24];
};

class UMaterial : public UObject
{
public:
    virtual void V22();
    virtual void V23();
    virtual void V24();
    virtual void V25();
    virtual INT MaterialUSize(); // +0x68
    virtual INT MaterialVSize(); // +0x6c
};

class UCanvas : public UObject
{
public:
    BYTE unk_28[0x0c];
    FLOAT ClipX;    // 0x34
    FLOAT ClipY;    // 0x38
    FLOAT CurX;     // 0x3c
    FLOAT CurY;     // 0x40
    FLOAT CurZ;     // 0x44
    BYTE Style;     // 0x48
    BYTE unk_49[7];
    FColor Color;   // 0x50

    void DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor InColor);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
};

class UGUIController : public UObject
{
public:
    BYTE unk_28[0xc0c];
    UMaterial *PadBackgroundMat; // 0xc34
    BYTE unk_c38[0x1d4];
    UMaterial *PadBorderMat;     // 0xe0c
};

class UGUI : public UObject
{
public:
    UGUIController *Controller; // 0x28
};

class UGUIStyles : public UGUI
{
public:
    BYTE unk_2c[0x0c];
    BYTE RStyles[5];      // 0x38
    BYTE unk_3d[3];
    UMaterial *Images[5]; // 0x40
    BYTE ImgStyle[5];     // 0x54
    BYTE unk_59[0x17];
    FColor ImgColors[5];  // 0x70

    UBOOL eventOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    void Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
};

class UGUIComponent : public UGUI
{
public:
    virtual void PreDraw(UCanvas *Canvas); // slot 22 (+0x58)
    virtual void Draw(UCanvas *Canvas);    // slot 23 (+0x5c)
    virtual void V24();                    // slot 24 (+0x60)
    virtual void V25();                    // slot 25 (+0x64)
    virtual FLOAT ActualWidth();           // slot 26 (+0x68)
    virtual FLOAT ActualHeight();          // slot 27 (+0x6c)
    virtual FLOAT ActualLeft();            // slot 28 (+0x70)
    virtual FLOAT ActualTop();             // slot 29 (+0x74)

    UGUIComponent *MenuOwner; // 0x2c
    BYTE MenuState;           // 0x30
    BYTE unk_31[0x2b];
    BITFIELD unk_5c_0 : 3;    // 0x5c bits 0..2
    BITFIELD bVisible : 1;    // 0x5c bit 3 (0x08)
    BYTE unk_60[0x10];
    FLOAT WinTop;             // 0x70
    FLOAT WinLeft;            // 0x74
    FLOAT WinWidth;           // 0x78
    FLOAT WinHeight;          // 0x7c
    BYTE unk_80[0x1c];
    UGUIStyles *Style;        // 0x9c
    FLOAT Bounds[4];          // 0xa0
    FLOAT ClientBounds[4];    // 0xb0
    BYTE unk_c0[0xd0];
};

class UGUILabel : public UGUIComponent
{
public:
    virtual void Draw(UCanvas *Canvas);

    BYTE unk_190[0x2c];
    FColor BackColor; // 0x1bc
    BYTE unk_1c0[0x4];
};

class UGUILabelPad : public UGUILabel
{
public:
    virtual void Draw(UCanvas *Canvas);

    BITFIELD bPadBorder : 1;     // 0x1c4 bit 0 (0x01)
    BITFIELD bPadBackground : 1; // 0x1c4 bit 1 (0x02)
};

class UGUICadre : public UGUIComponent
{
public:
    virtual void Draw(UCanvas *Canvas);
};

class UGUIMultiComponent : public UGUIComponent
{
public:
    virtual void PreDraw(UCanvas *Canvas);

    TArray<UGUIComponent *> Controls; // 0x190
    UGUIComponent *FocusedControl;    // 0x19c
};

class UGUISearchFilterBox : public UGUIMultiComponent
{
public:
    virtual void PreDraw(UCanvas *Canvas);
};

// RVA 0x15b170
void UGUILabelPad::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    if (bPadBackground) {
        BYTE OldStyle = Canvas->Style;
        Canvas->Style = 5;
        Canvas->DrawTile(
            Controller->PadBackgroundMat,
            ClientBounds[0] - 4.f,
            ClientBounds[1] - 2.f,
            ClientBounds[2] - ClientBounds[0] + 8.f,
            ClientBounds[3] - ClientBounds[1] + 4.f,
            0.f, 0.f, 32.f, 32.f, 0.f,
            BackColor
        );
        Canvas->Style = OldStyle;
    }

    if (bPadBorder) {
        Canvas->DrawTileStretched(
            Controller->PadBorderMat,
            ClientBounds[0] - 4.f,
            ClientBounds[1] - 2.f,
            ClientBounds[2] - ClientBounds[0] + 8.f,
            ClientBounds[3] - ClientBounds[1] + 4.f
        );
    }

    UGUILabel::Draw(Canvas);
}

// RVA 0x15b280
void UGUICadre::Draw(UCanvas *Canvas)
{
    if (!bVisible || !Style)
        return;

    UGUIComponent::Draw(Canvas);
    Style->Draw(Canvas, MenuState, ActualLeft(), ActualTop(), ActualWidth(), ActualHeight());
}

// RVA 0x15b2f0
void UGUISearchFilterBox::PreDraw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    UGUIMultiComponent::PreDraw(Canvas);

    Controls(2)->WinTop = ActualTop();
    Controls(2)->WinLeft = ActualLeft();
    Controls(2)->WinWidth = ActualWidth();
    Controls(2)->WinHeight = 0.04f;

    Controls(3)->WinLeft = ActualLeft() + 3.f;
    Controls(4)->WinLeft = ActualLeft() + 3.f;
    Controls(5)->WinLeft = ActualLeft() + 3.f;
    Controls(12)->WinLeft = ActualLeft() + 3.f;
    Controls(11)->WinLeft = ActualLeft() + 3.f;

    Controls(3)->WinWidth = ActualWidth();
    Controls(4)->WinWidth = ActualWidth();
    Controls(5)->WinWidth = ActualWidth();
    Controls(12)->WinWidth = ActualWidth();
    Controls(11)->WinWidth = ActualWidth();

    Controls(3)->WinTop = Controls(2)->ActualHeight() + Controls(2)->ActualTop() + 1.f;
    Controls(4)->WinTop = Controls(3)->ActualTop() + Controls(3)->ActualHeight();
    Controls(5)->WinTop = Controls(4)->ActualTop() + Controls(4)->ActualHeight();
    Controls(12)->WinTop = Controls(5)->ActualTop() + Controls(5)->ActualHeight();
    Controls(11)->WinTop = Controls(12)->ActualTop() + Controls(12)->ActualHeight();

    Controls(0)->WinTop = Controls(2)->WinTop - (2.f / 480.f);
    Controls(0)->WinLeft = Controls(2)->WinLeft;
    Controls(0)->WinWidth = Controls(2)->WinWidth;
    Controls(0)->WinHeight = 0.45f;

    Controls(1)->WinTop = ActualTop() + Controls(0)->WinHeight;
    Controls(1)->WinLeft = ActualLeft();
    Controls(1)->WinWidth = ActualWidth();
    Controls(1)->WinHeight = 0.002f;

    Controls(6)->WinLeft = ActualLeft() + 3.f;
    Controls(8)->WinLeft = ActualLeft() + 3.f;
    Controls(9)->WinLeft = ActualLeft() + 3.f;
    Controls(10)->WinLeft = ActualLeft() + 3.f;

    Controls(6)->WinWidth = ActualWidth();
    Controls(8)->WinWidth = ActualWidth();
    Controls(9)->WinWidth = ActualWidth();
    Controls(10)->WinWidth = ActualWidth();

    Controls(6)->WinTop = Controls(1)->ActualTop() + 1.f;
    Controls(8)->WinTop = Controls(6)->ActualTop() + Controls(6)->ActualHeight();
    Controls(9)->WinTop = Controls(8)->ActualTop() + Controls(8)->ActualHeight();
    Controls(10)->WinTop = Controls(9)->ActualTop() + Controls(9)->ActualHeight();
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the matched units.
// Stand-in bodies for callees whose custom LTCG calling conventions must match
// retail:
// - UCanvas::DrawTile (0xff300): this in ESI, Mat in EAX
// - UCanvas::DrawTileStretched (0x101ce0): this in EAX, Mat in EBX
// - UGUIStyles::Draw (0x1589e0): Canvas in EAX, this on stack
void Escape(void *);
void Sink(void *, void *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);

void UCanvas::DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                       FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor InColor)
{
    Escape(Mat);
    Escape(this);
    FLOAT SX = ClipX, SY = ClipY;
    Sink(this, &CurX, X * SX + CurX, Y * SY + CurY, XL * SX, YL * SY, U + SX, V + SY, UL * SX, VL * SY, Z, InColor);
    Sink(this, &CurY, X * SY, Y * SX, XL + CurX, YL + CurY, U * SY, V * SX, UL + SY, VL + SX, Z, InColor);
    Escape(this);
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
        fY = (mH > AHeight) ? (AHeight * 0.5f) : MidY;
        DrawTile(Mat, CurX + fX, CurY, SmallTileW, fY, fX, 0, 1.f, fY, 0, Color);
        DrawTile(Mat, CurX + fX, CurY + AHeight - fY, SmallTileW, fY, fX, mH - fY, 1.f, fY, 0, Color);
    } else {
        fX = AWidth * 0.5f;
    }

    if (mH < AHeight) {
        fY = MidY;
        DrawTile(Mat, CurX, CurY + fY, fX, SmallTileH, 0, fY, fX, 1.f, 0, Color);
        DrawTile(Mat, CurX + AWidth - fX, CurY + fY, fX, SmallTileH, mW - fX, fY, fX, 1.f, 0, Color);
    } else {
        fY = AHeight * 0.5f;
    }

    if (mH < AHeight && mW < AWidth)
        DrawTile(Mat, CurX + fX, CurY + fY, SmallTileW, SmallTileH, fX, fY, 1.f, 1.f, 0, Color);

    DrawTile(Mat, CurX, CurY, fX, fY, 0, 0, fX, fY, 0, Color);
    DrawTile(Mat, CurX + AWidth - fX, CurY, fX, fY, mW - fX, 0, fX, fY, 0, Color);
    DrawTile(Mat, CurX, CurY + AHeight - fY, fX, fY, 0, mH - fY, fX, fY, 0, Color);
    DrawTile(Mat, CurX + AWidth - fX, CurY + AHeight - fY, fX, fY, mW - fX, mH - fY, fX, fY, 0, Color);
}

void UGUIStyles::Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (MenuState > 5)
        return;
    if (eventOnDraw(Canvas, MenuState, Left, Top, Width, Height))
        return;
    UMaterial *Mat = Images[MenuState];
    if (!Mat)
        return;
    FColor C;
    C.A = 255;
    if (MenuState == 4) {
        C.B = C.G = C.R = 64;
    } else {
        C.B = C.G = C.R = 128;
    }
    Canvas->Color = C;
    UMaterial *Img = Images[MenuState];
    if (!Img)
        return;
    FLOAT mW = (FLOAT)Img->MaterialUSize();
    FLOAT mH = (FLOAT)Img->MaterialVSize();
    Canvas->Style = RStyles[MenuState];
    Canvas->Color = ImgColors[MenuState];
    switch (ImgStyle[MenuState]) {
    case 0:
        {
            FColor Gray;
            Gray.B = Gray.G = Gray.R = 128;
            Gray.A = 255;
            Canvas->DrawTile(Img, Left, Top, mW, mH, 0.f, 0.f, mW, mH, 0.f, Gray);
        }
        break;
    case 1:
        Canvas->DrawTileStretched(Img, Left, Top, Width, Height);
        break;
    case 2:
        Canvas->DrawTileStretched(Img, Left, Top, mW, mH);
        break;
    }
}

void UseCanvasA(UCanvas *C, UMaterial *M, FLOAT *P)
{
    C->DrawTileStretched(M, P[0], P[1], P[2], P[3]);
    Escape(C);
}

void UseCanvasB(UCanvas *C, UMaterial *M, FLOAT *P)
{
    Escape(M);
    C->DrawTileStretched(M, P[1], P[0], P[3], P[2]);
    Escape(C);
}

void Driver_15b170(UGUILabelPad *LP, UCanvas *C, UMaterial *M, FLOAT *P)
{
    UGUILabelPad Obj;
    Escape(&Obj);
    LP->Draw(C);
    UseCanvasA(C, M, P);
    UseCanvasB(C, M, P);
}

void Driver_15b280(UGUICadre *Cadre, UCanvas *C, UGUIStyles *S, FLOAT *P)
{
    UGUICadre Obj;
    Escape(&Obj);
    Cadre->Draw(C);
    S->Draw(C, 0, P[0], P[1], P[2], P[3]);
    S->Draw(C, 1, P[1], P[2], P[3], P[0]);
    UseCanvasA(C, 0, P);
    UseCanvasB(C, 0, P);
}
