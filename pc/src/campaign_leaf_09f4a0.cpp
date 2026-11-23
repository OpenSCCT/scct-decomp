// campaign_leaf_09f4a0.cpp -- constructor at VA 0x1099f4a0 (vtable at VA 0x110c9910): runs the base
// class constructor at VA 0x10cd7930, then stores -1 at 0x34 and copies the base class word at 0x18
// to 0x3c. The class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_1099f4a0_Base
{
public:
    UnkType_1099f4a0_Base();
    virtual ~UnkType_1099f4a0_Base();

protected:
    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
    unsigned char unk_1c[0x34 - 0x1c];
};

class UnkType_1099f4a0 : public UnkType_1099f4a0_Base
{
public:
    UnkType_1099f4a0();
    virtual ~UnkType_1099f4a0();

private:
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_1099f4a0::UnkType_1099f4a0
UnkType_1099f4a0::UnkType_1099f4a0() : unk_34(-1), unk_3c(unk_18)
{
}
