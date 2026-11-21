// Work item 0227 (LTCG): RVA 0xef2c0 and 0xef330.
// Helpers over an owner object (reached from exec natives through
// Level->Game-like pointers) holding a TArray of per-player records (+0x2c)
// and an 8-entry slot list (+0x4fc); each record carries a key (+0x30) and
// its own 8-entry slot list (+0x49c0). UpdateSlot adds a value to a list
// (or removes it when bRemove); the callees at RVA 0xef3d0 and 0x10e9f0 are
// in this file too, kept out of line as in retail. A key object is Cast to
// a fixed class (retail 0x10cc6ce8) and asked a virtual question (vtable
// slot 0x140). The classes are not identified, so the names are neutral
// (UnnamedOwner_ef2c0 etc.). Retail compiled these with /GL: values arrive
// in EAX/EBX/ESI/EDI as the linker chose.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UClass;

class UObject
{
public:
    // Vtable slot 0x140 (80) is the virtual question asked of the key.
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47();
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62(); virtual void V63();
    virtual void V64(); virtual void V65(); virtual void V66(); virtual void V67();
    virtual void V68(); virtual void V69(); virtual void V70(); virtual void V71();
    virtual void V72(); virtual void V73(); virtual void V74(); virtual void V75();
    virtual void V76(); virtual void V77(); virtual void V78(); virtual void V79();
    virtual UBOOL Query140();
    char Pad04[0x20];
    UClass *Class;          // +0x24
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass *SuperClass;     // +0x28 (SuperField)
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = C->SuperClass)
        if (C == SomeBase)
            return 1;
    return 0;
}

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

// Retail 0x10cc6ce8: the class the key is cast to.
extern UClass UnnamedKeyClass_ef2c0_StaticClass;



inline UObject *CastKey(UObject *Src)
{
    return Src && Src->IsA(&UnnamedKeyClass_ef2c0_StaticClass) ? Src : 0;
}

struct UnnamedRecord_ef2c0
{
    char Pad00[0x30];
    UObject *Key;           // +0x30
    char Pad34[0x49c0 - 0x34];
    INT Slots[8];           // +0x49c0
    void UpdateSlot(INT Value, UBOOL bRemove);   // RVA 0x10e9f0
};

struct UnnamedOwner_ef2c0
{
    char Pad00[0x2c];
    TArray<UnnamedRecord_ef2c0 *> Records;   // +0x2c
    char Pad38[0x4fc - 0x38];
    INT Slots[8];           // +0x4fc
    void UpdateSlot(INT Value, UBOOL bRemove);   // RVA 0xef3d0
    void UpdateKeySlots(INT Value, UObject *Key, UBOOL bRemove);   // RVA 0xef2c0
    UBOOL IsSlotFree(UObject *Key, INT Value);   // RVA 0xef330
};

__declspec(noinline) void UnnamedRecord_ef2c0::UpdateSlot(INT Value, UBOOL bRemove)
{
    if (bRemove)
    {
        for (INT i = 0; i < 8; i++)
            if (Slots[i] == Value)
                Slots[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (Slots[i] == Value)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (Slots[i] == 0)
                {
                    Slots[i] = Value;
                    break;
                }
        }
    }
}

__declspec(noinline) void UnnamedOwner_ef2c0::UpdateSlot(INT Value, UBOOL bRemove)
{
    if (bRemove)
    {
        for (INT i = 0; i < 8; i++)
            if (Slots[i] == Value)
                Slots[i] = 0;
    }
    else
    {
        INT i;
        for (i = 0; i < 8; i++)
            if (Slots[i] == Value)
                break;
        if (i == 8)
        {
            for (i = 0; i < 8; i++)
                if (Slots[i] == 0)
                {
                    Slots[i] = Value;
                    break;
                }
        }
    }
}

// RVA 0xef2c0: Value in EAX.
void UnnamedOwner_ef2c0::UpdateKeySlots(INT Value, UObject *Key, UBOOL bRemove)
{
    for (INT i = 0; i < Records.Num(); i++)
    {
        UnnamedRecord_ef2c0 *Record = Records(i);
        if (Record->Key == Key)
            Record->UpdateSlot(Value, bRemove);
    }
    if (CastKey(Key)->Query140())
        UpdateSlot(Value, bRemove);
}

// RVA 0xef330: Key in EBX.
UBOOL UnnamedOwner_ef2c0::IsSlotFree(UObject *Key, INT Value)
{
    for (INT i = 0; i < Records.Num(); i++)
    {
        UnnamedRecord_ef2c0 *Record = Records(i);
        if (Record->Key == Key)
            for (INT j = 0; j < 8; j++)
                if (Record->Slots[j] == Value)
                    return 0;
    }
    if (CastKey(Key)->Query140())
        for (INT j = 0; j < 8; j++)
            if (Slots[j] == Value)
                return 0;
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_ef2c0(UObject *Key, UnnamedOwner_ef2c0 *Owner, INT Value, UBOOL bRemove)
{
    Escape(&UnnamedKeyClass_ef2c0_StaticClass);
    if (Owner)
        Owner->UpdateKeySlots(Value, Key, bRemove);
}
INT Driver_ef330(UObject *Key, UnnamedOwner_ef2c0 *Owner, INT Value)
{
    Escape(&UnnamedKeyClass_ef2c0_StaticClass);
    INT r = Owner->IsSlotFree(Key, Value);
    Escape(Owner);
    return r + Owner->IsSlotFree(Key, Value);
}
