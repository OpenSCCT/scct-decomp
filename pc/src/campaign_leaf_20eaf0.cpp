// campaign_leaf_20eaf0.cpp -- constructor at VA 0x10b0eaf0. It installs the class's vtable (VA
// 0x110ddec0), assigns L"None" and L"NONE" to the empty strings at 0x04 and 0x10 through the
// method at VA 0x10907a00, and sets its words: -1 at 0x1c, 1 at 0x20, 0x24, 0x2c, 0x30 and 0x38, 0
// at 0x28 and 0x34, 0x100 at 0x54, 0x400 at 0x58, 100 at 0x5c and 0x20 at 0x60. The class, method
// and member names are invented.

class UnkType_10b0eaf0_String
{
public:
    // UnkType_10b0eaf0_String::UnkType_10b0eaf0_String
    UnkType_10b0eaf0_String()
        : unk_0(0), unk_4(0), unk_8(0)
    {
    }

    UnkType_10b0eaf0_String& Unk_10907a00(const unsigned short* Other);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b0eaf0
{
public:
    UnkType_10b0eaf0();

    virtual void VirtualSlot0();

private:
    UnkType_10b0eaf0_String unk_04;
    UnkType_10b0eaf0_String unk_10;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    char unk_3c[0x54 - 0x3c];
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
};

// UnkType_10b0eaf0::UnkType_10b0eaf0
UnkType_10b0eaf0::UnkType_10b0eaf0()
{
    unk_04.Unk_10907a00(L"None");
    unk_10.Unk_10907a00(L"NONE");
    unk_1c = -1;
    unk_20 = 1;
    unk_24 = 1;
    unk_28 = 0;
    unk_2c = 1;
    unk_30 = 1;
    unk_34 = 0;
    unk_38 = 1;
    unk_54 = 0x100;
    unk_58 = 0x400;
    unk_5c = 100;
    unk_60 = 0x20;
}
