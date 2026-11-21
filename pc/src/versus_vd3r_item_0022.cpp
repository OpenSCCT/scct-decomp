// Work item 0022 (LTCG retry): Versus RVA 0x5c20 (destructor) and 0x5ca0
// (constructor) of one window-like object class. Both were compiled with
// VC7.0 /GL and linked with /LTCG, which passes `this` on the stack (the
// constructor also receives the outer object in ECX and hands it on to the
// base constructor at RVA 0x5a30).
// Class names are neutral: no vtable label names the class (the constructor
// reads "<Name>.Split" from the "WindowPositions" config section and adds the
// object to a global list).
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef int INT;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;

// FArray from Unreal Engine 2; Add is the published add_array (RVA 0x44e0),
// Remove is retail 0x109119c0.
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

// FString from Unreal Engine 2 (constructor 0x109046c0, destructor
// 0x109048b0, operator+ 0x10904990).
extern const TCHAR EmptyString[];       // TEXT("") in writable data
class FString : public FArray
{
public:
    FString(const TCHAR* In);
    ~FString();
    FString operator+(const TCHAR* Str) const;
    const TCHAR* operator*() const { return ArrayNum ? (const TCHAR*)Data : EmptyString; }
};

// The global name table (FName::Names); entries keep their text at +0x0c.
struct FNameEntry
{
    DWORD Index;
    DWORD HashNext;
    DWORD Flags;
    TCHAR Name[64];
};
struct FNameTable
{
    FNameEntry** Data;
    INT ArrayNum;
    INT ArrayMax;
};
extern FNameTable FName_Names;

// The configuration cache (GConfig); slot 1 reads one integer value.
class UnnamedConfig
{
public:
    virtual void Slot0();
    virtual INT GetValue(const TCHAR* Section, INT Reserved, const TCHAR* Key, INT& Value, const TCHAR* Filename);
};
extern UnnamedConfig* GConfig;

extern const TCHAR WindowPositionsSection[];    // TEXT("WindowPositions")
extern const TCHAR SplitKeySuffix[];            // TEXT(".Split")

// The primary base: vtable at 0x00, object flags at 0x10, size 0x3c.
class UnnamedRoot_5c20
{
public:
    UnnamedRoot_5c20(DWORD InName, UnnamedRoot_5c20* InOuter)
    {
        Field04 = 0;
        Name = InName;
        Index = 0;
        Flags = 0x2000;
        Destroyed = 0;
        BitB = 0;
        Outer = InOuter;
        Field18 = Field1C = Field20 = Field24 = Field28 = 0;
        Field38 = 0;
    }
    virtual void Slot0();
    virtual ~UnnamedRoot_5c20();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Destroy();                 // vtable slot 5
    virtual void Slot6();
    DWORD Field04;
    DWORD Name;                             // 0x08: index into the global name table
    unsigned short Index;                   // 0x0c
    unsigned short Flags;                   // 0x0e
    unsigned Destroyed : 1;                 // 0x10
    unsigned BitB : 1;
    UnnamedRoot_5c20* Outer;                // 0x14
    DWORD Field18, Field1C, Field20, Field24, Field28;
    DWORD Field2C, Field30, Field34;
    DWORD Field38;
};

// The secondary base at 0x3c.
class UnnamedHook_5c20
{
public:
    UnnamedHook_5c20() : HookValue(1) {}
    virtual void HookSlot0();
    virtual void HookSlot1();
    virtual void HookSlot2();
    virtual void HookSlot3();
    DWORD HookValue;                        // 0x40
};

// A bound callback: an object and a member function of it.
typedef void (UnnamedRoot_5c20::*UnnamedCallback)();
class UnnamedDelegate_5c20
{
public:
    UnnamedDelegate_5c20() : Object(0), Func(0) {}
    virtual void Execute();
    void Bind(UnnamedRoot_5c20* InObject, UnnamedCallback InFunc)
    {
        Object = InObject;
        Func = InFunc;
    }
    UnnamedRoot_5c20* Object;
    UnnamedCallback Func;
};

// List node (constructor at RVA 0x4cd0).
class UnnamedNode_4cd0
{
public:
    UnnamedNode_4cd0(INT Index, UnnamedRoot_5c20* Owner, DWORD Value);
    virtual ~UnnamedNode_4cd0();
    DWORD NodeFields[6];
    UnnamedHook_5c20* Hook;                 // 0x1c
    DWORD NodeFields2[8];
};
extern DWORD GUnnamedNodeValue;             // retail 0x10c91c10

// Member of the base at 0x44 (constructor at RVA 0x59a0, destructor at RVA
// 0x5940): a list node followed by six callbacks.
class UnnamedMember44_5c20 : public UnnamedNode_4cd0
{
public:
    __declspec(noinline) UnnamedMember44_5c20(UnnamedRoot_5c20* Owner, INT Index)
        : UnnamedNode_4cd0(Index, Owner, GUnnamedNodeValue), Field88(0) {}
    ~UnnamedMember44_5c20();
    UnnamedDelegate_5c20 Callbacks[6];      // 0x40
    DWORD Field88;
};

// Base class: constructor at RVA 0x5a30, destructor at RVA 0x5b00.
class UnnamedBase_5c20 : public UnnamedRoot_5c20, public UnnamedHook_5c20
{
public:
    UnnamedMember44_5c20 Member44;          // 0x44
    DWORD FieldD0;                          // 0xd0
    __declspec(noinline) UnnamedBase_5c20(DWORD InName, UnnamedRoot_5c20* InOuter)
        : UnnamedRoot_5c20(InName, InOuter), Member44(this, 0)
    {
        FieldD0 = 0;
        Member44.Hook = this;
    }
    __declspec(noinline) ~UnnamedBase_5c20() {}
};

// Array member at 0xd4 of 8-byte elements (destructor at retail 0x10a7f6a0).
class UnnamedArray_5c20 : public FArray
{
public:
    __declspec(noinline) ~UnnamedArray_5c20() { Remove(0, ArrayNum, 8); }
};

// Every object of the class is kept in this list (retail 0x10c97784).
extern FArray GUnnamedWindows;

class UnnamedClass_5c20 : public UnnamedBase_5c20
{
public:
    UnnamedArray_5c20 Items;                // 0xd4
    DWORD FieldE0[4];
    DWORD FieldF0;
    INT SplitPosition;                      // 0xf4
    DWORD FieldF8;
    DWORD FieldFC;
    DWORD Field100;
    UnnamedClass_5c20(DWORD InName, UnnamedRoot_5c20* InOuter);
    ~UnnamedClass_5c20();
    // Overrides (vtable 0x10c0e610 slots 3-6; secondary vtable 0x10c0e600).
    virtual void Slot3();
    virtual void Slot4();
    // Retail calls slot 5 through the vtable's memory slot (`call
    // [vftable+0x14]`); declared dllimport to reproduce that indirect call
    // (same shape as the matched destructor at RVA 0x5150).
    __declspec(dllimport) virtual void Destroy();
    virtual void Slot6();
    virtual void HookSlot0();
    virtual void HookSlot1();
    virtual void HookSlot2();
    virtual void HookSlot3();
    // Callback handlers (retail 0x10b1b880 and 0x10b1b890).
    void OnCallback0();
    void OnCallback1();
};

// RVA 0x5ca0
UnnamedClass_5c20::UnnamedClass_5c20(DWORD InName, UnnamedRoot_5c20* InOuter)
    : UnnamedBase_5c20(InName, InOuter)
{
    FieldF0 = 0;
    SplitPosition = 0x80;
    FieldFC = 0;
    Field100 = 0;
    if (Name)
        GConfig->GetValue(WindowPositionsSection, 0,
                          *(FString(FName_Names.Data[Name]->Name) + SplitKeySuffix),
                          SplitPosition, 0);
    ((UnnamedClass_5c20**)GUnnamedWindows.Data)[GUnnamedWindows.Add(1, sizeof(UnnamedClass_5c20*))] = this;
    Member44.Callbacks[0].Bind(this, static_cast<UnnamedCallback>(&UnnamedClass_5c20::OnCallback0));
    Member44.Callbacks[1].Bind(this, static_cast<UnnamedCallback>(&UnnamedClass_5c20::OnCallback1));
    FieldF8 = 1;
}

// RVA 0x5c20
UnnamedClass_5c20::~UnnamedClass_5c20()
{
    if (!Destroyed)
    {
        Destroyed = 1;
        Destroy();
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned, void *Where) { return Where; }
void Driver_5c20(UnnamedClass_5c20* A) { Escape(&GMalloc); A->UnnamedClass_5c20::~UnnamedClass_5c20(); }
void Driver_5ca0(void* MemA, void* MemB, DWORD InName, UnnamedRoot_5c20* InOuter)
{
    Escape(&GConfig);
    Escape(&FName_Names);
    Escape(&GUnnamedWindows);
    new (MemA) UnnamedClass_5c20(InName, InOuter);
    new (MemB) UnnamedClass_5c20(InName, 0);
}
