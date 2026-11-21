// Work item 0152: UGUISplitter::MouseMove (Versus RVA 0x15f720)

typedef unsigned char  BYTE;
typedef unsigned short TCHAR;
typedef unsigned long  DWORD;
typedef int            INT;
typedef DWORD          UBOOL;
typedef DWORD          BITFIELD;
typedef float          FLOAT;

struct FGuid;
struct FStateFrame;
class UClass;
class UGUIController;

enum EMenuState {
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4
};

enum EGUISplitterType {
    SPLIT_Vertical   = 0,
    SPLIT_Horizontal = 1
};

FLOAT Clamp(FLOAT Value, FLOAT Min, FLOAT Max);

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

    UGUIController *Controller;
};

class UGUIController : public UObject {
public:
    BYTE unk_28[0xca4];
    INT  MouseX;
    INT  MouseY;
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void  VirtualSlot22();
    virtual void  VirtualSlot23();
    virtual void  VirtualSlot24();
    virtual void  VirtualSlot25();
    virtual FLOAT ActualWidth();
    virtual FLOAT ActualHeight();
    virtual FLOAT ActualLeft();
    virtual FLOAT ActualTop();
    virtual void  VirtualSlot30();
    virtual void  VirtualSlot31();
    virtual void  VirtualSlot32();
    virtual void  VirtualSlot33();
    virtual UBOOL MouseMove(INT XDelta, INT YDelta);
    virtual void  VirtualSlot35();
    virtual void  VirtualSlot36();
    virtual void  VirtualSlot37();
    virtual void  VirtualSlot38();
    virtual void  VirtualSlot39();
    virtual void  VirtualSlot40();
    virtual void  VirtualSlot41();
    virtual void  VirtualSlot42();
    virtual void  VirtualSlot43();

    void delegateOnCapturedMouseMove(FLOAT XDelta, FLOAT YDelta);

    UGUIComponent *MenuOwner;
    BYTE           MenuState;
    BYTE           unk_31[0x2b];
    BITFIELD       bBoundToParent : 1;
    BITFIELD       bScaleToParent : 1;
    BITFIELD       bHasFocus : 1;
    BITFIELD       bVisible : 1;
    BITFIELD       bAcceptsInput : 1;
    BITFIELD       bCaptureTabs : 1;
    BITFIELD       bCaptureMouse : 1;
    BYTE           unk_60[0x130];
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();

    UGUIComponent **ControlsData;
    INT             ControlsNum;
    INT             ControlsMax;
    BYTE            unk_19c[0x4];
};

class UGUIPanel : public UGUIMultiComponent {
public:
    virtual ~UGUIPanel();

    BYTE unk_1a0[0x8];
};

class UGUISplitter : public UGUIPanel {
public:
    virtual ~UGUISplitter();
    virtual UBOOL MouseMove(INT XDelta, INT YDelta);

    void SplitterUpdatePositions();

    BYTE  SplitOrientation;
    FLOAT SplitPosition;
    BYTE  unk_1b0[0x8];
};

// UGUISplitter::MouseMove (RVA 0x15f720)
UBOOL UGUISplitter::MouseMove(INT XDelta, INT YDelta)
{
    if (MenuState == MSAT_Pressed && bCaptureMouse)
        delegateOnCapturedMouseMove((FLOAT)XDelta, (FLOAT)YDelta);

    if (!Controller)
        return 1;

    if (MenuState == MSAT_Pressed) {
        switch (SplitOrientation) {
        case SPLIT_Vertical:
            SplitPosition = Clamp((Controller->MouseY - ActualTop()) / ActualHeight(), 0.0f, 1.0f);
            break;
        case SPLIT_Horizontal:
            SplitPosition = Clamp((Controller->MouseX - ActualLeft()) / ActualWidth(), 0.0f, 1.0f);
            break;
        }

        SplitterUpdatePositions();
        return 0;
    }

    bCaptureMouse = 0;
    return 0;
}

// Scaffolding for the link, not part of the unit.
void ExternalSink(FLOAT);
void Escape(void *);

void UGUISplitter::SplitterUpdatePositions()
{
    if (bVisible && ControlsNum >= 2 && ControlsData[0] && ControlsData[1]) {
        ExternalSink(ActualWidth());
        ExternalSink(ActualHeight());
        ExternalSink(ActualLeft());
        ExternalSink(ActualTop());
    }
}

void Driver_15f720(UGUISplitter *S, INT XDelta, INT YDelta)
{
    UGUISplitter Local;
    Escape(&Local);
    S->MouseMove(XDelta, YDelta);
}
