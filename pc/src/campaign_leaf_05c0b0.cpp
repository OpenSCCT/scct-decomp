// campaign_leaf_05c0b0.cpp -- constructor at VA 0x1095c0b0 taking three values: stores the first at
// 0x00 and the second at 0x04, and constructs the member at 0x08 from the third with the
// constructor at VA 0x10d7cf20. The class and member names are invented; the offsets and the
// address are the binary's.

class UnkType_10d7cf20_05c0b0
{
public:
    UnkType_10d7cf20_05c0b0(int Value);
};

class UnkType_1095c0b0
{
public:
    UnkType_1095c0b0(int Arg0, int Arg1, int Arg2);

private:
    int unk_00;
    int unk_04;
    UnkType_10d7cf20_05c0b0 unk_08;
};

// UnkType_1095c0b0::UnkType_1095c0b0
UnkType_1095c0b0::UnkType_1095c0b0(int Arg0, int Arg1, int Arg2)
: unk_00(Arg0)
, unk_04(Arg1)
, unk_08(Arg2)
{
}
