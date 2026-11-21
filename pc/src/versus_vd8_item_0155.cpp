// w4_item_0155.cpp -- UGUIMultiColumnListHeader::MouseHover (Versus RVA 0x1601f0)

typedef unsigned char  BYTE;
typedef unsigned short TCHAR;
typedef int            INT;
typedef unsigned long  DWORD;
typedef DWORD          UBOOL;
typedef float          FLOAT;

struct FGuid;
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

class UGUIController : public UObject {
public:
    BYTE unk_28[0xca4];
    INT  MouseX;
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
    virtual UBOOL MouseHover();
    virtual void  VirtualSlot37();
    virtual void  VirtualSlot38();
    virtual void  VirtualSlot39();
    virtual void  VirtualSlot40();
    virtual void  VirtualSlot41();
    virtual void  VirtualSlot42();
    virtual void  VirtualSlot43();

    BYTE    unk_2c[0x8];
    FString unk_34;
    FString unk_40;
    BYTE    unk_4c[0x18];
    FString unk_64;
    BYTE    unk_70[0x14];
    INT     MouseCursorIndex;
    BYTE    unk_88[0x108];
};

class UGUIMultiColumnList : public UGUIComponent {
public:
    BYTE          unk_190[0xc8];
    TArray<FLOAT> ColumnWidths;
};

class UGUIMultiColumnListHeader : public UGUIComponent {
public:
    virtual ~UGUIMultiColumnListHeader();
    virtual UBOOL MouseHover();

    UGUIMultiColumnList *MyList;
    BYTE                 unk_194[0x8];
};

// UGUIMultiColumnListHeader::MouseHover (vtable slot 36)
UBOOL UGUIMultiColumnListHeader::MouseHover()
{
    INT SizingCol = -1;
    FLOAT x = ActualLeft();

    for (INT i = 0; i < MyList->ColumnWidths.Num() && SizingCol == -1; i++) {
        x += MyList->ColumnWidths(i);
        if (x >= Controller->MouseX - 2.0f && x <= Controller->MouseX + 2.0f)
            SizingCol = i;
    }

    if (SizingCol != -1)
        MouseCursorIndex = 5;
    else
        MouseCursorIndex = 0;

    return 0;
}
