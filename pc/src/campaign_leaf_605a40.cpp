// campaign_leaf_605a40.cpp -- thiscall method at VA 0x10f05a40: returns false when the pointer at
// 0x10 is null; otherwise calls the method at VA 0x10f1f950 on it and returns true. The class and
// method names are invented.

class UnkType_10f1f950
{
public:
    void Unk_10f1f950();
};

class UnkType_10f05a40
{
public:
    bool Unk_10f05a40();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10f1f950* unk_10;
};

// UnkType_10f05a40::Unk_10f05a40
bool UnkType_10f05a40::Unk_10f05a40()
{
    if ( !unk_10 )
    {
        return false;
    }
    unk_10->Unk_10f1f950();
    return true;
}
