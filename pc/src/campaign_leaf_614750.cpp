// campaign_leaf_614750.cpp -- thiscall method at VA 0x10f14750: returns false when the pointer at 0x08 is
// null, otherwise whether the method at VA 0x10f10960 on it returns true. The class and method names
// are invented.

class UnkType_10f10960
{
public:
    unsigned char Unk_10f10960();
};

class UnkType_10f14750
{
public:
    bool Unk_10f14750();

private:
    int unk_00;
    int unk_04;
    UnkType_10f10960* unk_08;
};

// UnkType_10f14750::Unk_10f14750
bool UnkType_10f14750::Unk_10f14750()
{
    if ( !unk_08 )
    {
        return false;
    }
    return unk_08->Unk_10f10960() ? true : false;
}
