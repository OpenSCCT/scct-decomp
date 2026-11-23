// campaign_leaf_57ade0.cpp -- constructor at VA 0x10e7ade0: runs the base class constructor at VA
// 0x11018d20 with the record it is given, installs this class's two vtables (VA 0x1114ebbc and, for
// the base part at 0x08, VA 0x1114ebac), and copies the record's words at
// 0x10-0x37 to 0x20-0x47. The class names are invented; the addresses are the
// binary's.

struct UnkType_10e7ade0_Record
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
    int unk_34;
};

class UnkType_10e7ade0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e7ade0_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e7ade0_11018d20 : public UnkType_10e7ade0_Base0, public UnkType_10e7ade0_Base8
{
public:
    UnkType_10e7ade0_11018d20(const UnkType_10e7ade0_Record& Record);
};

class UnkType_10e7ade0 : public UnkType_10e7ade0_11018d20
{
public:
    UnkType_10e7ade0(const UnkType_10e7ade0_Record& Record);

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
};

// UnkType_10e7ade0::UnkType_10e7ade0
UnkType_10e7ade0::UnkType_10e7ade0(const UnkType_10e7ade0_Record& Record)
    : UnkType_10e7ade0_11018d20(Record)
{
    unk_20 = Record.unk_10;
    unk_24 = Record.unk_14;
    unk_28 = Record.unk_18;
    unk_2c = Record.unk_1c;
    unk_30 = Record.unk_20;
    unk_34 = Record.unk_24;
    unk_38 = Record.unk_28;
    unk_3c = Record.unk_2c;
    unk_40 = Record.unk_30;
    unk_44 = Record.unk_34;
}
