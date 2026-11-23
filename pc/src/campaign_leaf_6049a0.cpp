// campaign_leaf_6049a0.cpp -- thiscall method at VA 0x10f049a0: returns false when the pointer at
// 0x10 is null, otherwise whether the method at VA 0x10f1e960 on it returns true. The class and
// method names are invented.

class UnkType_10f1e960
{
public:
    unsigned char Unk_10f1e960();
};

class UnkType_10f049a0
{
public:
    bool Unk_10f049a0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10f1e960* unk_10;
};

// UnkType_10f049a0::Unk_10f049a0
bool UnkType_10f049a0::Unk_10f049a0()
{
    if ( !unk_10 )
    {
        return false;
    }
    return unk_10->Unk_10f1e960() ? true : false;
}
