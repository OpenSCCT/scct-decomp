// campaign_leaf_26b950.cpp -- a member function at VA 0x10b6b950: when the count at 0x04 of the
// array at 0x54 is positive it passes the array's data pointer to the member at VA 0x10b6b730 and
// then calls the array's member at VA 0x1090d050 with 0 and 1. guess: handles and removes the first
// element. The class, method and member names are invented; the offsets and addresses are the
// binary's.

class UnkType_1090d050
{
public:
    void Unk_1090d050(int Index, int Count);

    void* unk_00;
    int unk_04;
};

class UnkType_10b6b950
{
public:
    void Unk_10b6b730(void* Data);
    void Unk_10b6b950();

private:
    unsigned char unk_00[0x54];
    UnkType_1090d050 unk_54;
};

// UnkType_10b6b950::Unk_10b6b950
void UnkType_10b6b950::Unk_10b6b950()
{
    if ( unk_54.unk_04 > 0 )
    {
        Unk_10b6b730(unk_54.unk_00);
        unk_54.Unk_1090d050(0, 1);
    }
}
