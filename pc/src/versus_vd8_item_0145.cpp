// w4_item_0145.cpp -- Versus RVA 0x15d390 (UGUIList::PreDraw)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline INT appFloor(FLOAT F)
{
    return (INT)floor(F);
}

enum EName {
    NAME_GUI_GetFont = 0xd19c
};

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class FString : public TArray<TCHAR> {
public:
    ~FString();
};

struct FGuid;
class UFunction;

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

    BYTE unk_4[0x24];

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

struct FFontCharacter {
    INT  StartU;
    INT  StartV;
    INT  USize;
    INT  VSize;
    BYTE TextureIndex;
    BYTE unk_11[3];
};

struct FCharRemapPair {
    INT   HashNext;
    TCHAR Key;
    TCHAR Value;
};

class UFont : public UObject {
public:
    TArray<FFontCharacter> Characters;  // 0x28
    BYTE                   unk_34[0xc];
    TArray<FCharRemapPair> Pairs;       // 0x40
    INT                   *Hash;        // 0x4c
    INT                    HashCount;   // 0x50
    INT                    IsRemapped;  // 0x54
    INT                    Kerning;     // 0x58

    TCHAR RemapChar(TCHAR Char)
    {
        if (!IsRemapped)
            return Char;
        INT iHash = Hash[Char & (HashCount - 1)];
        while (iHash != -1) {
            if (Pairs(iHash).Key == Char)
                return Pairs(iHash).Value;
            iHash = Pairs(iHash).HashNext;
        }
        return 0x20;
    }

    void GetCharSize(TCHAR InCh, INT &Width, INT &Height)
    {
        Width = 0;
        Height = 0;
        TCHAR Ch = RemapChar(InCh);
        if (Ch < Characters.Num()) {
            FFontCharacter &Char = Characters(Ch);
            Width = Char.USize;
            Height = Char.VSize;
        }
    }
};

class UCanvas : public UObject {
public:
    UFont *Font;        // 0x28
    BYTE   unk_2c[0x2c];
    INT    SizeX;       // 0x58

    void ClippedStrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY,
                       INT &XL, INT &YL, const TCHAR *Text);
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

struct UGUIFont_eventGetFont_Parms {
    INT    XRes;
    UFont *ReturnValue;
};

class UGUIFont : public UGUI {
public:
    virtual ~UGUIFont();

    UFont *eventGetFont(INT XRes);
};

class UGUIStyles : public UGUI {
public:
    BYTE      unk_2c[0x58];
    UGUIFont *Fonts[5];     // 0x84
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);
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
    BYTE        MenuState;          // 0x30
    BYTE        unk_31[0x3];
    FString     unk_34;
    FString     unk_40;
    BYTE        unk_4c[0x10];
    BITFIELD    unk_5c_0 : 1;
    BITFIELD    unk_5c_1 : 1;
    BITFIELD    unk_5c_2 : 1;
    BITFIELD    bVisible : 1;       // 0x5c bit 3
    BYTE        unk_60[0x4];
    FString     unk_64;
    FLOAT       WinTop;             // 0x70
    FLOAT       WinLeft;            // 0x74
    FLOAT       WinWidth;           // 0x78
    FLOAT       WinHeight;          // 0x7c
    BYTE        unk_80[0x1c];
    UGUIStyles *Style;              // 0x9c
    FLOAT       Bounds[4];          // 0xa0
    FLOAT       ClientBounds[4];    // 0xb0
    BYTE        unk_c0[0xd0];
};

class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void VirtualSlot44();

    BYTE unk_190[0x18];
    INT  ItemsPerPage;              // 0x1a8
    INT  ItemHeight;                // 0x1ac
    BYTE unk_1b0[0x20];
};

class UGUIVertList : public UGUIListBase {
public:
    virtual ~UGUIVertList();
};

class UGUIList : public UGUIVertList {
public:
    UGUIList() {}
    virtual ~UGUIList();
    virtual void PreDraw(UCanvas *Canvas);

    BYTE unk_1d0[0x1c];
};

// Retail keeps the literal L"WQ,2" in writable .data (0x10c467d8).
extern const TCHAR GListMeasureSample[];

// UGUIList::PreDraw (RVA 0x15d390)
void UGUIList::PreDraw(UCanvas *Canvas)
{
    if (!bVisible || !Style)
        return;

    UGUIComponent::PreDraw(Canvas);

    Canvas->Font = Style->Fonts[MenuState]->eventGetFont(Canvas->SizeX);
    if (!Canvas->Font)
        return;

    INT XL, YL;
    Canvas->ClippedStrLen(Canvas->Font, 1.0f, 1.0f, XL, YL, GListMeasureSample);
    ItemHeight = YL;
    ItemsPerPage = appFloor((ClientBounds[3] - ClientBounds[1]) / YL);
}

// Scaffolding for the LTCG link of 0x15d390, not part of the unit.
#pragma auto_inline(off)
void UCanvas::ClippedStrLen(UFont *InFont, FLOAT ScaleX, FLOAT ScaleY,
                            INT &XL, INT &YL, const TCHAR *Text)
{
    XL = 0;
    YL = 0;
    if (!InFont) {
        InFont = Font;
        if (!InFont)
            return;
    }
    for (INT i = 0; Text[i]; i++) {
        INT W, H;
        InFont->GetCharSize(Text[i], W, H);
        if (Text[i + 1])
            W += InFont->Kerning;
        XL += (INT)(W * ScaleX);
        INT ScaledH = (INT)(H * ScaleY);
        if (YL < ScaledH)
            YL = ScaledH;
    }
}

UFont *UGUIFont::eventGetFont(INT XRes)
{
    UGUIFont_eventGetFont_Parms Parms;
    Parms.ReturnValue = 0;
    Parms.XRes = XRes;
    ProcessEvent(FindFunctionChecked(NAME_GUI_GetFont), &Parms);
    return Parms.ReturnValue;
}
#pragma auto_inline(on)

inline void *operator new(unsigned int, void *Ptr) { return Ptr; }
void Escape(void *);
void Driver_15d390(void *Mem, UGUIList *List, UCanvas *Canvas, UGUIFont *GuiFont,
                   UFont *Font, INT XRes, const TCHAR *Text)
{
    Escape(new(Mem) UGUIList);
    Escape(GuiFont->eventGetFont(XRes));
    INT XL, YL;
    Canvas->ClippedStrLen(Font, 1.0f, 1.0f, XL, YL, Text);
    Escape(&XL);
    Escape(&YL);
    List->PreDraw(Canvas);
}
