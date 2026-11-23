// campaign_leaf_26dae0.cpp -- a member function at VA 0x10b6dae0: when the member at VA 0x10ad5970
// of the object the pointer at 0x10 refers to accepts the pointer at 0x1c, it looks up an object
// through that object (the entry its member at 0x04 gives for its byte at 0x0c with the member at
// VA 0x10a0e220, then the member at VA 0x10a45b50 of that entry's object at 0x64) and, when there
// is one, passes what its member at VA 0x10cd92d0 returns for the global at VA 0x1122f608, 0, 0
// and 0 to its virtual slot 4. Otherwise, when the pointer at 0x6c is set, that member accepts it
// and the int at 0x54 is at most 1, it calls its own member at VA 0x10b6d430 with 0. The class,
// method, member and global names are invented; the offsets, addresses and slot are the binary's.

#include "campaign_global_1122f608.h"

class UnkType_10b6dae0_Page;

class UnkType_10b6dae0_Result;

class UnkType_10b6dae0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10b6dae0_Result* Result);

    UnkType_10b6dae0_Result* Unk_10cd92d0(int Name, int First, int Second, int Third);
};

class UnkType_10b6dae0_Lookup
{
public:
    UnkType_10b6dae0_Target* Unk_10a45b50();
};

class UnkType_10b6dae0_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b6dae0_Lookup* unk_64;
};

class UnkType_10b6dae0_Table
{
public:
    UnkType_10b6dae0_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b6dae0_Menu
{
public:
    bool Unk_10ad5970(UnkType_10b6dae0_Page* Page);

    int unk_00;
    UnkType_10b6dae0_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b6dae0
{
public:
    void Unk_10b6d430(int Value);
    void Unk_10b6dae0();

private:
    unsigned char unk_00[0x10];
    UnkType_10b6dae0_Menu* unk_10;
    unsigned char unk_14[0x1c - 0x14];
    UnkType_10b6dae0_Page* unk_1c;
    unsigned char unk_20[0x54 - 0x20];
    int unk_54;
    unsigned char unk_58[0x6c - 0x58];
    UnkType_10b6dae0_Page* unk_6c;
};

// UnkType_10b6dae0::Unk_10b6dae0
void UnkType_10b6dae0::Unk_10b6dae0()
{
    if ( unk_10->Unk_10ad5970(unk_1c) )
    {
        UnkType_10b6dae0_Target* Target =
            unk_10->unk_04->Unk_10a0e220(unk_10->unk_0c)->unk_64->Unk_10a45b50();
        if ( Target )
        {
            Target->VirtualSlot4(Target->Unk_10cd92d0(GUnk_1122f608, 0, 0, 0));
        }
    }
    else if ( unk_6c && unk_10->Unk_10ad5970(unk_6c) && unk_54 <= 1 )
    {
        Unk_10b6d430(0);
    }
}
