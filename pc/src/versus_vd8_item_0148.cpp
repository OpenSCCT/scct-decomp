// w4_item_0148.cpp -- UGUIList sorting (CompareListElem, FGUIListElem copy ctor, UGUIList::execSortList)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef int UBOOL;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *String1, const TCHAR *String2);
extern "C" __declspec(dllimport) void __cdecl qsort(
    void *Base,
    unsigned int Num,
    unsigned int Width,
    INT (__cdecl *Compare)(const void *, const void *));

struct FGuid;

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

    BYTE unk_4[0x24];
};

class FName {
public:
    INT Index;
};

struct FScriptDelegate {
    UObject *Object;
    FName FunctionName;
};

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

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
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

struct FGUIListElem {
    FString Item;
    UObject *ExtraData;
    FString ExtraStrData;
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

    BYTE unk_2c[0x164];
};

class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void VirtualSlot44();

    BYTE unk_190[0x40];
};

class UGUIVertList : public UGUIListBase {
public:
    virtual ~UGUIVertList();
};

class UGUIList : public UGUIVertList {
public:
    virtual ~UGUIList();

    BYTE unk_1d0[0x4];
    TArray<FGUIListElem> Elements;
    BYTE unk_1e0[0x4];
    FScriptDelegate __CompareItem__Delegate;

    INT delegateCompareItem(FGUIListElem ElemA, FGUIListElem ElemB);
    void execSortList(FFrame &Stack, void *const Result);
};

// File-scope pointer holding the list currently being sorted by qsort (originally static).
extern UGUIList *GSortingList;

// CompareListElem -- qsort comparator for UGUIList::Elements (RVA 0x15e170)
INT __cdecl CompareListElem(const void *A, const void *B)
{
    const FGUIListElem *ElemA = (const FGUIListElem *)A;
    const FGUIListElem *ElemB = (const FGUIListElem *)B;
    if (GSortingList)
        return GSortingList->delegateCompareItem(*ElemA, *ElemB);
    return _wcsicmp(*ElemA->Item, *ElemB->Item);
}

// UGUIList::execSortList (RVA 0x15e290)
void UGUIList::execSortList(FFrame &Stack, void *const Result)
{
    Stack.Code++;
    if (__CompareItem__Delegate.Object && !__CompareItem__Delegate.Object->IsPendingKill())
        GSortingList = this;
    else
        GSortingList = 0;
    qsort(&Elements(0), Elements.Num(), sizeof(FGUIListElem), CompareListElem);
}

// Scaffolding for LTCG link, not part of the unit.
void Escape(void *);
void Driver_15e170(UGUIList *List, FFrame *Stack, void *Result)
{
    Escape(&GSortingList);
    List->execSortList(*Stack, Result);
}
