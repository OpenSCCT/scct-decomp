// Work item w3 0177: Versus RVA 0xdf840-0xdfcae.
// Class names are neutral (no vtable label or string names these classes).
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef float FLOAT;
typedef DWORD UBOOL;

// FArray from Unreal Engine 2; Remove is retail 0x109119c0.
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize);
};

// ---------------------------------------------------------------------------
// RVA 0xdfc20: tear-down of an object registered in an owner's tables.
// ---------------------------------------------------------------------------
class UnnamedChild_dfc20
{
public:
    virtual ~UnnamedChild_dfc20();
    char Pad04[0x4c];
    UnnamedChild_dfc20* Next;           // +0x50
};

class UnnamedOwner_dfc20;

class UnnamedBase_dfc20
{
public:
    void Destroy();                     // retail 0x10915ce0
};

class UnnamedObject_dfc20 : public UnnamedBase_dfc20
{
public:
    char Pad00[0x28];
    UnnamedOwner_dfc20* Owner;          // +0x28
    INT Slot;                           // +0x2c
    char Pad30[0x10];
    UnnamedChild_dfc20* ListA;          // +0x40
    UnnamedChild_dfc20* ListB;          // +0x44
    void Destroy();
};

class UnnamedOwner_dfc20
{
public:
    char Pad00[0xef0];
    UnnamedObject_dfc20* Slots[(0x26fc - 0xef0) / 4];  // +0xef0
    FArray Objects;                     // +0x26fc, TArray<UnnamedObject_dfc20*>
};

void UnnamedObject_dfc20::Destroy()
{
    UnnamedChild_dfc20* Child;
    UnnamedChild_dfc20* Next;
    for (Child = ListB; Child; Child = Next)
    {
        Next = Child->Next;
        delete Child;
    }
    for (Child = ListA; Child; Child = Next)
    {
        Next = Child->Next;
        delete Child;
    }
    FArray& Objects = Owner->Objects;
    for (INT i = 0; i < Objects.ArrayNum; i++)
    {
        if (((UnnamedObject_dfc20**)Objects.Data)[i] == this)
            Objects.Remove(i--, 1, sizeof(UnnamedObject_dfc20*));
    }
    Owner->Slots[Slot] = 0;
    Owner = 0;
    UnnamedBase_dfc20::Destroy();
}
