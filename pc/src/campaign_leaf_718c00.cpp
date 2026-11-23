// campaign_leaf_718c00.cpp -- constructor at VA 0x11018c00: constructs the 4-byte member at 0x00
// with the constructor at VA 0x10e681e0, then clears the members at 0x04 and 0x08. The class names
// are invented; the offsets and addresses are the binary's.

class UnkType_10e681e0
{
public:
    UnkType_10e681e0();

private:
    int unk_00;
};

class UnkType_11018c00
{
public:
    UnkType_11018c00();

private:
    UnkType_10e681e0 unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_11018c00::UnkType_11018c00
UnkType_11018c00::UnkType_11018c00()
{
    unk_04 = 0;
    unk_08 = 0;
}
