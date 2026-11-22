// campaign_leaf_26aa00.cpp -- a member function at VA 0x10b6aa00: when the pointer at 0x18 and the
// pointer at 0x08 of its object are both non-null it passes its argument and 1 to the member at VA
// 0x10d307f0 of the inner object. The class, method and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10d307f0
{
public:
    void Unk_10d307f0(int Value, int Flag);
};

class UnkType_10b6aa00_Item
{
public:
    int unk_00;
    int unk_04;
    UnkType_10d307f0* unk_08;
};

class UnkType_10b6aa00
{
public:
    void Unk_10b6aa00(int Value);

private:
    unsigned char unk_00[0x18];
    UnkType_10b6aa00_Item* unk_18;
};

// UnkType_10b6aa00::Unk_10b6aa00
void UnkType_10b6aa00::Unk_10b6aa00(int Value)
{
    if ( unk_18 && unk_18->unk_08 )
    {
        unk_18->unk_08->Unk_10d307f0(Value, 1);
    }
}
