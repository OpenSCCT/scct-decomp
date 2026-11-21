// Work item 0144: Versus RVA 0x3e600 (destructor) and 0x3e6b0 (constructor).
//
// Names are neutral: no vtable label identifies these classes.
// UnnamedClass_3e600 derives from UnnamedBase_3e520 (an Unreal object class:
// constructor RVA 0x3e520, destructor RVA 0x3e450, vtable 0x10c0c530) and from
// UnnamedInterface_a4, a small polymorphic base placed at +0xa4 (vtable
// 0x10c0e918) whose constructor and destructor are inline. The class adds a
// TArray-like member at +0x4ec.
typedef unsigned long DWORD;
typedef int INT;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class __declspec(novtable) UObject {
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
    virtual void Destroy();
    INT Index;
    DWORD Reserved[5];
    DWORD ObjectFlags;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Parent class: constructor RVA 0x3e520, destructor RVA 0x3e450.
// Retail RVA 0x3e520: the parent constructor. Link-time code generation gave
// it `this` on the stack, so it is declared as the __stdcall function the
// linker made of it.
class UnnamedBase_3e520;
void __stdcall UnnamedBase_3e520_Construct(UnnamedBase_3e520 *Self);

class __declspec(novtable) UnnamedBase_3e520 : public UObject {
public:
    UnnamedBase_3e520() { UnnamedBase_3e520_Construct(this); }
    virtual ~UnnamedBase_3e520();
    DWORD BaseData[(0xa4 - 0x20) / 4];
};

// Polymorphic base at +0xa4 (vtable 0x10c0e918).
class UnnamedInterface_a4 {
public:
    virtual void InterfaceSlot0();
    DWORD Field04;
    DWORD Field08;
    DWORD Field0C;
    DWORD Field10;
    DWORD Field14;
    DWORD Field18;
    DWORD Field1C;
    DWORD Field20;
    DWORD Field24;
    DWORD Field28;
    DWORD Field2C;
    DWORD Field30;
    DWORD Field34;
    DWORD Field38;
    DWORD Field3C;
    UnnamedInterface_a4()
    {
        Field0C = 0;
        Field10 = 0;
        Field14 = 0;
        Field18 = 0;
        Field1C = 0;
        Field2C = 0;
        Field30 = 0;
        Field38 = 0;
        Field04 = 0xaf;
        Field08 = 2000;
        Field20 = 1;
        Field24 = 1;
        Field28 = 1;
        Field34 = 3;
        Field3C = 0xffffffff;
    }
    ~UnnamedInterface_a4() {}
};

// Retail 0x10a7bf30: releases a TArray-like member, `this` on the stack.
void __stdcall UnnamedArray_Release(void *Array);

struct UnnamedArray {
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    UnnamedArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~UnnamedArray() { UnnamedArray_Release(this); }
};

class UnnamedClass_3e600 : public UnnamedBase_3e520, public UnnamedInterface_a4 {
public:
    UnnamedClass_3e600();
    virtual ~UnnamedClass_3e600();
    DWORD Data[(0x4ec - 0xe4) / 4];
    UnnamedArray Array;
};

// Retail RVA 0x3e600.
UnnamedClass_3e600::~UnnamedClass_3e600()
{
    ConditionalDestroy();
}

// Retail RVA 0x3e6b0.
UnnamedClass_3e600::UnnamedClass_3e600()
{
}

// Scaffolding for the link, not part of the unit: the InternalConstructor
// helper retail calls the constructor from (RVA 0x3e6a0).
enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) throw() { return (void *)Mem; }
void Driver_3e6b0(void *X) { new ((EInternal *)X) UnnamedClass_3e600; }
