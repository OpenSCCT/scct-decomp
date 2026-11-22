// campaign_leaf_4b4be0.cpp -- constructor at VA 0x10db4be0: runs the empty base constructor at
// VA 0x10d9d560 and clears the dword at offset 0. All names are invented.

class UnkType_10d9d560
{
public:
    UnkType_10d9d560();
};

class UnkType_10db4be0 : public UnkType_10d9d560
{
public:
    UnkType_10db4be0();

private:
    int unk_00;
};

// UnkType_10db4be0::UnkType_10db4be0
UnkType_10db4be0::UnkType_10db4be0()
{
    unk_00 = 0;
}
