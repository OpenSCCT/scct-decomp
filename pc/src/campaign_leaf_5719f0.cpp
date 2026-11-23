// campaign_leaf_5719f0.cpp -- constructor at VA 0x10e719f0: runs the base class constructor at VA
// 0x10e5e1a0 with the record it is given, installs this class's two vtables (VA 0x110cb0f8 and,
// for the base part at 0x08, VA 0x110cb0e8), copies the base part through the method at VA
// 0x10e6d2b0 and copies the record's members at 0x10-0x28 to 0x20-0x38. The class names are
// invented; the addresses are the binary's.

struct UnkType_10e719f0_Record
{
    int unk_00[4];
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    char unk_28;
};

class UnkType_10e719f0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e719f0_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e719f0_10e5e1a0 : public UnkType_10e719f0_Base0, public UnkType_10e719f0_Base8
{
public:
    UnkType_10e719f0_10e5e1a0(const UnkType_10e719f0_Record& Record);

    void Unk_10e6d2b0(const UnkType_10e719f0_Record& Record);
};

class UnkType_10e719f0 : public UnkType_10e719f0_10e5e1a0
{
public:
    UnkType_10e719f0(const UnkType_10e719f0_Record& Record);

private:
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    char unk_38;
};

// UnkType_10e719f0::UnkType_10e719f0
UnkType_10e719f0::UnkType_10e719f0(const UnkType_10e719f0_Record& Record)
    : UnkType_10e719f0_10e5e1a0(Record)
{
    Unk_10e6d2b0(Record);
    unk_38 = Record.unk_28;
    unk_20 = Record.unk_10;
    unk_24 = Record.unk_14;
    unk_28 = Record.unk_18;
    unk_2c = Record.unk_1c;
    unk_34 = Record.unk_24;
    unk_30 = Record.unk_20;
}
