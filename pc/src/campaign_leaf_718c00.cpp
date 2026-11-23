// campaign_leaf_718c00.cpp -- one function at file offset 0x718c00, preferred VA 0x11018c00. A
// constructor: it runs the base constructor at VA 0x10e681e0 and zeroes the words at 0x4 and 0x8.
// The class names are invented; the offset and the addresses are the binary's.

class UnkType_10e681e0
{
public:
    UnkType_10e681e0();

    int unk_0;
};

class UnkType_11018c00 : public UnkType_10e681e0
{
public:
    UnkType_11018c00();

    int unk_4;
    int unk_8;
};

// UnkType_11018c00::UnkType_11018c00
UnkType_11018c00::UnkType_11018c00()
{
    unk_4 = 0;
    unk_8 = 0;
}
