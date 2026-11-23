// campaign_leaf_0bfef0.cpp -- method at VA 0x109bfef0: if the value at 0x08 is negative, calls the
// method at VA 0x109bff10 of the member at 0x0c with 0 and negates the value. The class, member and
// method names are invented; the offsets and the address are the binary's.

class UnkType_109bfef0_0c
{
public:
    void Unk_109bff10(int Value);
};

class UnkType_109bfef0
{
public:
    void Unk_109bfef0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_109bfef0_0c unk_0c;
};

// UnkType_109bfef0::Unk_109bfef0
void UnkType_109bfef0::Unk_109bfef0()
{
    if ( unk_08 < 0 )
    {
        unk_0c.Unk_109bff10(0);
        unk_08 = -unk_08;
    }
}
