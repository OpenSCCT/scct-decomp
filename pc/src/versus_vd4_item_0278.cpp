// Work item 0278: Versus RVA 0x6a620 (destructor), 0x6a700 (constructor of a
// derived record) and 0x6a790 (constructor). Built with VC7.0 /GL and linked
// with /LTCG, which gives the custom conventions seen in retail (`this` in
// ESI or on the stack, owner in EDI).
//
// Neutral names: no vtable label or string identifies these classes. A
// record links itself into a singly linked list headed at +0x40b4 of its
// owner and keeps a TArray-like buffer at +0x448.
typedef unsigned long DWORD;
typedef int INT;

// COM-style interface (stdcall methods, `this` pushed) reached through
// +0x46a4 of the owning device.
struct UnnamedInterface_6a620
{
    virtual void __stdcall Slot00(); virtual void __stdcall Slot01(); virtual void __stdcall Slot02();
    virtual void __stdcall Slot03(); virtual void __stdcall Slot04(); virtual void __stdcall Slot05();
    virtual void __stdcall Slot06(); virtual void __stdcall Slot07(); virtual void __stdcall Slot08();
    virtual void __stdcall Slot09(); virtual void __stdcall Slot10(); virtual void __stdcall Slot11();
    virtual void __stdcall Slot12(); virtual void __stdcall Slot13(); virtual void __stdcall Slot14();
    virtual void __stdcall Slot15(); virtual void __stdcall Slot16(); virtual void __stdcall Slot17();
    virtual void __stdcall Slot18(); virtual void __stdcall Slot19(); virtual void __stdcall Slot20();
    virtual void __stdcall Slot21(); virtual void __stdcall Slot22(); virtual void __stdcall Slot23();
    virtual void __stdcall Slot24(); virtual void __stdcall Slot25(); virtual void __stdcall Slot26();
    virtual void __stdcall Slot27(); virtual void __stdcall Slot28(); virtual void __stdcall Slot29();
    virtual void __stdcall Slot30(); virtual void __stdcall Slot31(); virtual void __stdcall Slot32();
    virtual void __stdcall Slot33(); virtual void __stdcall Slot34(); virtual void __stdcall Slot35();
    virtual void __stdcall Slot36(); virtual void __stdcall Slot37(); virtual void __stdcall Slot38();
    virtual void __stdcall Slot39(); virtual void __stdcall Slot40(); virtual void __stdcall Slot41();
    virtual void __stdcall Slot42(); virtual void __stdcall Slot43(); virtual void __stdcall Slot44();
    virtual void __stdcall Slot45(); virtual void __stdcall Slot46(); virtual void __stdcall Slot47();
    virtual void __stdcall Slot48(); virtual void __stdcall Slot49(); virtual void __stdcall Slot50();
    virtual void __stdcall Slot51(); virtual void __stdcall Slot52(); virtual void __stdcall Slot53();
    virtual void __stdcall Slot54(); virtual void __stdcall Slot55(); virtual void __stdcall Slot56();
    virtual void __stdcall Slot57(); virtual void __stdcall Slot58(); virtual void __stdcall Slot59();
    virtual void __stdcall Slot60(); virtual void __stdcall Slot61(); virtual void __stdcall Slot62();
    virtual void __stdcall Slot63(); virtual void __stdcall Slot64(); virtual void __stdcall Slot65();
    virtual void __stdcall Slot66(); virtual void __stdcall Slot67(); virtual void __stdcall Slot68();
    virtual void __stdcall Slot69(); virtual void __stdcall Slot70(); virtual void __stdcall Slot71();
    virtual void __stdcall Slot72(); virtual void __stdcall Slot73(); virtual void __stdcall Slot74();
    virtual void __stdcall Create(void *Data, INT Reserved, INT *Handle, DWORD Flags);   // +0x12c
    virtual void __stdcall SetMode(INT Mode);                                            // +0x130
    virtual void __stdcall Slot77();
    virtual void __stdcall Release(INT Handle);                                          // +0x138
};

struct UnnamedDevice_6a620
{
    char Pad0[0x46a4];
    UnnamedInterface_6a620 *Interface;  // +0x46a4
};

struct UnnamedSlot_6a620
{
    UnnamedDevice_6a620 *Device;        // +0x00
    char Pad4[0xda0];
    INT Current;                        // +0xda4
};

struct UnnamedRecord_6a790;

struct UnnamedOwner_6a790
{
    char Pad0[0x40b4];
    UnnamedRecord_6a790 *Records;       // +0x40b4: list head
    char Pad40b8[0x20];
    DWORD Flag40d8;                     // +0x40d8
    char Pad40dc[0x46a4 - 0x40dc];
    UnnamedInterface_6a620 *Interface;  // +0x46a4
    char Pad46a8[0x2fb58 - 0x46a8];
    UnnamedSlot_6a620 Slot;             // +0x2fb58
};

// Retail 0x10a7bf30: releases a TArray-like member, `this` on the stack.
void __stdcall UnnamedArray_Release(void *Array);
// Retail RVA 0x6ac30: initialises the block at +4, `this` on the stack.
void __stdcall UnnamedBlock_Init(void *Block);

// Block at +4 of the record; its constructor is retail RVA 0x6ac30.
struct UnnamedBlock_6ac30
{
    char Data[0x444];
    UnnamedBlock_6ac30() { UnnamedBlock_Init(this); }
};

struct UnnamedArray_6a790
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    UnnamedArray_6a790() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~UnnamedArray_6a790() { UnnamedArray_Release(this); }
};

struct UnnamedRecord_6a790
{
    UnnamedRecord_6a790(UnnamedOwner_6a790 *InOwner, INT InHandle);
    UnnamedRecord_6a790(UnnamedOwner_6a790 *InOwner, const UnnamedBlock_6ac30 &Src);  // RVA 0x6a2f0
    ~UnnamedRecord_6a790();

    DWORD Active;                       // +0x000
    UnnamedBlock_6ac30 Block;           // +0x004
    UnnamedArray_6a790 Buffer;          // +0x448
    INT Handle;                         // +0x454
    UnnamedOwner_6a790 *Owner;          // +0x458
    UnnamedRecord_6a790 *Next;          // +0x45c
};

// Retail RVA 0x6a790.
UnnamedRecord_6a790::UnnamedRecord_6a790(UnnamedOwner_6a790 *InOwner, INT InHandle)
{
    Active = 1;
    Owner = InOwner;
    Handle = InHandle;
    Next = InOwner->Records;
    InOwner->Records = this;
}

// Retail RVA 0x6a620.
UnnamedRecord_6a790::~UnnamedRecord_6a790()
{
    UnnamedRecord_6a790 *R = Owner->Records;
    if (R != this)
    {
        while (R)
        {
            if (R->Next == this)
            {
                R->Next = Next;
                break;
            }
            R = R->Next;
        }
    }
    else
    {
        Owner->Records = Next;
    }
    UnnamedSlot_6a620 *S = &Owner->Slot;
    INT H = Handle;
    Next = 0;
    if (S->Current == H)
    {
        S->Current = 2;
        S->Device->Interface->SetMode(2);
    }
    S->Device->Interface->Release(H);
}

// A record created from a copy of an existing block, registered with the
// owner's interface.
struct UnnamedRecordCopy_6a700 : UnnamedRecord_6a790
{
    UnnamedRecordCopy_6a700(UnnamedOwner_6a790 *InOwner, const UnnamedBlock_6ac30 &Src);
};

// Retail RVA 0x6a700.
UnnamedRecordCopy_6a700::UnnamedRecordCopy_6a700(UnnamedOwner_6a790 *InOwner, const UnnamedBlock_6ac30 &Src)
    : UnnamedRecord_6a790(InOwner, Src)
{
    Active = 0;
    Owner->Interface->Create(Buffer.Data, 0, &Handle, InOwner->Flag40d8 ? 0 : 0x10);
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
UnnamedRecord_6a790 *Driver_6a790(void *Mem, UnnamedOwner_6a790 *O, INT H)
{
    return new(Mem) UnnamedRecord_6a790(O, H);
}
// Stand-in for retail RVA 0x6a2f0 (published elsewhere), defined here only so
// the linker gives it the same this-on-the-stack convention as retail.
void __stdcall UnnamedRecord_FillBuffer(UnnamedRecord_6a790 *R);
__declspec(noinline) UnnamedRecord_6a790::UnnamedRecord_6a790(UnnamedOwner_6a790 *InOwner, const UnnamedBlock_6ac30 &Src)
{
    Owner = InOwner;
    Block = Src;
    UnnamedRecord_FillBuffer(this);
}
UnnamedRecordCopy_6a700 *Driver_6a700(void *Mem, UnnamedOwner_6a790 *O, const UnnamedBlock_6ac30 *Src)
{
    return new(Mem) UnnamedRecordCopy_6a700(O, *Src);
}
void Driver_6a620(UnnamedRecord_6a790 *R)
{
    R->~UnnamedRecord_6a790();
}
