// campaign_leaf_55bee0.cpp -- constructor at VA 0x10e5bee0: runs the constructor of the empty base class
// at VA 0x10e6d280, then clears the members at 0x00 and 0x04. The class names are invented; the offsets and addresses are the
// binary's.

class UnkType_10e6d280
{
public:
    UnkType_10e6d280();
};

class UnkType_10e5bee0 : public UnkType_10e6d280
{
public:
    UnkType_10e5bee0();

private:
    int unk_00;
    int unk_04;
};

// UnkType_10e5bee0::UnkType_10e5bee0
UnkType_10e5bee0::UnkType_10e5bee0()
{
    unk_00 = 0;
    unk_04 = 0;
}
