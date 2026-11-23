// campaign_leaf_094f40.cpp -- constructor at VA 0x10994f40 (vtable at VA 0x110c7470): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8. The class
// and member names are invented; the offsets, the values and the addresses are the binary's.

struct UnkType_10994f40_Sub
{
    UnkType_10994f40_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_10994f40_Base
{
public:
    UnkType_10994f40_Base();
    virtual ~UnkType_10994f40_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_10994f40_Middle : public UnkType_10994f40_Base
{
public:
    virtual ~UnkType_10994f40_Middle();

private:
    UnkType_10994f40_Sub unk_1cc;
};

class UnkType_10994f40 : public UnkType_10994f40_Middle
{
public:
    UnkType_10994f40();
    virtual ~UnkType_10994f40();

private:
};

// UnkType_10994f40::UnkType_10994f40
UnkType_10994f40::UnkType_10994f40()
{
}
