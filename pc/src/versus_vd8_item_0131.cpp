// w4_item_0131.cpp -- UGUIComponent::PerformInBounds (Versus RVA 0x158f70)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;
typedef DWORD BITFIELD;

struct FGuid;
struct FStateFrame;
class UClass;

struct FName {
    INT Index;
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
    virtual UBOOL IsPendingKill();
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

struct FScriptDelegate {
    UObject *Object;
    FName    FunctionName;
};

#define DELEGATE_IS_SET(del) \
    (__##del##__Delegate.Object != 0 && !__##del##__Delegate.Object->IsPendingKill())

// MenuState values (standard UE2 eMenuState convention)
enum eMenuState {
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

// GUI.GUIComponent (0x190 bytes, 44 virtual functions).
// Method and field names below follow standard UE2 GUI conventions where no symbol
// table names them directly.
class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual UBOOL PerformInBounds(INT MouseX, INT MouseY);

    UGUIComponent  *MenuOwner;
    BYTE            MenuState;
    BYTE            unk_31[0x2b];
    BITFIELD        bBoundToParent : 1;
    BITFIELD        bScaleToParent : 1;
    BITFIELD        unk_5c_2       : 1;
    BITFIELD        bVisible       : 1;
    BITFIELD        bAcceptsInput  : 1;
    BYTE            unk_60[0x40];
    FLOAT           Bounds[4];
    BYTE            unk_b0[0x60];
    FScriptDelegate __OnHitTest__Delegate;
    BYTE            unk_118[0x78];

    void delegateOnHitTest(FLOAT MouseX, FLOAT MouseY);
};

// UGUIComponent::PerformInBounds (vtable slot 24, RVA 0x158f70)
UBOOL UGUIComponent::PerformInBounds(INT MouseX, INT MouseY)
{
    if (!bVisible || !bAcceptsInput || MenuState == MSAT_Disabled)
        return 0;

    if (DELEGATE_IS_SET(OnHitTest))
        delegateOnHitTest((FLOAT)MouseX, (FLOAT)MouseY);

    if (MouseX >= Bounds[0] && MouseX <= Bounds[2] &&
        MouseY >= Bounds[1] && MouseY <= Bounds[3])
        return 1;

    return 0;
}
