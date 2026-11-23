// campaign_leaf_0c4280.cpp -- constructor at VA 0x109c4280 (vtable at VA 0x110ce8d8): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8. The class
// and member names are invented; the offsets, the values and the addresses are the binary's.

struct UnkType_109c4280_Sub
{
    UnkType_109c4280_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109c4280_Base
{
public:
    UnkType_109c4280_Base();
    virtual ~UnkType_109c4280_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109c4280_Middle : public UnkType_109c4280_Base
{
public:
    virtual ~UnkType_109c4280_Middle();

private:
    UnkType_109c4280_Sub unk_1cc;
};

class UnkType_109c4280 : public UnkType_109c4280_Middle
{
public:
    UnkType_109c4280();
    virtual ~UnkType_109c4280();

private:
};

// UnkType_109c4280::UnkType_109c4280
UnkType_109c4280::UnkType_109c4280()
{
}
