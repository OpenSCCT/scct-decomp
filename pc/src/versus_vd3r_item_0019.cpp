// Work item 0019 (LTCG retry): Versus RVA 0x59a0.
// A constructor compiled with /GL and linked with /LTCG: `this` arrives in
// ESI, the owner in ECX and the index in EDX (both passed straight through to
// the base constructor at 0x4cd0). Class names are neutral; no vtable label or
// string identifies the engine's names.

// FArray from Unreal Engine 2: Add() is the published add_array at RVA 0x44e0.
class FArray {
public:
    int Add(int Count, int ElementSize);
    void **Data;
    int ArrayNum;
    int ArrayMax;
};

inline void *operator new(unsigned, void *where) { return where; }

struct UnnamedOwner_4cd0 {
    int Reserved0[3];
    unsigned short Padding0c;
    unsigned short NextIndex;        // +0x0e
    int Reserved10[4];
    FArray Nodes;                    // +0x20
};

class UnnamedNodeBase_4cd0 {
public:
    UnnamedNodeBase_4cd0(UnnamedOwner_4cd0 *owner)
    {
        Value4 = 0;
        Value8 = 0;
        Index = 0;
        Flags = 0x2000;
        Bits10 &= ~3u;
        Owner = owner;
        Value18 = 0;
        Value1c = 0;
        Value20 = 0;
        Value24 = 0;
        Value28 = 0;
        Value38 = 0;
    }
    virtual ~UnnamedNodeBase_4cd0();
    int Value4;
    int Value8;
    unsigned short Index;             // +0x0c
    unsigned short Flags;             // +0x0e
    unsigned Bits10;                  // +0x10, low two bits cleared
    UnnamedOwner_4cd0 *Owner;         // +0x14
    int Value18, Value1c, Value20, Value24, Value28;
    int Value2c, Value30, Value34;
    int Value38;
};

// RVA 0x4cd0 (matched separately in item_0008_ltcg).
class UnnamedNode_4cd0 : public UnnamedNodeBase_4cd0 {
public:
    UnnamedNode_4cd0(UnnamedOwner_4cd0 *owner, int index, int value);
    virtual ~UnnamedNode_4cd0();
    int Value3c;
};

UnnamedNode_4cd0::UnnamedNode_4cd0(UnnamedOwner_4cd0 *owner, int index, int value)
    : UnnamedNodeBase_4cd0(owner), Value3c(value)
{
    if (!index)
        index = owner->NextIndex++;
    Index = (unsigned short)index;
    FArray *nodes = &Owner->Nodes;
    nodes->Data[nodes->Add(1, sizeof(void *))] = this;
}

// 12-byte polymorphic sub-object (vtable 0x10c0f060) with two zeroed words.
class UnnamedSlot_59a0 {
public:
    UnnamedSlot_59a0() : A(0), B(0) {}
    virtual void Slot0();
    int A;
    int B;
};

// Value handed to the base constructor (retail global 0x10c91c10).
extern int GUnnamedValue_59a0;

// Intermediate class holding the slots; its destructor is RVA 0x5890. Its
// own vtable store is dead in the derived constructor and is removed.
class UnnamedBase_59a0 : public UnnamedNode_4cd0 {
public:
    UnnamedBase_59a0(UnnamedOwner_4cd0 *owner, int index)
        : UnnamedNode_4cd0(owner, index, GUnnamedValue_59a0), Value88(0) {}
    virtual ~UnnamedBase_59a0();
    UnnamedSlot_59a0 Slot40;          // +0x40
    UnnamedSlot_59a0 Slot4c;          // +0x4c
    UnnamedSlot_59a0 Slot58;          // +0x58
    UnnamedSlot_59a0 Slot64;          // +0x64
    UnnamedSlot_59a0 Slot70;          // +0x70
    UnnamedSlot_59a0 Slot7c;          // +0x7c
    int Value88;                      // +0x88
};

// RVA 0x59a0: vtable 0x10c0df60; its destructor is RVA 0x5940.
class UnnamedClass_59a0 : public UnnamedBase_59a0 {
public:
    UnnamedClass_59a0(UnnamedOwner_4cd0 *owner, int index);
    virtual ~UnnamedClass_59a0();
};

UnnamedClass_59a0::UnnamedClass_59a0(UnnamedOwner_4cd0 *owner, int index)
    : UnnamedBase_59a0(owner, index)
{
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_59a0(void **mem, UnnamedOwner_4cd0 *owner, int *index)
{
    Escape(&GUnnamedValue_59a0);
    new (mem[0]) UnnamedClass_59a0(owner, index[0]);
    new (mem[1]) UnnamedClass_59a0(owner, index[1]);
    new (mem[2]) UnnamedClass_59a0(owner, index[2]);
    new (mem[3]) UnnamedClass_59a0(owner, index[3]);
    new (mem[4]) UnnamedClass_59a0(owner, index[4]);
}
