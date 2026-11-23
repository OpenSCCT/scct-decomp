// campaign_leaf_56d2f0.cpp -- constructor at VA 0x10e6d2f0: constructs the 4-byte member at 0x00
// with the constructor at VA 0x10e681e0, then clears the member at 0x04. The class names are
// invented; the offsets and addresses are the binary's.

class UnkType_10e681e0
{
public:
    UnkType_10e681e0();

private:
    int unk_00;
};

class UnkType_10e6d2f0
{
public:
    UnkType_10e6d2f0();

private:
    UnkType_10e681e0 unk_00;
    int unk_04;
};

// UnkType_10e6d2f0::UnkType_10e6d2f0
UnkType_10e6d2f0::UnkType_10e6d2f0()
{
    unk_04 = 0;
}
