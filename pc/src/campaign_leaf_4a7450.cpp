// campaign_leaf_4a7450.cpp -- one function at file offset 0x4a7450, preferred VA 0x10da7450.
// The constructor runs the base constructor at 0x10d9d560 and clears the ints at offsets 0 and 4.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10da7450_Base
{
public:
    UnkType_10da7450_Base();
};

class UnkType_10da7450 : public UnkType_10da7450_Base
{
public:
    int unk_0;
    int unk_4;

    UnkType_10da7450();
};

// UnkType_10da7450::UnkType_10da7450
UnkType_10da7450::UnkType_10da7450()
{
    unk_0 = 0;
    unk_4 = 0;
}
