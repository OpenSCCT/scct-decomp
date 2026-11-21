// w4_item_0151.cpp -- Versus GUI splitter position update (RVA 0x15f390)

typedef unsigned char  BYTE;
typedef unsigned short TCHAR;
typedef int            INT;
typedef unsigned long  DWORD;
typedef DWORD          UBOOL;
typedef DWORD          BITFIELD;
typedef float          FLOAT;

struct FGuid;
struct FFrame;
struct FStateFrame;
class UClass;

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
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
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

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
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
    // Sets child component bounds (width, height, left, top).
    virtual void VirtualSlot39(FLOAT Width, FLOAT Height, FLOAT Left, FLOAT Top);
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();

    BYTE     unk_2c[0x8];
    FString  unk_34;
    FString  unk_40;
    BYTE     unk_4c[0x10];
    // Bit 3 of flags at 0x5c; exact UnrealScript property name not yet verified.
    BITFIELD unk_5c_0 : 1;
    BITFIELD unk_5c_1 : 1;
    BITFIELD unk_5c_2 : 1;
    BITFIELD unk_5c_bit3 : 1;
    BYTE     unk_60[0x4];
    FString  unk_64;
    BYTE     unk_70[0x120];
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();

    TArray<UGUIComponent *> Controls;
    BYTE                    unk_19c[0x4];
};

class UGUIPanel : public UGUIMultiComponent {
public:
    virtual ~UGUIPanel();

    BYTE unk_1a0[0x8];
};

enum EGUISplitterType {
    SPLIT_Vertical   = 0,
    SPLIT_Horizontal = 1
};

class UGUISplitter : public UGUIPanel {
public:
    virtual ~UGUISplitter();

    BYTE  SplitOrientation;
    FLOAT SplitPosition;
    BYTE  unk_1b0[0x4];
    FLOAT SplitAreaSize;

    void SplitterUpdatePositions();
};

// UGUISplitter::SplitterUpdatePositions (RVA 0x15f390)
void UGUISplitter::SplitterUpdatePositions()
{
    if (!unk_5c_bit3)
        return;

    if (Controls.Num() < 2)
        return;

    if (Controls(0) == 0 || Controls(1) == 0)
        return;

    FLOAT W = ActualWidth();
    FLOAT H = ActualHeight();

    switch (SplitOrientation) {
    case SPLIT_Vertical: {
        FLOAT H1 = (H - SplitAreaSize) * SplitPosition;
        Controls(0)->VirtualSlot39(W, H1, 0.0f, 0.0f);
        Controls(1)->VirtualSlot39(W, H - H1 - SplitAreaSize, 0.0f, H1 + SplitAreaSize);
        break;
    }
    case SPLIT_Horizontal: {
        FLOAT W1 = (W - SplitAreaSize) * SplitPosition;
        Controls(0)->VirtualSlot39(W1, H, 0.0f, 0.0f);
        Controls(1)->VirtualSlot39(W - W1 - SplitAreaSize, H, W1 + SplitAreaSize, 0.0f);
        break;
    }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_15f390(UGUISplitter *Splitter)
{
    Escape(Splitter);
    Splitter->SplitterUpdatePositions();
}
