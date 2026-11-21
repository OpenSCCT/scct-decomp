// Work item 0141: Versus RVA 0x15bda0, UGUIVertScrollButton::Draw (LTCG).
// UCanvas tile helpers and UGUIComponent/UGUIVertScrollButton layouts follow
// published Versus units (versus_gui_classes.h, versus_gui_bounds.c,
// versus_vd5_item_0294.cpp, versus_vd5_item_0295.cpp).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);
inline INT appFloor(FLOAT F) { return (INT)floor(F); }

template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

struct FColor
{
    BYTE B, G, R, A;
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

class UCanvas
{
public:
    void *VfTable;
    BYTE unk_04[0x28];
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
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileRect_102550(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTileFull_102590(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
};

class UGUIStyles
{
public:
    BYTE unk_00[0x70];
    FColor ImgColors[5]; // 0x70
};

class UGUIComponent
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58();
    virtual void Draw(UCanvas *Canvas); // 0x5c (slot 23)
    virtual void Vf60(); virtual void Vf64();
    virtual FLOAT ActualWidth();        // 0x68 (slot 26)
    virtual FLOAT ActualHeight();       // 0x6c (slot 27)
    virtual FLOAT ActualLeft();         // 0x70 (slot 28)
    virtual FLOAT ActualTop();          // 0x74 (slot 29)

    BYTE unk_04[0x2c];
    BYTE MenuState;       // 0x30
    BYTE unk_31[0x2b];
    DWORD : 3;            // 0x5c
    DWORD bVisible : 1;
    BYTE unk_60[0x3c];
    UGUIStyles *Style;    // 0x9c
    FLOAT Bounds[4];      // 0xa0
    FLOAT ClientBounds[4];// 0xb0
    BYTE unk_c0[0xd0];
};

class UGUIButton : public UGUIComponent
{
public:
    virtual void Draw(UCanvas *Canvas); // 0x10a5b930

    BYTE unk_190[0x20];
};

class UGUIGFXButton : public UGUIButton
{
public:
    UMaterial *Graphic;      // 0x1b0
    BYTE Position;           // 0x1b4
    BYTE unk_1b5[0x3];
    INT GraphicX;            // 0x1b8
    INT GraphicY;            // 0x1bc
    INT GraphicWidth;        // 0x1c0
    INT GraphicHeight;       // 0x1c4
    DWORD bCheckBox : 1;     // 0x1c8 bit 0
    DWORD : 1;               // bit 1
    DWORD bClientBound : 1;  // bit 2
    DWORD bChecked : 1;      // bit 3
};

class UGUIVertScrollButton : public UGUIGFXButton
{
public:
    virtual void Draw(UCanvas *Canvas); // 0x15bda0

    DWORD bIncreaseButton : 1; // 0x1cc bit 0
};

// UGUIVertScrollButton::Draw (Versus RVA 0x15bda0)
void UGUIVertScrollButton::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    UGUIButton::Draw(Canvas);

    if (!Graphic)
        return;

    if (bCheckBox && !bChecked)
        return;

    FLOAT UL, VL;
    if (GraphicWidth && GraphicHeight)
    {
        UL = (FLOAT)GraphicWidth;
        VL = (FLOAT)GraphicHeight;
    }
    else
    {
        UL = (FLOAT)Graphic->MaterialUSize();
        VL = (FLOAT)Graphic->MaterialVSize();
    }

    Canvas->DrawColor = Style->ImgColors[MenuState];

    FLOAT W, H, Left, Top;
    if (bClientBound)
    {
        W = ClientBounds[2] - ClientBounds[0];
        H = ClientBounds[3] - ClientBounds[1];
        Left = ClientBounds[0];
        Top = ClientBounds[1];
    }
    else
    {
        W = ActualWidth();
        H = ActualHeight();
        Left = ActualLeft();
        Top = ActualTop();
    }

    FLOAT DrawW = Min(W, UL);
    FLOAT DrawH = Min(H, VL);

    if (Position == 1)
    {
        if (!bIncreaseButton)
        {
            Canvas->DrawTile(Graphic, Left + (W - DrawW) * 0.5f, Top + (H - DrawH) * 0.5f,
                             DrawW, DrawH, (FLOAT)GraphicX, (FLOAT)GraphicY, UL, VL, 0.f, Canvas->DrawColor);
        }
        else
        {
            Canvas->DrawTile(Graphic, Left + (W - DrawW) * 0.5f, Top + (H - DrawH) * 0.5f,
                             DrawW, DrawH, (FLOAT)GraphicX, VL - (FLOAT)GraphicY, UL, -VL, 0.f, Canvas->DrawColor);
        }
    }
    else if (Position == 3)
    {
        Canvas->DrawTileStretched(Graphic, Left, Top, W, H);
    }
    else if (Position == 2)
    {
        if (!bIncreaseButton)
        {
            Canvas->DrawTileFull_102590(Graphic, Left, Top, W, H);
        }
        else
        {
            Canvas->DrawTile(Graphic, Left, Top, W, H, 0.f, VL, UL, -VL, 0.f, Canvas->DrawColor);
        }
    }
    else if (Position == 4)
    {
        Canvas->DrawTileRect_102550(Graphic, Left, Top, W, H);
    }
    else
    {
        Canvas->DrawTile(Graphic, Left, Top, DrawW, DrawH, 0.f, 0.f, DrawW, DrawH, 0.f, Canvas->DrawColor);
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for the
// UCanvas LTCG callees so the linker reproduces their retail register
// conventions, and a driver rooting UGUIVertScrollButton::Draw.
void Escape(void *);
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

void UCanvas::DrawTileRect_102550(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
        DrawTile(Mat, X, Y, XL, YL, 0, 0, XL, YL, 0, DrawColor);
}

void UCanvas::DrawTileFull_102590(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
    {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}
#pragma auto_inline(on)

void Driver_15bda0(UGUIVertScrollButton *Btn, UCanvas *C)
{
    UGUIVertScrollButton Obj;
    Escape(&Obj);
    Btn->UGUIVertScrollButton::Draw(C);
}
