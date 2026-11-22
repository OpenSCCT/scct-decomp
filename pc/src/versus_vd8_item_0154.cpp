// w4_item_0154.cpp -- Versus work item 0154 (RVA 0x160080)

#include "versus_build.h"
#include "unreal_containers.h"
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef char ANSICHAR;
typedef unsigned short TCHAR;

struct FGuid;
struct FStateFrame;

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

    INT           Index;
    BYTE          unk_8[0x4];
    FStateFrame  *StateFrame;
    BYTE          unk_10[0xc];
    DWORD         ObjectFlags;
    BYTE          unk_20[0x4];
    class UClass *Class;
};

// GUI.GUI: 0x2c bytes, 22 virtual functions
class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
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
    virtual UBOOL VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();

    BYTE    unk_2c[0x8];
    FString unk_34;
    FString unk_40;
    BYTE    unk_4c[0x18];
    FString unk_64;
    BYTE    unk_70[0x120];
};

// GUI.GUIMultiColumnListHeader: 0x19c bytes, 44 virtual functions
class UGUIMultiColumnListHeader : public UGUIComponent {
public:
    virtual ~UGUIMultiColumnListHeader();
    virtual UBOOL VirtualSlot35();

    BYTE unk_190[0x4];
    INT  unk_194;
    INT  unk_198;
};

// UGUIMultiColumnListHeader::VirtualSlot35 (RVA 0x160080)
UBOOL UGUIMultiColumnListHeader::VirtualSlot35()
{
    UGUIComponent::VirtualSlot35();
    unk_198 = -1;
    unk_194 = -1;
    return 1;
}
