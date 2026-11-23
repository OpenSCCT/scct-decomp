// campaign_leaf_2316c0.cpp -- a member function at VA 0x10b316c0 that clears the int at 0x80 and
// passes its argument to the free function at VA 0x10b2ccb0; when that returns an object it passes
// to the object's virtual slot 25 the object found through the pointer at 0x18 (the member at VA
// 0x10a0e220 of its pointer at 0x04 with its byte at 0x0c, then the member at VA 0x10a45b50 of the
// result's pointer at 0x64), and when the slot returns non-null it calls the member at VA
// 0x10b30640 with the argument. It returns the slot's result, or null. The class, function, method
// and member names are invented; the offsets, addresses and slot are the binary's.

class UnkType_10b316c0_Owner;

class UnkType_10b316c0_Result;

class UnkType_10b316c0_Handler
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual UnkType_10b316c0_Result* VirtualSlot25(UnkType_10b316c0_Owner* Owner);
};

UnkType_10b316c0_Handler* Unk_10b2ccb0(int Value);

class UnkType_10b316c0_Lookup
{
public:
    UnkType_10b316c0_Owner* Unk_10a45b50();
};

class UnkType_10b316c0_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b316c0_Lookup* unk_64;
};

class UnkType_10b316c0_Table
{
public:
    UnkType_10b316c0_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b316c0_Item
{
public:
    int unk_00;
    UnkType_10b316c0_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b316c0
{
public:
    void Unk_10b30640(int Value);
    UnkType_10b316c0_Result* Unk_10b316c0(int Value);

private:
    unsigned char unk_00[0x18];
    UnkType_10b316c0_Item* unk_18;
    unsigned char unk_1c[0x80 - 0x1c];
    int unk_80;
};

// UnkType_10b316c0::Unk_10b316c0
UnkType_10b316c0_Result* UnkType_10b316c0::Unk_10b316c0(int Value)
{
    UnkType_10b316c0_Result* Result = 0;
    unk_80 = 0;
    UnkType_10b316c0_Handler* Handler = Unk_10b2ccb0(Value);
    if ( Handler )
    {
        Result = Handler->VirtualSlot25(
            unk_18->unk_04->Unk_10a0e220(unk_18->unk_0c)->unk_64->Unk_10a45b50());
        if ( Result )
        {
            Unk_10b30640(Value);
        }
    }
    return Result;
}
