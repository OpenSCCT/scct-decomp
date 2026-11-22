// campaign_leaf_32a6f0.cpp -- a member function at VA 0x10c2a6f0: when the int at 0x04 of its
// member at 0xd4 is not zero it calls that member's method at VA 0x10c29e50 with 0 and 1. guess:
// removes the first element of an array. The class, method and member names are invented; the
// offsets and addresses are the binary's.

class UnkType_10c29e50
{
public:
    void Unk_10c29e50(int Index, int Count);

    int unk_00;
    int unk_04;
};

class UnkType_10c2a6f0
{
public:
    void Unk_10c2a6f0();

private:
    unsigned char unk_00[0xd4];
    UnkType_10c29e50 unk_d4;
};

// UnkType_10c2a6f0::Unk_10c2a6f0
void UnkType_10c2a6f0::Unk_10c2a6f0()
{
    if ( unk_d4.unk_04 )
    {
        unk_d4.Unk_10c29e50(0, 1);
    }
}
