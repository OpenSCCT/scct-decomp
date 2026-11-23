// campaign_leaf_6fdfc0.cpp -- constructor at VA 0x10ffdfc0: constructs the 4-byte member at 0x00
// with the constructor at VA 0x10e10d90, then clears the member at 0x04. The class names are
// invented; the offsets and addresses are the binary's.

class UnkType_10e10d90
{
public:
    UnkType_10e10d90();

private:
    int unk_00;
};

class UnkType_10ffdfc0
{
public:
    UnkType_10ffdfc0();

private:
    UnkType_10e10d90 unk_00;
    int unk_04;
};

// UnkType_10ffdfc0::UnkType_10ffdfc0
UnkType_10ffdfc0::UnkType_10ffdfc0()
{
    unk_04 = 0;
}
