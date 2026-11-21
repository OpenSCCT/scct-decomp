// Work item 0232: Versus RVA 0x57560, UStructProperty vtable slot 35.
// UE2 UStructProperty::CopyCompleteValue: copies each member property of the struct.
// Layouts as in published item 0098/0118 (UStructProperty::Struct at +0x58,
// UProperty::Offset at +0x3c, UProperty::CopyCompleteValue at vtable +0x90).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { CLASS_IsAUProperty = 0x8000 };

class UClass;
class UStruct;
class UObject
{
public:
    // vtable slots 0..35 (not recovered here)
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    BYTE Pad04[0x24 - 0x04];
    UClass *Class;          // +0x24
};
class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};
class UStruct : public UField
{
public:
    UField *Children;       // +0x30
    UStruct *GetInheritanceSuper();
};
class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
};

class UProperty : public UField
{
public:
    BYTE Pad30[0x3c - 0x30];
    INT Offset;             // +0x3c
    // vtable +0x90 (slot 36)
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *Obj);
};

class UStructProperty : public UProperty
{
public:
    BYTE Pad40[0x58 - 0x40];
    UStruct *Struct;        // +0x58
    UStructProperty() {}
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *Obj);
};

class TFieldIterator_UProperty
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator_UProperty(UStruct *InStruct)
        : Struct(InStruct), Field(InStruct ? InStruct->Children : 0)
    {
        IterateToNext();
    }
    operator UBOOL() { return Field != 0; }
    UProperty *operator->() { return (UProperty *)Field; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    void IterateToNext();
};

// RVA 0x1f850, bound separately (published with item 0098).
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

void UStructProperty::CopyCompleteValue(void *Dest, void *Src, UObject *Obj)
{
    for (TFieldIterator_UProperty It(Struct); It; ++It)
        It->CopyCompleteValue((BYTE *)Dest + It->Offset, (BYTE *)Src + It->Offset, Obj);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_57560(void *D, void *S, UObject *O)
{
    UStructProperty *P = new UStructProperty;
    Escape(P);
    P->CopyCompleteValue(D, S, O);
}
