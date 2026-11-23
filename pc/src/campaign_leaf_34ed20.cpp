// campaign_leaf_34ed20.cpp -- method at VA 0x10c4ed20: calls the method at VA 0x10be9960, then,
// when the byte at 0x426 is set, stores it divided by 128 at 0x430 and clears it. The class,
// member and method names are invented; the offsets, the constant and the address are the
// binary's.

class UnkType_10c4ed20
{
public:
    void Unk_10be9960();
    void Unk_10c4ed20();

private:
    char unk_0[0x426];
    unsigned char unk_426;
    char unk_427[0x430 - 0x427];
    float unk_430;
};

// UnkType_10c4ed20::Unk_10c4ed20
void UnkType_10c4ed20::Unk_10c4ed20()
{
    Unk_10be9960();
    if ( unk_426 )
    {
        unk_430 = unk_426 / 128.0f;
        unk_426 = 0;
    }
}
