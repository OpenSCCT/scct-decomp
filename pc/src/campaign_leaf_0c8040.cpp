// campaign_leaf_0c8040.cpp -- constructor at VA 0x109c8040 (vtable at VA 0x110cf0b8): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// sets up the 16-byte records at 0x1cc, 0x2d4 and 0x2e8: each zeroed except its float at 0x08, set
// to 1e-8. The class and member names are invented; the offsets, the values and the addresses are
// the binary's.

struct UnkType_109c8040_Sub
{
    UnkType_109c8040_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109c8040_Base
{
public:
    UnkType_109c8040_Base();
    virtual ~UnkType_109c8040_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109c8040_Middle : public UnkType_109c8040_Base
{
public:
    virtual ~UnkType_109c8040_Middle();

private:
    UnkType_109c8040_Sub unk_1cc;
};

class UnkType_109c8040 : public UnkType_109c8040_Middle
{
public:
    UnkType_109c8040();
    virtual ~UnkType_109c8040();

private:
    unsigned char unk_1dc[0x2d4 - 0x1dc];
    UnkType_109c8040_Sub unk_2d4;
    unsigned char unk_2e4[0x2e8 - 0x2e4];
    UnkType_109c8040_Sub unk_2e8;
};

// UnkType_109c8040::UnkType_109c8040
UnkType_109c8040::UnkType_109c8040()
{
}
