// campaign_leaf_762f70.cpp -- one function at file offset 0x762f70, preferred VA 0x11062f70. When
// the record is set, has an object at 0x74 and its word at 0x88 is clear, it passes the address of
// the record's member at 0x5c and 0 to that object's seventeenth virtual method and sets the word
// at 0x88 to 1. The type and function names are invented; the offsets are the binary's.

class UnkType_11062f70_Object
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
    virtual void VirtualSlot16(void* Data, int Flags);
};

struct UnkType_11062f70
{
    unsigned char unk_0[0x5c];
    int unk_5c;
    unsigned char unk_60[0x74 - 0x60];
    UnkType_11062f70_Object* unk_74;
    unsigned char unk_78[0x88 - 0x78];
    int unk_88;
};

// Unk_11062f70
void __stdcall Unk_11062f70(UnkType_11062f70* Record)
{
    if ( Record != 0 && Record->unk_74 != 0 && Record->unk_88 == 0 )
    {
        Record->unk_74->VirtualSlot16(&Record->unk_5c, 0);
        Record->unk_88 = 1;
    }
}
