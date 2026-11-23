// campaign_leaf_0aecf0.cpp -- constructor at VA 0x109aecf0 (vtable at VA 0x110cceb8): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8, zeroes the
// words at 0x2b4, 0x2b8 and 0x2c4 and sets the floats at 0x2c8 and 0x2cc to 1000. The class and
// member names are invented; the offsets, the values and the addresses are the binary's.

struct UnkType_109aecf0_Sub
{
    UnkType_109aecf0_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109aecf0_Base
{
public:
    UnkType_109aecf0_Base();
    virtual ~UnkType_109aecf0_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109aecf0_Middle : public UnkType_109aecf0_Base
{
public:
    virtual ~UnkType_109aecf0_Middle();

private:
    UnkType_109aecf0_Sub unk_1cc;
};

class UnkType_109aecf0 : public UnkType_109aecf0_Middle
{
public:
    UnkType_109aecf0();
    virtual ~UnkType_109aecf0();

private:
    unsigned char unk_1dc[0x2b4 - 0x1dc];
    int unk_2b4;
    int unk_2b8;
    unsigned char unk_2bc[0x2c4 - 0x2bc];
    int unk_2c4;
    float unk_2c8;
    float unk_2cc;
};

// UnkType_109aecf0::UnkType_109aecf0
UnkType_109aecf0::UnkType_109aecf0()
    : unk_2b4(0), unk_2b8(0), unk_2c4(0), unk_2c8(1000.0f), unk_2cc(1000.0f)
{
}
