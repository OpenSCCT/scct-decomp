// Work item 0142 (Versus RVA 0x15c0c0): UGUIHorzScrollButton::Draw.
// Retail compiled with VC7.0 /GL and linked with /LTCG. UCanvas tile helpers
// take custom LTCG register conventions (DrawTile: this in ESI, Mat in EAX;
// DrawTileStretched: this in EAX, Mat in EBX; DrawTileFull: this in EAX,
// Mat in EDI; DrawTileRect: this in EAX, Mat on stack).

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

enum EIconPosition
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
    virtual INT MaterialUSize(); // 0x68
    virtual INT MaterialVSize(); // 0x6c
};

class UCanvas
{
public:
    BYTE unk_00[0x2c];
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
    virtual ~UGUIComponent();
    virtual void VirtualSlot01(); virtual void VirtualSlot02(); virtual void VirtualSlot03();
    virtual void VirtualSlot04(); virtual void VirtualSlot05(); virtual void VirtualSlot06();
    virtual void VirtualSlot07(); virtual void VirtualSlot08(); virtual void VirtualSlot09();
    virtual void VirtualSlot10(); virtual void VirtualSlot11(); virtual void VirtualSlot12();
    virtual void VirtualSlot13(); virtual void VirtualSlot14(); virtual void VirtualSlot15();
    virtual void VirtualSlot16(); virtual void VirtualSlot17(); virtual void VirtualSlot18();
    virtual void VirtualSlot19(); virtual void VirtualSlot20(); virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void Draw(UCanvas *Canvas); // slot 23 (0x5c)
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual FLOAT ActualWidth();        // slot 26 (0x68)
    virtual FLOAT ActualHeight();       // slot 27 (0x6c)
    virtual FLOAT ActualLeft();         // slot 28 (0x70)
    virtual FLOAT ActualTop();          // slot 29 (0x74)

    BYTE unk_04[0x2c];
    BYTE MenuState;           // 0x30
    BYTE unk_31[0x2b];
    BITFIELD bUnk5c_0 : 1;    // 0x5c bit 0
    BITFIELD bUnk5c_1 : 1;    // 0x5c bit 1
    BITFIELD bUnk5c_2 : 1;    // 0x5c bit 2
    BITFIELD bVisible : 1;    // 0x5c bit 3 (0x08)
    BYTE unk_60[0x3c];
    UGUIStyles *Style;        // 0x9c
    FLOAT Bounds[4];          // 0xa0
    FLOAT ClientBounds[4];    // 0xb0
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
    UMaterial *Graphic;       // 0x1b0
    BYTE Position;            // 0x1b4
    INT ImageX;               // 0x1b8
    INT ImageY;               // 0x1bc
    INT ImageXL;              // 0x1c0
    INT ImageYL;              // 0x1c4
    BITFIELD bCheckBox : 1;   // 0x1c8 bit 0 (0x01)
    BITFIELD bUnk1c8_1 : 1;   // 0x1c8 bit 1 (0x02)
    BITFIELD bClientBound : 1;// 0x1c8 bit 2 (0x04)
    BITFIELD bChecked : 1;    // 0x1c8 bit 3 (0x08)
};

class UGUIHorzScrollButton : public UGUIGFXButton
{
public:
    virtual void Draw(UCanvas *Canvas);

    BITFIELD LeftButton : 1;  // 0x1cc bit 0 (0x01)
};

// UGUIHorzScrollButton::Draw (RVA 0x15c0c0)
void UGUIHorzScrollButton::Draw(UCanvas *Canvas)
{
    if (!bVisible)
        return;

    UGUIButton::Draw(Canvas);

    if (!Graphic)
        return;

    if (bCheckBox && !bChecked)
        return;

    FLOAT MatW, MatH;
    if (ImageXL && ImageYL)
    {
        MatW = (FLOAT)ImageXL;
        MatH = (FLOAT)ImageYL;
    }
    else
    {
        MatW = (FLOAT)Graphic->MaterialUSize();
        MatH = (FLOAT)Graphic->MaterialVSize();
    }

    Canvas->DrawColor = Style->ImgColors[MenuState];

    FLOAT W, H, L, T;
    if (bClientBound)
    {
        W = ClientBounds[2] - ClientBounds[0];
        H = ClientBounds[3] - ClientBounds[1];
        L = ClientBounds[0];
        T = ClientBounds[1];
    }
    else
    {
        W = ActualWidth();
        H = ActualHeight();
        L = ActualLeft();
        T = ActualTop();
    }

    FLOAT XL = Min(W, MatW);
    FLOAT YL = Min(H, MatH);

    if (Position == ICP_Center)
    {
        if (LeftButton)
            Canvas->DrawTile(Graphic, L + (W - XL) * 0.5f, T + (H - YL) * 0.5f, XL, YL,
                             (FLOAT)ImageX, (FLOAT)ImageY, MatW, MatH, 0.0f, Canvas->DrawColor);
        else
            Canvas->DrawTile(Graphic, L + (W - XL) * 0.5f, T + (H - YL) * 0.5f, XL, YL,
                             MatW - (FLOAT)ImageX, (FLOAT)ImageY, -MatW, MatH, 0.0f,
                             Canvas->DrawColor);
    }
    else if (Position == ICP_Stretched)
    {
        Canvas->DrawTileStretched(Graphic, L, T, W, H);
    }
    else if (Position == ICP_Scaled)
    {
        if (LeftButton)
            Canvas->DrawTileFull_102590(Graphic, L, T, W, H);
        else
            Canvas->DrawTile(Graphic, L, T, W, H, MatW, 0.0f, -MatW, MatH, 0.0f, Canvas->DrawColor);
    }
    else if (Position == ICP_Bound)
    {
        Canvas->DrawTileRect_102550(Graphic, L, T, W, H);
    }
    else
    {
        Canvas->DrawTile(Graphic, L, T, XL, YL, 0.0f, 0.0f, XL, YL, 0.0f, Canvas->DrawColor);
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for the
// UCanvas callees whose custom LTCG conventions must be reproduced, plus a
// driver rooting UGUIHorzScrollButton::Draw as a virtual function.
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

inline void *operator new(unsigned int, void *P) { return P; }

void Driver_15c0c0(void *Buf, UGUIHorzScrollButton *Btn, UCanvas *Canvas)
{
    Escape(new (Buf) UGUIHorzScrollButton);
    Btn->Draw(Canvas);
}
