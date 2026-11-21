// Work item 0192: Versus RVA 0xe2fc0-0xe3074 (LTCG-compiled object).
// 0xe2fc0: a script event thunk (name index 0xb4d, not recovered) taking an
//          FString and a DWORD; class not identified, neutral names.
// 0xe3050: C++ property constructor of a UProperty subclass whose vtable is
//          retail 0x10c0c948 (class not identified, neutral name). Same shape
//          as 0x60380: LTCG passes this in ESI and InOffset in ECX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short _WORD;

enum ECppProperty { EC_CppProperty };
enum EName { NAME_None, NAME_Unnamed_b4d = 0xb4d };

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString() {}
    ~FString();                                  // 0x48b0
    FString &operator=(const FString &Other);    // 0x4800
};

class UClass;
class UProperty;
class UFunction;

class UObject
{
public:
    virtual ~UObject();
    virtual void Virtual01();
    virtual void Virtual02();
    virtual void Virtual03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // +0x10
    virtual void Virtual05();
    virtual void Virtual06();
    virtual void Virtual07();
    virtual void Virtual08();
    virtual void Virtual09();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void AddCppProperty(UProperty *Property);   // +0x58

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0); // 0x16830

    DWORD Fields04[5];
    UObject *Outer;           // 0x18
    DWORD ObjectFlags;        // 0x1c
    FName Name;               // 0x20
    UClass *Class;            // 0x24
};

// ---------------------------------------------------------------------------
// RVA 0xe2fc0
class UnnamedObject_e2fc0 : public UObject
{
public:
    void eventUnnamed_b4d(const FString &S, DWORD D);
};

void UnnamedObject_e2fc0::eventUnnamed_b4d(const FString &S, DWORD D)
{
    struct Unnamed_b4d_Parms
    {
        FString S;
        DWORD D;
    } Parms;
    Parms.S = S;
    Parms.D = D;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_b4d), &Parms);
}

// ---------------------------------------------------------------------------
class UField : public UObject
{
public:
    UField *SuperField;       // 0x28
    UField *Next;             // 0x2c
    UField(UField *InSuperField) : SuperField(InSuperField) {}
};

class UProperty : public UField
{
public:
    _WORD ArrayDim;           // 0x30
    _WORD ElementSize;
    DWORD PropertyFlags;      // 0x34
    FName Category;           // 0x38
    INT Offset;               // 0x3c
    DWORD Fields40[3];
    UProperty *PropertyLinkNext; // 0x4c

    UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags);
    virtual ~UProperty();
};

// Retail 0x54140 (separate unit), defined here only so the linker gives it
// its retail convention (this on the stack, InFlags in ECX).
#pragma auto_inline(off)
UProperty::UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
: UField(0), ArrayDim(1), PropertyFlags(InFlags), Category(InCategory), Offset(InOffset), PropertyLinkNext(0)
{
    ((UField *)Outer)->AddCppProperty(this);
}
#pragma auto_inline(on)

// RVA 0xe3050
class UnnamedProperty_e3050 : public UProperty
{
public:
    DWORD Fields50[2];
    DWORD Extra;              // 0x58
    UnnamedProperty_e3050(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, DWORD InExtra);
    virtual ~UnnamedProperty_e3050();
};

UnnamedProperty_e3050::UnnamedProperty_e3050(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, DWORD InExtra)
: UProperty(EC_CppProperty, InOffset, InCategory, InFlags), Extra(InExtra)
{}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
void Driver_e2fc0(UnnamedObject_e2fc0 *O, const FString &S, DWORD D)
{
    O->eventUnnamed_b4d(S, D);
    O->eventUnnamed_b4d(S, D + 1);
    O->eventUnnamed_b4d(S, D + 2);
}

void *AllocProperty(unsigned int Size, UObject *Outer, FName Name, DWORD Flags);
inline void *operator new(unsigned int Size, UObject *Outer, FName Name, DWORD Flags)
{
    return AllocProperty(Size, Outer, Name, Flags);
}
void Driver_e3050(UObject *Outer, DWORD X)
{
    new (Outer, (EName)0x32, 4) UnnamedProperty_e3050(EC_CppProperty, 0x412c, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x33, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4130, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x34, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4134, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x35, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4138, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x36, 4) UnnamedProperty_e3050(EC_CppProperty, 0x413c, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x37, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4140, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x38, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4144, (EName)0x3c0, 0x4000, X);
    new (Outer, (EName)0x39, 4) UnnamedProperty_e3050(EC_CppProperty, 0x4148, (EName)0x3c0, 0x4000, X);
}
