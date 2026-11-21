// w4_item_0133.cpp -- Versus RVA 0x1591e0 (UGUIComponent::ActualTop)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

struct FGuid;

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object: 0x28 bytes, 22 virtual functions in Versus.
class UObject : public FUnknown
{
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

    INT Index;
    BYTE unk_08[0x20];
};

class UEngine;

class UViewport : public UObject
{
public:
    BYTE unk_28[0x78];
    INT SizeX;
    INT SizeY;
};

class UClient : public UObject
{
public:
    UEngine *Engine;
    TArray<UViewport *> Viewports;
};

class UInteractionMaster : public UObject
{
public:
    UClient *Client;
};

class UInteraction : public UObject
{
public:
    BYTE unk_28[0x8];
    UInteractionMaster *Master;
};

class UGUIController : public UInteraction
{
public:
};

class UGUI : public UObject
{
public:
    UGUIController *Controller;
};

class UGUIComponent : public UGUI
{
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual FLOAT ActualWidth();
    virtual FLOAT ActualHeight();
    virtual FLOAT ActualLeft();
    virtual FLOAT ActualTop();

    UGUIComponent *MenuOwner;
    BYTE unk_30[0x2c];
    BITFIELD bBoundToParent : 1;
    BITFIELD bScaleToParent : 1;
    BYTE unk_60[0x10];
    FLOAT WinTop;
    FLOAT WinLeft;
    FLOAT WinWidth;
    FLOAT WinHeight;
};

// UGUIComponent::ActualTop -- returns the component's top coordinate in viewport pixels.
FLOAT UGUIComponent::ActualTop()
{
    if (!Controller || !Controller->Master || !Controller->Master->Client ||
        !Controller->Master->Client->Viewports.Num() || !Controller->Master->Client->Viewports(0))
        return 0.0f;

    if (WinTop <= 1.0f) {
        if (bBoundToParent && MenuOwner)
            return (WinTop * MenuOwner->ActualHeight()) + MenuOwner->ActualTop();
        return WinTop * Controller->Master->Client->Viewports(0)->SizeY;
    }

    if (bBoundToParent && MenuOwner)
        return MenuOwner->ActualTop() + WinTop;

    return WinTop;
}
