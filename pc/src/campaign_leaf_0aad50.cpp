// campaign_leaf_0aad50.cpp -- constructor at VA 0x109aad50 (vtable at VA 0x110ccb80): runs the base
// class constructor at VA 0x10cd7930, then zeroes the words at 0x28, 0x38, 0x3c, 0x40 and 0x44. The
// class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_109aad50_Base
{
public:
    UnkType_109aad50_Base();
    virtual ~UnkType_109aad50_Base();

protected:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_109aad50 : public UnkType_109aad50_Base
{
public:
    UnkType_109aad50();
    virtual ~UnkType_109aad50();

private:
    int unk_28;
    unsigned char unk_2c[0x38 - 0x2c];
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
};

// UnkType_109aad50::UnkType_109aad50
UnkType_109aad50::UnkType_109aad50() : unk_28(0), unk_38(0), unk_3c(0), unk_40(0), unk_44(0)
{
}
