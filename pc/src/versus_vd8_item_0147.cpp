// w4_item_0147.cpp -- Versus GUI list item drawing (UGUIList::DrawItem)

typedef unsigned char  BYTE;
typedef unsigned short TCHAR;
typedef int            INT;
typedef unsigned long  DWORD;
typedef DWORD          UBOOL;
typedef float          FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double X);
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Buf, unsigned int Count,
                                                         const TCHAR *Fmt, char *Args);

inline INT appRound(FLOAT F)
{
    return (INT)floor(F + 0.5f);
}

struct FGuid;
struct FColor {
    BYTE B, G, R, A;
};

struct FName {
    INT Index;
    FName(INT InIndex) : Index(InIndex) {}
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

struct FGUIListElem {
    FString Item;
    BYTE    unk_0c[0x10];
};

class UFunction;
class UFont;

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object: 0x28 bytes, 22 virtual functions in Versus.
class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
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

    BYTE unk_04[0x24];

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class UCanvas : public UObject {
public:
    UFont  *Font;           // 0x28
    BYTE    unk_2c[0x10];
    FLOAT   CurX;           // 0x3c
    FLOAT   CurY;           // 0x40
    BYTE    unk_44[0x4];
    BYTE    Style;          // 0x48
    BYTE    unk_49[0x7];
    FColor  Color;          // 0x50
    BYTE    unk_54[0x4];
    INT     SizeX;          // 0x58

    void WrappedStrLenf(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY, INT &XL, INT &YL,
                        const TCHAR *Text);
    void __cdecl DrawTextJustified(BYTE Justification, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2,
                                   const TCHAR *Fmt, ...);
};

// GUI.GUI: 0x2c bytes, 22 virtual functions
class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

struct UGUIFont_eventGetFont_Parms {
    INT    XRes;
    UFont *ReturnValue;
};

// GUI.GUIFont: 0x58 bytes, 22 virtual functions
class UGUIFont : public UGUI {
public:
    virtual ~UGUIFont();

    BYTE unk_2c[0x2c];

    UFont *eventGetFont(INT XRes);
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

// GUI.GUIStyles
class UGUIStyles : public UGUI {
public:
    virtual ~UGUIStyles();

    BYTE       unk_2c[0xc];
    BYTE       RStyles[6];      // 0x38
    BYTE       unk_3e[0x1e];
    FColor     FontColors[6];   // 0x5c
    BYTE       unk_74[0x10];
    UGUIFont  *Fonts[6];        // 0x84
    BYTE       unk_9c[0x48];
    DWORD      bShadow;         // 0xe4

    UBOOL eventOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width,
                          FLOAT Height, BYTE Align, const FString &Text);
    void DrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width,
                  FLOAT Height, BYTE Align, const TCHAR *Text);
};

// GUI.GUIComponent: 0x190 bytes, 44 virtual functions
class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
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
    BYTE        MenuState;      // 0x30
    BYTE        unk_31[0x3];
    FString     unk_34;
    FString     unk_40;
    BYTE        unk_4c[0x18];
    FString     unk_64;
    BYTE        unk_70[0x2c];
    UGUIStyles *Style;          // 0x9c
    BYTE        unk_a0[0xf0];
};

// GUI.GUIListBase: 0x1d0 bytes, 45 virtual functions
class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void DrawItem(UCanvas *Canvas, INT Item, FLOAT X, FLOAT Y, FLOAT W, FLOAT H);

    BYTE unk_190[0x40];
};

// GUI.GUIVertList: 0x1d0 bytes, 45 virtual functions
class UGUIVertList : public UGUIListBase {
public:
    virtual ~UGUIVertList();
};

// GUI.GUIList: 0x1ec bytes, 45 virtual functions
class UGUIList : public UGUIVertList {
public:
    virtual ~UGUIList();
    virtual void DrawItem(UCanvas *Canvas, INT Item, FLOAT X, FLOAT Y, FLOAT W, FLOAT H);

    BYTE                 TextAlign;     // 0x1d0
    BYTE                 unk_1d1[0x3];
    TArray<FGUIListElem> Elements;      // 0x1d4
    BYTE                 unk_1e0[0xc];
};

// UGUIList::DrawItem (RVA 0x15e000, UGUIList vtable slot 44)
void UGUIList::DrawItem(UCanvas *Canvas, INT Item, FLOAT X, FLOAT Y, FLOAT W, FLOAT H)
{
    Style->DrawText(Canvas, MenuState, X, Y, W, H, TextAlign, *Elements(Item).Item);
}

// Scaffolding for the LTCG link, not part of the 0x15e000 unit.
void Escape(void *);

void __cdecl UCanvas::DrawTextJustified(BYTE Justification, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2,
                                        const TCHAR *Fmt, ...)
{
    TCHAR Buffer[4096];
    char *Args = (char *)&Fmt + sizeof(Fmt);
    _vsnwprintf(Buffer, 4096, Fmt, Args);
    INT XL = 0, YL = 0;
    CurX = 0.0f;
    CurY = 0.0f;
    WrappedStrLenf(Font, 1.0f, 1.0f, XL, YL, Buffer);
    CurY = (Y2 - Y1) * 0.5f - (FLOAT)(YL / 2);
    if (Justification == 0)
        CurX = X1;
    else if (Justification == 1)
        CurX = X2 - XL;
}

UFont *UGUIFont::eventGetFont(INT XRes)
{
    UGUIFont_eventGetFont_Parms Parms;
    Parms.XRes = XRes;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunctionChecked(FName(0xd19c)), &Parms);
    return Parms.ReturnValue;
}

UBOOL UGUIStyles::eventOnDrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top,
                                  FLOAT Width, FLOAT Height, BYTE Align, const FString &Text)
{
    UGUIStyles_eventOnDrawText_Parms Parms;
    Parms.ReturnValue = 0;
    Parms.Canvas = Canvas;
    Parms.MenuState = MenuState;
    Parms.Left = Left;
    Parms.Top = Top;
    Parms.Width = Width;
    Parms.Height = Height;
    Parms.Align = Align;
    Parms.Text = Text;
    ProcessEvent(FindFunctionChecked(FName(0xd19d)), &Parms);
    return Parms.ReturnValue;
}

void UGUIStyles::DrawText(UCanvas *Canvas, BYTE MenuState, FLOAT Left, FLOAT Top, FLOAT Width,
                          FLOAT Height, BYTE Align, const TCHAR *Text)
{
    BYTE   OldStyle = Canvas->Style;
    FColor OldColor = Canvas->Color;
    UFont *OldFont  = Canvas->Font;

    Left   = (FLOAT)appRound(Left);
    Top    = (FLOAT)appRound(Top);
    Width  = (FLOAT)appRound(Width);
    Height = (FLOAT)appRound(Height);

    if (MenuState > 5)
        return;

    if (!Fonts[MenuState])
        return;

    if (eventOnDrawText(Canvas, MenuState, Left, Top, Width, Height, Align, FString(Text)))
        return;

    Canvas->Style = RStyles[MenuState];
    Canvas->Color = FontColors[MenuState];
    UFont *Font   = Fonts[MenuState]->eventGetFont(Canvas->SizeX);
    Canvas->Font  = Font;

    if (bShadow & 2)
        Align += 10;

    if (Font)
        Canvas->DrawTextJustified(Align, Left, Top, Left + Width, Top + Height, Text);

    Canvas->Style = OldStyle;
    Canvas->Color = OldColor;
    Canvas->Font  = OldFont;
}

void Driver_15e000(UGUIList *List, UCanvas *Canvas, UGUIFont *GF, UGUIStyles *St,
                   const FString &S, INT N, FLOAT A, FLOAT B, FLOAT C, FLOAT D)
{
    UGUIList Local;
    Escape(&Local);
    if (N == 1)
        Escape(GF->eventGetFont(N));
    else if (N == 2)
        Escape((void *)St->eventOnDrawText(Canvas, (BYTE)N, A, B, C, D, (BYTE)N, S));
    else if (N == 3)
        Canvas->DrawTextJustified((BYTE)N, A, B, C, D, *S);
    else if (N == 4)
        St->DrawText(Canvas, (BYTE)N, A, B, C, D, (BYTE)N, *S);
    else
        List->DrawItem(Canvas, N, A, B, C, D);
}
