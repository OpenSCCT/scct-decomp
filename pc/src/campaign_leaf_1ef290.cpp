// campaign_leaf_1ef290.cpp -- one function at file offset 0x1ef290, preferred VA 0x10aef290. It
// zeroes the eight words at offsets 0x88-0xa4 of its argument, then zeroes the argument's word at
// offset 0x7c unless the object at its offset 0 exists, has the byte 2 at offset 0x4d and nonzero
// words at offsets 0x184 and 0x64. It has no this pointer. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkOwner
{
public:
    unsigned char unk_0[0x4d];
    unsigned char unk_4d;
    unsigned char unk_4e[0x64 - 0x4e];
    int unk_64;
    unsigned char unk_68[0x184 - 0x68];
    int unk_184;
};

class UnkType_10aef290
{
public:
    UnkOwner* unk_0;
    unsigned char unk_4[0x7c - 0x4];
    int unk_7c;
    unsigned char unk_80[0x88 - 0x80];
    int unk_88;
    int unk_8c;
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9c;
    int unk_a0;
    int unk_a4;

    static void Unk_10aef290(UnkType_10aef290* Object);
};

// UnkType_10aef290::Unk_10aef290
void UnkType_10aef290::Unk_10aef290(UnkType_10aef290* Object)
{
    Object->unk_88 = 0;
    Object->unk_8c = 0;
    Object->unk_90 = 0;
    Object->unk_94 = 0;
    Object->unk_98 = 0;
    Object->unk_9c = 0;
    Object->unk_a0 = 0;
    Object->unk_a4 = 0;
    UnkOwner* Owner = Object->unk_0;
    if ( !Owner || Owner->unk_4d != 2 || !Owner->unk_184 || !Owner->unk_64 )
    {
        Object->unk_7c = 0;
    }
}
