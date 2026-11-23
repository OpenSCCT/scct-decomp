// campaign_leaf_55df10.cpp -- constructor at VA 0x10e5df10: runs the base class constructor at VA
// 0x10e6d1a0 with the record it is given, installs this class's two vtables (VA 0x1114d0ac and, for
// the base part at 0x08, VA 0x1114d09c), clears the members at 0x44 and 0x48, and copies the
// record's words at 0x10-0x33 to 0x20-0x43. The class names are invented; the addresses are the
// binary's.

struct UnkType_10e5df10_Record
{
    int unk_00[4];
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
};

class UnkType_10e5df10_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e5df10_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e5df10_10e6d1a0 : public UnkType_10e5df10_Base0, public UnkType_10e5df10_Base8
{
public:
    UnkType_10e5df10_10e6d1a0(const UnkType_10e5df10_Record& Record);
};

class UnkType_10e5df10 : public UnkType_10e5df10_10e6d1a0
{
public:
    UnkType_10e5df10(const UnkType_10e5df10_Record& Record);

private:
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
};

// UnkType_10e5df10::UnkType_10e5df10
UnkType_10e5df10::UnkType_10e5df10(const UnkType_10e5df10_Record& Record)
    : UnkType_10e5df10_10e6d1a0(Record)
{
    unk_44 = 0;
    unk_48 = 0;
    unk_20 = Record.unk_10;
    unk_24 = Record.unk_14;
    unk_28 = Record.unk_18;
    unk_2c = Record.unk_1c;
    unk_30 = Record.unk_20;
    unk_34 = Record.unk_24;
    unk_38 = Record.unk_28;
    unk_3c = Record.unk_2c;
    unk_40 = Record.unk_30;
}
