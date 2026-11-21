// Work item 0332: Versus RVA 0x10d970 (LTCG: this on the stack with ret 4, Value in EBX).
// Class names are neutral; no vtable label identifies them.
typedef int INT;

struct UnnamedElement_10d970
{
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25();
    virtual void Notify(INT Value);          // slot 0x68
    INT Pad04[11];
    INT Key;                                 // +0x30
};

struct UnnamedOwner_10d970
{
    char Pad[0x26fc];
    UnnamedElement_10d970 **Elements;        // +0x26fc (TArray data)
    INT ElementCount;                        // +0x2700 (TArray num)
    void NotifyElements(INT Value);
};

void FUN_109dfcb0();

__declspec(noinline) void UnnamedOwner_10d970::NotifyElements(INT Value)
{
    for (INT i = ElementCount - 1; i >= 0; i--)
    {
        UnnamedElement_10d970 *E = Elements[i];
        E->Notify(Value);
        if (E->Key == Value)
            FUN_109dfcb0();
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_10d970(UnnamedOwner_10d970 *Owner, INT Value)
{
    Owner->NotifyElements(Value);
    Owner->NotifyElements(Value + 1);
}
