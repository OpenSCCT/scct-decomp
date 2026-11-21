// w4_item_0132.cpp -- UGUIComponent::ActualLeft (Versus RVA 0x159120)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;
typedef unsigned short TCHAR;

struct FGuid;
struct FStateFrame;
class UClass;
class UGUIController;
class UInteractionMaster;
class UClient;
class UViewport;

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString();
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

class UViewport : public UObject {
public:
    BYTE unk_28[0x78];
    INT  SizeX;
    INT  SizeY;
};

class UClient : public UObject {
public:
    BYTE                unk_28[0x4];
    TArray<UViewport *> Viewports;
};

class UInteractionMaster : public UObject {
public:
    UClient *Client;
};

class UGUIController : public UObject {
public:
    BYTE                unk_28[0x8];
    UInteractionMaster *Master;
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    UGUIController *Controller;
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
    virtual void  VirtualSlot34();
    virtual void  VirtualSlot35();
    virtual void  VirtualSlot36();
    virtual void  VirtualSlot37();
    virtual void  VirtualSlot38();
    virtual void  VirtualSlot39();
    virtual void  VirtualSlot40();
    virtual void  VirtualSlot41();
    virtual void  VirtualSlot42();
    virtual void  VirtualSlot43();

    UGUIComponent *MenuOwner;
    BYTE           unk_30[0x4];
    FString        unk_34;
    FString        unk_40;
    BYTE           unk_4c[0x10];
    BITFIELD       bBoundToParent : 1;
    BITFIELD       bScaleToParent : 1;
    BYTE           unk_60[0x4];
    FString        unk_64;
    FLOAT          WinTop;
    FLOAT          WinLeft;
    FLOAT          WinWidth;
    FLOAT          WinHeight;
};

// UGUIComponent::ActualLeft
FLOAT UGUIComponent::ActualLeft()
{
    if (!Controller || !Controller->Master || !Controller->Master->Client ||
        !Controller->Master->Client->Viewports.Num() || !Controller->Master->Client->Viewports(0))
        return 0.0f;

    if (WinLeft <= 1.0f) {
        if (bBoundToParent && MenuOwner)
            return MenuOwner->ActualLeft() + MenuOwner->ActualWidth() * WinLeft;
        else
            return Controller->Master->Client->Viewports(0)->SizeX * WinLeft;
    } else {
        if (bBoundToParent && MenuOwner)
            return MenuOwner->ActualLeft() + WinLeft;
        else
            return WinLeft;
    }
}
