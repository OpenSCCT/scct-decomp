// campaign_leaf_4c75f0.cpp -- constructor at VA 0x10dc75f0: runs the base constructor at
// VA 0x10d98ab0 and clears the dword at offset 0x24. All names are invented.

class UnkType_10d98ab0
{
public:
    UnkType_10d98ab0();

private:
    unsigned char unk_00[0x24];
};

class UnkType_10dc75f0 : public UnkType_10d98ab0
{
public:
    UnkType_10dc75f0();

private:
    int unk_24;
};

// UnkType_10dc75f0::UnkType_10dc75f0
UnkType_10dc75f0::UnkType_10dc75f0()
{
    unk_24 = 0;
}
