// campaign_leaf_4dc3f0.cpp -- one function at file offset 0x4dc3f0, preferred VA 0x10ddc3f0. It
// does nothing when the byte at 0x2c is set and Source is null; otherwise it clears the byte,
// stores Source at 0x28 and copies the words at 0x18 and 0x14 of Source to 0x30 and 0x34, or
// zeroes them for a null Source. The class, method, structure and member names are invented; the
// offsets and the bytes are the binary's.

struct UnkSource
{
    unsigned char unk_0[0x14];
    int unk_14;
    int unk_18;
};

class UnkType_10ddc3f0
{
public:
    void Unk_10ddc3f0(UnkSource* Source);

    unsigned char unk_0[0x28];
    UnkSource* unk_28;
    unsigned char unk_2c;
    int unk_30;
    int unk_34;
};

// UnkType_10ddc3f0::Unk_10ddc3f0
void UnkType_10ddc3f0::Unk_10ddc3f0(UnkSource* Source)
{
    if ( unk_2c != 0 && Source == 0 )
    {
        return;
    }
    unk_2c = 0;
    unk_28 = Source;
    if ( Source == 0 )
    {
        unk_30 = 0;
        unk_34 = 0;
    }
    else
    {
        unk_30 = Source->unk_18;
        unk_34 = Source->unk_14;
    }
}
