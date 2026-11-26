// campaign_leaf_4e5500.cpp -- destructor at VA 0x10de5500: calls the method at VA 0x10de6310, then
// for each of the pointers at 0x98 and 0x94 that is set, deletes the object at its 0x1c and hands
// it to the method at VA 0x10de6170 of the object at 0x9c; then destroys the member at 0xa4 (VA
// 0x10dacf90) and the base (VA 0x10de6450). The class and member names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_leaf_4e5500_member.h"

class UnkType_10de5500_Owned
{
public:
    virtual ~UnkType_10de5500_Owned();
};

class UnkType_10de5500_Item
{
public:
    unsigned char unk_00[0x1c];
    UnkType_10de5500_Owned* unk_1c;
};

class UnkType_10de5500_Pool
{
public:
    void Unk_10de6170(UnkType_10de5500_Item* Item);
};

class UnkType_10de5500_Base
{
public:
    ~UnkType_10de5500_Base();

    int unk_00[0x25];
};

class UnkType_10de5500 : public UnkType_10de5500_Base
{
public:
    ~UnkType_10de5500();
    void Unk_10de6310();

    UnkType_10de5500_Item* unk_94;
    UnkType_10de5500_Item* unk_98;
    UnkType_10de5500_Pool* unk_9c;
    bool unk_a0;
    bool unk_a1;
    UnkType_10de5500_Member unk_a4;
    int unk_124;
};

// UnkType_10de5500::~UnkType_10de5500
UnkType_10de5500::~UnkType_10de5500()
{
    Unk_10de6310();
    UnkType_10de5500_Item* Second = unk_98;
    if ( Second )
    {
        delete Second->unk_1c;
        unk_9c->Unk_10de6170(Second);
    }
    UnkType_10de5500_Item* First = unk_94;
    if ( First )
    {
        delete First->unk_1c;
        unk_9c->Unk_10de6170(First);
    }
}
