// campaign_leaf_0d8ad0.cpp -- constructor at VA 0x109d8ad0 (vtable at VA 0x110cf500): runs the base
// class constructor at VA 0x109732b0, then zeroes the word at 0x54 and the bytes at 0x58, 0x59 and
// 0x5a. The class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_109d8ad0_Base
{
public:
    UnkType_109d8ad0_Base();
    virtual ~UnkType_109d8ad0_Base();

protected:
    unsigned char unk_04[0x54 - 0x04];
};

class UnkType_109d8ad0 : public UnkType_109d8ad0_Base
{
public:
    UnkType_109d8ad0();
    virtual ~UnkType_109d8ad0();

private:
    int unk_54;
    unsigned char unk_58;
    unsigned char unk_59;
    unsigned char unk_5a;
};

// UnkType_109d8ad0::UnkType_109d8ad0
UnkType_109d8ad0::UnkType_109d8ad0() : unk_54(0), unk_58(0), unk_59(0), unk_5a(0)
{
}
