// campaign_leaf_094ee0.cpp -- constructor at VA 0x10994ee0 (vtable at VA 0x110c71d8): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8. The class
// and member names are invented; the offsets, the values and the addresses are the binary's.

struct UnkType_10994ee0_Sub
{
    UnkType_10994ee0_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_10994ee0_Base
{
public:
    UnkType_10994ee0_Base();
    virtual ~UnkType_10994ee0_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_10994ee0_Middle : public UnkType_10994ee0_Base
{
public:
    virtual ~UnkType_10994ee0_Middle();

private:
    UnkType_10994ee0_Sub unk_1cc;
};

class UnkType_10994ee0 : public UnkType_10994ee0_Middle
{
public:
    UnkType_10994ee0();
    virtual ~UnkType_10994ee0();

private:
};

// UnkType_10994ee0::UnkType_10994ee0
UnkType_10994ee0::UnkType_10994ee0()
{
}
