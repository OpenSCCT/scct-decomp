// campaign_leaf_1f1ce0.cpp -- function at VA 0x10af1ce0 with no this pointer. It returns true when
// the first object's slot 7 returns nonzero, the flag is set, the word at 0x428 of the object
// reached through the first object's 0x04 and 0x30 members is not 9, the second object's word at
// 0x54 is zero, and the list reached through the first object's member at 0x234 (head at 0x8a4)
// holds a node whose first word equals the key; otherwise false. The class, function and member
// names are invented.

struct UnkType_10af1ce0_Node
{
    int Key;
    UnkType_10af1ce0_Node* Next;
};

struct UnkType_10af1ce0_Owner
{
    char unk_000[0x8a4];
    UnkType_10af1ce0_Node* unk_8a4;
};

struct UnkType_10af1ce0_State
{
    char unk_000[0x428];
    int unk_428;
};

struct UnkType_10af1ce0_Link
{
    char unk_00[0x30];
    UnkType_10af1ce0_State* unk_30;
};

class UnkType_10af1ce0_Subject
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual int VirtualSlot7();

    UnkType_10af1ce0_Link* unk_004;
    char unk_008[0x234 - 0x008];
    UnkType_10af1ce0_Owner* unk_234;
};

struct UnkType_10af1ce0_Other
{
    char unk_00[0x54];
    int unk_54;
};

// Unk_10af1ce0
bool Unk_10af1ce0(UnkType_10af1ce0_Subject* Subject, UnkType_10af1ce0_Other* Other, int bFlag,
                  int Key)
{
    if ( Subject->VirtualSlot7() && bFlag && Subject->unk_004->unk_30->unk_428 != 9
         && Other->unk_54 == 0 )
    {
        UnkType_10af1ce0_Node* Node;
        for ( Node = Subject->unk_234->unk_8a4; Node != 0; Node = Node->Next )
        {
            if ( Node->Key == Key )
            {
                return true;
            }
        }
    }
    return false;
}
