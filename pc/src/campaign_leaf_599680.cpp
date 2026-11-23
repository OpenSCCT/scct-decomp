// campaign_leaf_599680.cpp -- constructor at VA 0x10e99680: runs the constructor of the empty base
// class at VA 0x10e9bda0, then clears the members at 0x00-0x08 and the byte at 0x0c. The class
// names are invented; the offsets and addresses are the binary's.

class UnkType_10e9bda0
{
public:
    UnkType_10e9bda0();
};

class UnkType_10e99680 : public UnkType_10e9bda0
{
public:
    UnkType_10e99680();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c;
};

// UnkType_10e99680::UnkType_10e99680
UnkType_10e99680::UnkType_10e99680()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
}
