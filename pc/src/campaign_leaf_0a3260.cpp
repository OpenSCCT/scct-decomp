// campaign_leaf_0a3260.cpp -- constructor at VA 0x109a3260 (vtable at VA 0x110cab08): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8, and zeroes
// the word at 0x2b4. The class and member names are invented; the offsets, the values and the
// addresses are the binary's.

struct UnkType_109a3260_Sub
{
    UnkType_109a3260_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109a3260_Base
{
public:
    UnkType_109a3260_Base();
    virtual ~UnkType_109a3260_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109a3260_Middle : public UnkType_109a3260_Base
{
public:
    virtual ~UnkType_109a3260_Middle();

private:
    UnkType_109a3260_Sub unk_1cc;
};

class UnkType_109a3260 : public UnkType_109a3260_Middle
{
public:
    UnkType_109a3260();
    virtual ~UnkType_109a3260();

private:
    unsigned char unk_1dc[0x2b4 - 0x1dc];
    int unk_2b4;
};

// UnkType_109a3260::UnkType_109a3260
UnkType_109a3260::UnkType_109a3260() : unk_2b4(0)
{
}
