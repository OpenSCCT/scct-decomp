// campaign_leaf_1ef360.cpp -- function at VA 0x10aef360 with no this pointer, taking an owner, a
// device and two words. When the owner's node list at 0x868 is not empty it calls the device's
// virtual slot 19 with 1, then for every node sets the first word at 0x238 of the node's object,
// calls that object's virtual slot 5 with the device, 0 and the second word, clears the word
// again and calls the device's virtual slot 13 with 2 and with 1, passing the owner's object's
// members at 0x8c and 0x0c and two 1.0 factors; it finishes with slot 19 and 0. The type and
// function names are invented.

struct UnkType_10aef360_Block
{
    int unk_0;
};

struct UnkType_10aef360_Source
{
    char unk_00[0x0c];
    UnkType_10aef360_Block unk_0c;
    char unk_10[0x8c - 0x10];
    UnkType_10aef360_Block unk_8c;
};

class UnkType_10aef360_Device
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
    virtual void VirtualSlot13(int Stage, UnkType_10aef360_Block* Block, float First,
                               float Second);
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19(int Enable);
};

class UnkType_10aef360_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(UnkType_10aef360_Device* Device, int Value, int Word);

    char unk_004[0x238 - 0x004];
    int unk_238;
};

struct UnkType_10aef360_Node
{
    UnkType_10aef360_Object* unk_0;
    UnkType_10aef360_Node* unk_4;
};

struct UnkType_10aef360_Owner
{
    UnkType_10aef360_Source* unk_000;
    char unk_004[0x868 - 0x004];
    UnkType_10aef360_Node* unk_868;
};

// Unk_10aef360
void Unk_10aef360(UnkType_10aef360_Owner* Owner, UnkType_10aef360_Device* Device, int First,
                  int Second)
{
    UnkType_10aef360_Node* Node = Owner->unk_868;
    if ( Node )
    {
        Device->VirtualSlot19(1);
        for ( ; Node; Node = Node->unk_4 )
        {
            Node->unk_0->unk_238 = First;
            Node->unk_0->VirtualSlot5(Device, 0, Second);
            Node->unk_0->unk_238 = 0;
            Device->VirtualSlot13(2, &Owner->unk_000->unk_8c, 1.0f, 1.0f);
            Device->VirtualSlot13(1, &Owner->unk_000->unk_0c, 1.0f, 1.0f);
        }
        Device->VirtualSlot19(0);
    }
}
