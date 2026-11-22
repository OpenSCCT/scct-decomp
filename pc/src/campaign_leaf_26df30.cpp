// campaign_leaf_26df30.cpp -- one function at file offset 0x26df30, preferred VA 0x10b6df30. For
// each of the objects at offsets 0x2c, 0x30 and 0x34 that exists and has a non-null object at its
// offset 0x8, it clears that object's word at offset 0x2c and bit 0x1 of its own byte at offset
// 0x18. The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10b6df30_Target
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
};

class UnkType_10b6df30_Item
{
public:
    unsigned char unk_0[0x8];
    UnkType_10b6df30_Target* unk_8;
    unsigned char unk_c[0x18 - 0xc];
    unsigned char unk_18;
};

class UnkType_10b6df30
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10b6df30_Item* unk_2c;
    UnkType_10b6df30_Item* unk_30;
    UnkType_10b6df30_Item* unk_34;

    void Unk_10b6df30();
};

// UnkType_10b6df30::Unk_10b6df30
void UnkType_10b6df30::Unk_10b6df30()
{
    if ( unk_2c )
    {
        UnkType_10b6df30_Target* Target = unk_2c->unk_8;
        if ( Target )
        {
            Target->unk_2c = 0;
            unk_2c->unk_18 &= ~1;
        }
    }
    if ( unk_30 )
    {
        UnkType_10b6df30_Target* Target = unk_30->unk_8;
        if ( Target )
        {
            Target->unk_2c = 0;
            unk_30->unk_18 &= ~1;
        }
    }
    if ( unk_34 )
    {
        UnkType_10b6df30_Target* Target = unk_34->unk_8;
        if ( Target )
        {
            Target->unk_2c = 0;
            unk_34->unk_18 &= ~1;
        }
    }
}
