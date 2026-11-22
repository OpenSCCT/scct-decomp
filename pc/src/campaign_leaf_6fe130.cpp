// campaign_leaf_6fe130.cpp -- constructor at VA 0x10ffe130: constructs the 4-byte member at 0x00 with the
// constructor at VA 0x10e10d90, then clears the members at 0x04 and 0x08. The class names are invented; the offsets
// and addresses are the binary's.

class UnkType_10e10d90
{
public:
    UnkType_10e10d90();

private:
    int unk_00;
};

class UnkType_10ffe130
{
public:
    UnkType_10ffe130();

private:
    UnkType_10e10d90 unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10ffe130::UnkType_10ffe130
UnkType_10ffe130::UnkType_10ffe130()
{
    unk_04 = 0;
    unk_08 = 0;
}
