// campaign_leaf_50f730.cpp -- constructor at VA 0x10e0f730: runs the base constructor at
// VA 0x10e0f700 and clears the dword at offset 8. All names are invented.

class UnkType_10e0f700
{
public:
    UnkType_10e0f700();

private:
    int unk_00;
    int unk_04;
};

class UnkType_10e0f730 : public UnkType_10e0f700
{
public:
    UnkType_10e0f730();

private:
    int unk_08;
};

// UnkType_10e0f730::UnkType_10e0f730
UnkType_10e0f730::UnkType_10e0f730()
{
    unk_08 = 0;
}
