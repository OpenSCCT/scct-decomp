// campaign_leaf_3e9f70.cpp -- constructor of the class at VA 0x10ce9f70: it passes 0 to the base
// constructor at VA 0x10ce3ad0, stores 1 in the 16-bit value at 0x34 and clears the int at 0x50.
// The class names are invented; the offsets and addresses are the binary's.

class UnkType_10ce3ad0
{
public:
    UnkType_10ce3ad0(int Value);
    virtual ~UnkType_10ce3ad0();

private:
    unsigned char unk_04[0x34 - 4];
};

class UnkType_10ce9f70 : public UnkType_10ce3ad0
{
public:
    UnkType_10ce9f70();
    virtual ~UnkType_10ce9f70();

private:
    short unk_34;
    unsigned char unk_36[0x50 - 0x36];
    int unk_50;
};

// UnkType_10ce9f70::UnkType_10ce9f70
UnkType_10ce9f70::UnkType_10ce9f70()
    : UnkType_10ce3ad0(0)
{
    unk_34 = 1;
    unk_50 = 0;
}
