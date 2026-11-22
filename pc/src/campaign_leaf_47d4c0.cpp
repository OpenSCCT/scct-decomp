// campaign_leaf_47d4c0.cpp -- constructor at VA 0x10d7d4c0: constructs the member at offset 4 with
// the constructor at VA 0x10d8b2d0, then clears the dword at offset 0. All names are invented.

class UnkType_10d8b2d0
{
public:
    UnkType_10d8b2d0();

private:
    int unk_00;
};

class UnkType_10d7d4c0
{
public:
    UnkType_10d7d4c0();

private:
    int unk_00;
    UnkType_10d8b2d0 unk_04;
};

// UnkType_10d7d4c0::UnkType_10d7d4c0
UnkType_10d7d4c0::UnkType_10d7d4c0()
{
    unk_00 = 0;
}
