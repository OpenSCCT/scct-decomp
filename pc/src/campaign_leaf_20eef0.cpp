// campaign_leaf_20eef0.cpp -- constructor at VA 0x10b0eef0. It runs the base class constructor at
// VA 0x10b0eaf0, installs the class's vtable (VA 0x110de0f4), assigns L"Select" and L"SELECT" to
// the base's strings at 0x04 and 0x10 through the method at VA 0x10907a00, sets the words at 0x1c
// to 8, 0x20 to 0x30 to 0 and 0x34 to 1, and copies the three floats at VA 0x113169f8 to the base's
// 0x48 and from there to 0x3c. The class, method and member names are invented.

#include "campaign_global_113169f8.h"

class UnkType_10b0eef0_String
{
public:
    UnkType_10b0eef0_String& Unk_10907a00(const unsigned short* Other);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b0eef0_Base
{
public:
    UnkType_10b0eef0_Base();

    virtual void VirtualSlot0();

protected:
    UnkType_10b0eef0_String unk_04;
    UnkType_10b0eef0_String unk_10;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    UnkType_113169f8 unk_3c;
    UnkType_113169f8 unk_48;
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
};

class UnkType_10b0eef0 : public UnkType_10b0eef0_Base
{
public:
    UnkType_10b0eef0();

    virtual void VirtualSlot0();
};

// UnkType_10b0eef0::UnkType_10b0eef0
UnkType_10b0eef0::UnkType_10b0eef0()
{
    unk_04.Unk_10907a00(L"Select");
    unk_10.Unk_10907a00(L"SELECT");
    unk_2c = 0;
    unk_30 = 0;
    unk_28 = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_1c = 8;
    unk_34 = 1;
    unk_3c = unk_48 = GUnk_113169f8;
}
