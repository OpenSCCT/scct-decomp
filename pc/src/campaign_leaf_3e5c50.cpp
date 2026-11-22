// campaign_leaf_3e5c50.cpp -- constructor of the class at VA 0x10ce5c50: after the base constructor
// at VA 0x10cd7930 it clears the three ints at 0x50. The class names are invented; the offsets and
// addresses are the binary's.

class UnkType_10cd7930
{
public:
    UnkType_10cd7930();
    virtual ~UnkType_10cd7930();

private:
    unsigned char unk_04[0x50 - 4];
};

class UnkType_10ce5c50 : public UnkType_10cd7930
{
public:
    UnkType_10ce5c50();
    virtual ~UnkType_10ce5c50();

private:
    int unk_50;
    int unk_54;
    int unk_58;
};

// UnkType_10ce5c50::UnkType_10ce5c50
UnkType_10ce5c50::UnkType_10ce5c50()
{
    unk_50 = 0;
    unk_54 = 0;
    unk_58 = 0;
}
