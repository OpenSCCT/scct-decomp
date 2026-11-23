// campaign_leaf_5a1810.cpp -- constructor at VA 0x10ea1810: runs the constructor of the empty base
// class at VA 0x10e9a2a0, constructs nine empty arrays (data, count, and a capacity word whose top
// bit is set) and clears the member at 0x00. The class names are invented; the offsets and
// addresses are the binary's.

class UnkType_10ea1810_Base
{
public:
    UnkType_10ea1810_Base();
};

struct UnkType_10ea1810_Array
{
    // UnkType_10ea1810_Array::UnkType_10ea1810_Array
    UnkType_10ea1810_Array()
        : unk_00(0), unk_04(0), unk_08(0x80000000)
    {
    }

    void* unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkType_10ea1810 : public UnkType_10ea1810_Base
{
public:
    UnkType_10ea1810();

private:
    int unk_00;
    UnkType_10ea1810_Array unk_04;
    UnkType_10ea1810_Array unk_10;
    UnkType_10ea1810_Array unk_1c;
    UnkType_10ea1810_Array unk_28;
    UnkType_10ea1810_Array unk_34;
    UnkType_10ea1810_Array unk_40;
    UnkType_10ea1810_Array unk_4c;
    UnkType_10ea1810_Array unk_58;
};

// UnkType_10ea1810::UnkType_10ea1810
UnkType_10ea1810::UnkType_10ea1810()
{
    unk_00 = 0;
}
