// campaign_leaf_0a28a0.cpp -- constructor at VA 0x109a28a0 (vtable at VA 0x110ca820): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8, and zeroes
// the word at 0x2b4. The class and member names are invented; the offsets, the values and the
// addresses are the binary's.

struct UnkType_109a28a0_Sub
{
    UnkType_109a28a0_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109a28a0_Base
{
public:
    UnkType_109a28a0_Base();
    virtual ~UnkType_109a28a0_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109a28a0_Middle : public UnkType_109a28a0_Base
{
public:
    virtual ~UnkType_109a28a0_Middle();

private:
    UnkType_109a28a0_Sub unk_1cc;
};

class UnkType_109a28a0 : public UnkType_109a28a0_Middle
{
public:
    UnkType_109a28a0();
    virtual ~UnkType_109a28a0();

private:
    unsigned char unk_1dc[0x2b4 - 0x1dc];
    int unk_2b4;
};

// UnkType_109a28a0::UnkType_109a28a0
UnkType_109a28a0::UnkType_109a28a0() : unk_2b4(0)
{
}
