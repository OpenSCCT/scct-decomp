// Work item 0399: Versus RVA 0xa7d70 and 0xa7df0.
//
// Both functions come from a link-time code generation (LTCG) object: the
// member destructors 0xa7d70 and 0x10a7bf30 (TArray<DWORD>::~TArray) take
// `this` on the stack. Check with try_ltcg.py, rooted at the two drivers at
// the end of the file.
//
// Names are neutral where no vtable label identifies a class: UnnamedClass_a7df0
// (vtables at retail 0x10c092b0 / 0x10c0929c) derives from the UObject-based
// class destroyed by RVA 0x115ee0, which has a second vtable at +0x28.
// The destructor's call to Destroy() binds to the vtable slot the retail code
// reads ([vftable + 0x24]); it is written as a qualified call through a
// dllimport declaration so the verifier binds that address by name.
typedef unsigned long DWORD;

class FString
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;
    ~FString();                                 // RVA 0x48b0
};

class TArray_FString
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;
    ~TArray_FString();                          // RVA 0xc5f0
};

// Member record destroyed by RVA 0xa7d70.
struct UnnamedRecord_a7d70
{
    FString Name;           // 0x00
    FString Text;           // 0x0c
    DWORD Value18;          // 0x18
    FString Extra;          // 0x1c
    TArray_FString List;    // 0x28
    FString Tail;           // 0x34
    ~UnnamedRecord_a7d70();
};

// Retail RVA 0xa7d70 (LTCG: `this` on the stack, ret 4).
UnnamedRecord_a7d70::~UnnamedRecord_a7d70()
{
}

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const unsigned short* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const unsigned short* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;

class FArray
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;
    void Remove(int Index, int Count, int ElementSize);    // RVA 0x119c0
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
        ArrayNum = 0;
    }
};

template<class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
};

// TArray<DWORD>::~TArray is retail 0x10a7bf30 (this on the stack).
struct UnnamedEntry_10
{
    TArray<DWORD> List;
    DWORD Value;
};

struct UnnamedEntry_18
{
    TArray<DWORD> List;
    DWORD Values[3];
};

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    __declspec(dllimport) virtual void Destroy();
    int Index;              // 0x04
    DWORD Reserved[5];
    DWORD ObjectFlags;      // 0x1c
    DWORD Name;             // 0x20
    void* Class;            // 0x24
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            UObject::Destroy();
            return 1;
        }
        return 0;
    }
};

class UnnamedInterface_a7df0
{
public:
    virtual void InterfaceSlot0();
};

class UnnamedBase_115ee0 : public UObject, public UnnamedInterface_a7df0
{
public:
    virtual ~UnnamedBase_115ee0();
};

class UnnamedClass_a7df0 : public UnnamedBase_115ee0
{
public:
    UnnamedEntry_10 Array2C;
    UnnamedEntry_10 Array3C;
    UnnamedEntry_10 Array4C;
    UnnamedEntry_10 Array5C;
    UnnamedEntry_10 Array6C;
    UnnamedEntry_10 Array7C;
    UnnamedEntry_10 Array8C;
    UnnamedEntry_10 Array9C;
    UnnamedEntry_10 ArrayAC;
    UnnamedEntry_10 ArrayBC;
    UnnamedEntry_10 ArrayCC;
    UnnamedEntry_18 ArrayDC;
    UnnamedRecord_a7d70 Record;     // 0xf4
    virtual ~UnnamedClass_a7df0();
};

// Retail RVA 0xa7df0.
UnnamedClass_a7df0::~UnnamedClass_a7df0()
{
    ConditionalDestroy();
}

// Scaffolding for the link, not part of the unit.
void Driver_a7df0(UnnamedClass_a7df0* P) { P->UnnamedClass_a7df0::~UnnamedClass_a7df0(); }
void Driver_a7d70(UnnamedRecord_a7d70* P) { P->~UnnamedRecord_a7d70(); }
