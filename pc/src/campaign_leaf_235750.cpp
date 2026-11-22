// campaign_leaf_235750.cpp -- one function at file offset 0x235750, preferred VA 0x10b35750. It
// clears bit 0x1 of the byte at offset 0x18 of every entry of the pointer arrays at offsets 0x40
// (count at 0x44) and 0x4c (count at 0x50), and of the object at offset 0x3c. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x18];
    unsigned char unk_18;
};

class UnkType_10b35750
{
public:
    unsigned char unk_0[0x3c];
    UnkItem* unk_3c;
    UnkItem** unk_40;
    int unk_44;
    unsigned char unk_48[0x4c - 0x48];
    UnkItem** unk_4c;
    int unk_50;

    void Unk_10b35750();
};

// UnkType_10b35750::Unk_10b35750
void UnkType_10b35750::Unk_10b35750()
{
    int i;
    for ( i = 0; i < unk_44; i++ )
    {
        unk_40[i]->unk_18 &= ~1;
    }
    for ( i = 0; i < unk_50; i++ )
    {
        unk_4c[i]->unk_18 &= ~1;
    }
    unk_3c->unk_18 &= ~1;
}
