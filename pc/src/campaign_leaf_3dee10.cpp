// campaign_leaf_3dee10.cpp -- one function at file offset 0x3dee10, preferred VA 0x10cdee10. A
// constructor: it installs the vtable at 0x11132c88, constructs the member at 0x2c (constructor
// at 0x10d04700) and clears the words at 0x70 to 0x90 and 0x98 to 0xa0. The class, member and
// slot names are invented; the offsets and the bytes are the binary's.

class UnkType_10cdee10_Member
{
public:
    UnkType_10cdee10_Member();

    unsigned char unk_0[0x44];
};

class UnkType_10cdee10
{
public:
    UnkType_10cdee10();
    virtual void VirtualSlot0();

    unsigned char unk_4[0x28];
    UnkType_10cdee10_Member unk_2c;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7c;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8c;
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9c;
    int unk_a0;
};

// UnkType_10cdee10::UnkType_10cdee10
UnkType_10cdee10::UnkType_10cdee10()
{
    unk_70 = 0;
    unk_74 = 0;
    unk_78 = 0;
    unk_7c = 0;
    unk_80 = 0;
    unk_84 = 0;
    unk_88 = 0;
    unk_8c = 0;
    unk_90 = 0;
    unk_98 = 0;
    unk_9c = 0;
    unk_a0 = 0;
}
