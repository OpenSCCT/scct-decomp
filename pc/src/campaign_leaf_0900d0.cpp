// campaign_leaf_0900d0.cpp -- one function at file offset 0x900d0, preferred VA 0x109900d0. It
// returns the first available of: the pointer at offset 0x184; the pointer at offset 0x188 when bit
// 0x4000000 of the flags at offset 0x30 is clear or its argument is zero; the pointer at offset
// 0x1c8; the pointer at offset 0x40 of the object reached through offsets 0x7c and 0x38; else null.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkItem;

class UnkInner
{
public:
    unsigned char unk_0[0x40];
    UnkItem* unk_40;
};

class UnkOuter
{
public:
    unsigned char unk_0[0x38];
    UnkInner* unk_38;
};

class UnkType_109900d0
{
public:
    unsigned char unk_0[0x30];
    int unk_30;
    unsigned char unk_34[0x7c - 0x34];
    UnkOuter* unk_7c;
    unsigned char unk_80[0x184 - 0x80];
    UnkItem* unk_184;
    UnkItem* unk_188;
    unsigned char unk_18c[0x1c8 - 0x18c];
    UnkItem* unk_1c8;

    UnkItem* Unk_109900d0(int Flag);
};

// UnkType_109900d0::Unk_109900d0
UnkItem* UnkType_109900d0::Unk_109900d0(int Flag)
{
    if ( unk_184 )
    {
        return unk_184;
    }
    if ( unk_188 && ( !( unk_30 & 0x4000000 ) || !Flag ) )
    {
        return unk_188;
    }
    if ( unk_1c8 )
    {
        return unk_1c8;
    }
    if ( unk_7c->unk_38 )
    {
        return unk_7c->unk_38->unk_40;
    }
    return 0;
}
