// campaign_leaf_50f700.cpp -- constructor at VA 0x10e0f700: runs the base constructor at
// VA 0x10e10d90 and clears the dword at offset 4. All names are invented.

class UnkType_10e10d90
{
public:
    UnkType_10e10d90();

private:
    int unk_00;
};

class UnkType_10e0f700 : public UnkType_10e10d90
{
public:
    UnkType_10e0f700();

private:
    int unk_04;
};

// UnkType_10e0f700::UnkType_10e0f700
UnkType_10e0f700::UnkType_10e0f700()
{
    unk_04 = 0;
}
