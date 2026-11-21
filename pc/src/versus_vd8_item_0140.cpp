// Work item 0140: Versus RVA 0x15ba30 (UGUIGFXButton::Draw).
// Retail compiled with VC7.0 /GL and linked with /LTCG: the UCanvas tile
// helpers called here use custom LTCG register conventions.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
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

enum eMenuState
{
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4,
};

enum eIconPosition
{
    ICP_Normal    = 0,
    ICP_Center    = 1,
    ICP_Scaled    = 2,
    ICP_Stretched = 3,
    ICP_Bound     = 4,
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
    virtual INT MaterialUSize();    // 0x68
    virtual INT MaterialVSize();    // 0x6c
};

class UCanvas
{
public:
    virtual void Vf00();
    BYTE unk_04[0x28];
    FLOAT OrgX;         // 0x2c
    FLOAT OrgY;         // 0x30
    FLOAT ClipX;        // 0x34
    FLOAT ClipY;        // 0x38
    FLOAT CurX;         // 0x3c
    FLOAT CurY;         // 0x40
    FLOAT Z;            // 0x44
    BYTE Style;         // 0x48
    FLOAT CurYL;        // 0x4c
    FColor DrawColor;   // 0x50

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
    void DrawTileScaleBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL);
};

class UGUIStyles
{
public:
    BYTE unk_00[0x70];
    FColor ImgColors[5];    // 0x70
};

class UGUIComponent
{
public:
    virtual void Vf00(); virtual void Vf01(); virtual void Vf02(); virtual void Vf03();
    virtual void Vf04(); virtual void Vf05(); virtual void Vf06(); virtual void Vf07();
    virtual void Vf08(); virtual void Vf09(); virtual void Vf10(); virtual void Vf11();
    virtual void Vf12(); virtual void Vf13(); virtual void Vf14(); virtual void Vf15();
    virtual void Vf16(); virtual void Vf17(); virtual void Vf18(); virtual void Vf19();
    virtual void Vf20(); virtual void Vf21(); virtual void Vf22();
    virtual void Draw(UCanvas *Canvas);     // slot 23 (0x5c)
    virtual void Vf24(); virtual void Vf25();
    virtual FLOAT ActualWidth();            // slot 26 (0x68)
    virtual FLOAT ActualHeight();           // slot 27 (0x6c)
    virtual FLOAT ActualLeft();             // slot 28 (0x70)
    virtual FLOAT ActualTop();              // slot 29 (0x74)

    BYTE unk_04[0x2c];
    BYTE MenuState;             // 0x30
    BYTE unk_31[0x2b];
    BITFIELD unk_5c_0 : 3;
    BITFIELD bVisible : 1;      // 0x5c bit 3 (0x08)
    BYTE unk_60[0x3c];
    UGUIStyles *Style;          // 0x9c
    FLOAT Bounds[4];            // 0xa0
    FLOAT ClientBounds[4];      // 0xb0
    BYTE unk_c0[0xd0];
};

class UGUIButton : public UGUIComponent
{
public:
    virtual void Draw(UCanvas *Canvas);

    BYTE unk_190[0x20];
};

class UGUIGFXButton : public UGUIButton
{
public:
    virtual void Draw(UCanvas *Canvas);

    UMaterial *Graphic;         // 0x1b0
    BYTE Position;              // 0x1b4
    INT ImageLeft;              // 0x1b8
    INT ImageTop;               // 0x1bc
    INT ImageWidth;             // 0x1c0
    INT ImageHeight;            // 0x1c4
    BITFIELD bCheckBox : 1;     // 0x1c8 bit 0 (0x01)
    BITFIELD unk_1c8_1 : 1;     // 0x1c8 bit 1 (0x02)
    BITFIELD bClientBound : 1;  // 0x1c8 bit 2 (0x04)
    BITFIELD bChecked : 1;      // 0x1c8 bit 3 (0x08)
};

// RVA 0x15ba30: UGUIGFXButton::Draw
void UGUIGFXButton::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    bool bFlip = false;
    if (ImageHeight < 0)
    {
        bFlip = true;
        ImageHeight = -ImageHeight;
    }

    UGUIButton::Draw(Canvas);

    if (!Graphic)
        return;

    if (bCheckBox && !bChecked)
        return;

    FLOAT u, v;
    if (ImageWidth && ImageHeight)
    {
        u = (FLOAT)ImageWidth;
        v = (FLOAT)ImageHeight;
    }
    else
    {
        u = (FLOAT)Graphic->MaterialUSize();
        v = (FLOAT)Graphic->MaterialVSize();
    }

    if (MenuState == MSAT_Disabled)
        Canvas->DrawColor = Style->ImgColors[0];
    else
        Canvas->DrawColor = Style->ImgColors[MenuState];

    FLOAT w, h, l, t;
    if (bClientBound)
    {
        w = ClientBounds[2] - ClientBounds[0];
        h = ClientBounds[3] - ClientBounds[1];
        l = ClientBounds[0];
        t = ClientBounds[1];
    }
    else
    {
        w = ActualWidth();
        h = ActualHeight();
        l = ActualLeft();
        t = ActualTop();
    }

    FLOAT xl = Min(w, u);
    FLOAT yl = Min(h, v);

    if (Position == ICP_Center)
    {
        if (bFlip)
            Canvas->DrawTile(Graphic, l + (w - xl) * 0.5f, t + (h - yl) * 0.5f, xl, yl,
                             (FLOAT)ImageLeft, v, u, (FLOAT)ImageTop - v, 0, Canvas->DrawColor);
        else
            Canvas->DrawTile(Graphic, l + (w - xl) * 0.5f, t + (h - yl) * 0.5f, xl, yl,
                             (FLOAT)ImageLeft, (FLOAT)ImageTop, u, v, 0, Canvas->DrawColor);
    }
    else if (Position == ICP_Stretched)
    {
        Canvas->DrawTileStretched(Graphic, l, t, w, h);
    }
    else if (Position == ICP_Scaled)
    {
        Canvas->DrawTileScaleBound(Graphic, l, t, w, h);
    }
    else if (Position == ICP_Bound)
    {
        Canvas->DrawTileBound(Graphic, l, t, w, h);
    }
    else
    {
        if (bFlip)
            Canvas->DrawTile(Graphic, l, t, xl, yl, 0, yl, xl, -yl, 0, Canvas->DrawColor);
        else
            Canvas->DrawTile(Graphic, l, t, xl, yl, 0, 0, xl, yl, 0, Canvas->DrawColor);
    }

    if (bFlip)
        ImageHeight = -ImageHeight;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in definitions for
// the UCanvas LTCG callees so the linker assigns their retail register
// conventions, plus the driver rooting UGUIGFXButton::Draw via its vtable.
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

void UCanvas::DrawTileBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
        DrawTile(Mat, X, Y, XL, YL, 0, 0, XL, YL, 0, DrawColor);
}

void UCanvas::DrawTileScaleBound(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL)
{
    if (Style)
    {
        FLOAT USize = (FLOAT)Mat->MaterialUSize();
        FLOAT VSize = (FLOAT)Mat->MaterialVSize();
        DrawTile(Mat, X, Y, XL, YL, 0, 0, USize, VSize, 0, DrawColor);
    }
}
#pragma auto_inline(on)

void Driver_15ba30(UCanvas *C, UMaterial *M, FLOAT a, FLOAT b, FLOAT c, FLOAT d)
{
    UGUIGFXButton Btn;
    Escape(&Btn);
    C->DrawTileStretched(M, a, b, c, d);
    C->DrawTileBound(M, a, b, c, d);
    C->DrawTileScaleBound(M, a, b, c, d);
}
