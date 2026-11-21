// w4_item_0144.cpp -- Versus GUI scroll bar and list box layout/drawing methods

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline FLOAT floorf(FLOAT F)
{
    return (FLOAT)floor((double)F);
}

struct FGuid;
struct FStateFrame;
class UClass;
class UCanvas;
class UMaterial;
class UGUIStyles;

struct FColor {
    BYTE R, G, B, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : R(InR), G(InG), B(InB), A(InA) {}
};

template<class T>
class TArray {
public:
    T  *Data;
    INT ArrayNum;
    INT ArrayMax;

    T &operator()(INT i) { return Data[i]; }
    const T &operator()(INT i) const { return Data[i]; }
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
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
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
    virtual ~UMaterial();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual INT MaterialUSize();
    virtual INT MaterialVSize();
};

class UCanvas : public UObject {
public:
    BYTE   unk_28[0x20];
    BYTE   Style;
    BYTE   unk_49[0x7];
    FColor DrawColor;

    void DrawTile(UMaterial *Mat, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color, FColor Fog);
    void DrawTileStretched(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT AWidth, FLOAT AHeight);
    void DrawTileScaled(UMaterial *Mat, FLOAT Left, FLOAT Top, FLOAT XScale, FLOAT YScale);
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

class UGUIStyles : public UGUI {
public:
    BYTE       unk_2c[0xc];
    BYTE       RStyles[5];
    BYTE       unk_3d[0x3];
    UMaterial *Images[5];
    BYTE       ImgStyle[5];
    BYTE       unk_59[0x17];
    FColor     ImgColors[5];

    UBOOL eventOnDraw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
    void Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height);
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
    virtual void SetDims(FLOAT Width, FLOAT Height, FLOAT Left, FLOAT Top);
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();

    BYTE        unk_2c[0x4];
    BYTE        MenuState;
    BYTE        unk_31[0x1b];
    FLOAT       Bounds[4];
    BITFIELD    bBit0 : 1;
    BITFIELD    bBit1 : 1;
    BITFIELD    bBit2 : 1;
    BITFIELD    bVisible : 1;
    BYTE        unk_60[0x3c];
    UGUIStyles *Style;
    BYTE        unk_a0[0xf0];
};

class UGUIMultiComponent : public UGUIComponent {
public:
    typedef UGUIComponent Super;
    virtual ~UGUIMultiComponent();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);

    TArray<UGUIComponent *> Controls;
    BYTE                    unk_19c[0x4];
};

class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void VirtualSlot44();

    BYTE unk_190[0x18];
    INT  ItemsPerPage;
    BYTE unk_1ac[0x8];
    INT  ItemCount;
    BYTE unk_1b8[0x18];
};

class UGUIScrollBarBase : public UGUIMultiComponent {
public:
    typedef UGUIMultiComponent Super;
    virtual ~UGUIScrollBarBase();

    UGUIListBase *MyList;
};

class UGUIVertScrollZone : public UGUIComponent {
public:
    typedef UGUIComponent Super;
    virtual ~UGUIVertScrollZone();
    virtual void Draw(UCanvas *Canvas);

    BYTE unk_190[0x8];
};

class UGUIVertScrollBar : public UGUIScrollBarBase {
public:
    typedef UGUIScrollBarBase Super;
    virtual ~UGUIVertScrollBar();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);

    FLOAT GripPos;
    FLOAT GripSize;
    BYTE  unk_1ac[0x4];
};

class UGUIListBoxBase : public UGUIMultiComponent {
public:
    typedef UGUIMultiComponent Super;
    virtual ~UGUIListBoxBase();

    BYTE unk_1a0[0x8];
};

class UGUIListBox : public UGUIListBoxBase {
public:
    typedef UGUIListBoxBase Super;
    virtual ~UGUIListBox();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);

    BYTE unk_1a8[0x4];
};

// UGUIVertScrollZone::Draw (RVA 0x15ce70)
void UGUIVertScrollZone::Draw(UCanvas *Canvas)
{
    if (!bVisible || !Style)
        return;

    if (ActualWidth() <= 1.0f || ActualHeight() <= 1.0f)
        return;

    Super::Draw(Canvas);
    Style->Draw(Canvas, MenuState, ActualLeft(), ActualTop() + 2.0f,
                ActualWidth(), ActualHeight());
}

// UGUIVertScrollBar::PreDraw (RVA 0x15cf10)
void UGUIVertScrollBar::PreDraw(UCanvas *Canvas)
{
    Super::PreDraw(Canvas);

    if (!bVisible || !MyList || MyList->ItemCount == 0)
        return;

    FLOAT W = ActualWidth();
    FLOAT H = ActualHeight();

    Controls(0)->SetDims(W, H - (2 * W), ActualLeft() + 1.0f, ActualTop() + W);
    Controls(1)->SetDims(W, W, ActualLeft() + 1.0f, ActualTop() + 1.0f);
    Controls(2)->SetDims(W, W, ActualLeft() + 1.0f, ActualTop() + H - W + 1.0f);

    FLOAT ZoneHeight = Controls(0)->ActualHeight();
    GripSize = 20.0f;
    FLOAT Y = Controls(0)->ActualTop() + (INT)floorf((ZoneHeight - GripSize) * GripPos);

    Controls(3)->SetDims(W - 2.0f, GripSize, ActualLeft() + 2.0f, Y + 1.0f);
}

// UGUIVertScrollBar::Draw (RVA 0x15d0c0)
void UGUIVertScrollBar::Draw(UCanvas *Canvas)
{
    if (!bVisible || !MyList || MyList->ItemCount == 0)
        return;

    Super::Draw(Canvas);

    if (Style)
        Style->Draw(Canvas, MenuState, ActualLeft(), ActualTop(),
                    ActualWidth(), ActualHeight());
}

// UGUIListBox::PreDraw (RVA 0x15d140)
void UGUIListBox::PreDraw(UCanvas *Canvas)
{
    Super::PreDraw(Canvas);

    if (!bVisible)
        return;

    UGUIListBase *List = (UGUIListBase *)Controls(0);
    if (List->ItemsPerPage > 0 && List->ItemCount > List->ItemsPerPage)
        Controls(1)->bVisible = 1;
    else
        Controls(1)->bVisible = 0;

    FLOAT ScrollWidth = Controls(1)->bVisible ? Controls(1)->ActualWidth() : 0.0f;
    Controls(0)->SetDims(ActualWidth() - ScrollWidth, ActualHeight(), ActualLeft(), ActualTop());
    Controls(1)->SetDims(Controls(1)->ActualWidth(), ActualHeight() - 1.0f,
                         Controls(0)->ActualLeft() + Controls(0)->ActualWidth() - 1.0f,
                         ActualTop());
}

// UGUIListBox::Draw (RVA 0x15d260)
void UGUIListBox::Draw(UCanvas *Canvas)
{
    Bounds[3] = Controls(0)->Bounds[3];
    Bounds[2] = Controls(0)->Bounds[2];
    Bounds[1] = Controls(0)->Bounds[1];
    Bounds[0] = Controls(0)->Bounds[0];
    Super::Draw(Canvas);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
UCanvas *GetCanvas();
void UGUIStyles::Draw(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width, FLOAT Height)
{
    if (!Canvas)
        Canvas = GetCanvas();
    if (MenuState > 5)
        return;

    if (eventOnDraw(Canvas, MenuState, Left, Top, Width, Height))
        return;

    if (!Images[MenuState])
        return;

    if (MenuState == 4)
        Canvas->DrawColor = FColor(64, 64, 64, 255);
    else
        Canvas->DrawColor = FColor(128, 128, 128, 255);

    UMaterial *Img = Images[MenuState];
    if (!Img)
        return;

    FLOAT USize = (FLOAT)Img->MaterialUSize();
    FLOAT VSize = (FLOAT)Img->MaterialVSize();

    Canvas->Style = RStyles[MenuState];
    Canvas->DrawColor = ImgColors[MenuState];

    switch (ImgStyle[MenuState]) {
    case 0:
        Canvas->DrawTile(Img, Left, Top, USize, VSize, 0.0f, 0.0f, USize, VSize, 0.0f, FColor(128, 128, 128, 255), FColor(0, 0, 0, 0));
        break;
    case 1:
        Canvas->DrawTileStretched(Img, Left, Top, Width, Height);
        break;
    case 2:
        Canvas->DrawTileScaled(Img, Left, Top, Width, Height);
        break;
    }
}

void Driver_15ce70(UGUIStyles *Style, BYTE State, FLOAT L, FLOAT T, FLOAT W, FLOAT H)
{
    UGUIVertScrollZone Zone;
    UGUIVertScrollBar Bar;
    Escape(&Zone);
    Escape(&Bar);
    Style->Draw(GetCanvas(), State, L, T, W, H);
}
