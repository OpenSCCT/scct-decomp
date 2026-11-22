// campaign_leaf_5ffce0.cpp -- thiscall method at VA 0x10effce0: returns false when the byte at
// 0x148 is clear; otherwise calls the method at VA 0x10f14750 on the object at 0x150 and returns
// true. The class and method names are invented.

class UnkType_10f14750
{
public:
    bool Unk_10f14750();
};

class UnkType_10effce0
{
public:
    bool Unk_10effce0();

private:
    int unk_00[82];
    unsigned char unk_148;
    unsigned char unk_149;
    unsigned char unk_14a;
    unsigned char unk_14b;
    int unk_14c;
    UnkType_10f14750* unk_150;
};

// UnkType_10effce0::Unk_10effce0
bool UnkType_10effce0::Unk_10effce0()
{
    if ( !unk_148 )
    {
        return false;
    }
    unk_150->Unk_10f14750();
    return true;
}
