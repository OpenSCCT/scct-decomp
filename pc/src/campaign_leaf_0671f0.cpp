// campaign_leaf_0671f0.cpp -- method at VA 0x109671f0: if the value at 0x08 is negative, calls the
// method at VA 0x10967210 of the member at 0x0c with 0 and negates the value. The class, member and
// method names are invented; the offsets and the address are the binary's.

class UnkType_109671f0_0c
{
public:
    void Unk_10967210(int Value);
};

class UnkType_109671f0
{
public:
    void Unk_109671f0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_109671f0_0c unk_0c;
};

// UnkType_109671f0::Unk_109671f0
void UnkType_109671f0::Unk_109671f0()
{
    if ( unk_08 < 0 )
    {
        unk_0c.Unk_10967210(0);
        unk_08 = -unk_08;
    }
}
