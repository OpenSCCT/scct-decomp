// campaign_leaf_29b8c0.cpp -- one function at file offset 0x29b8c0, preferred VA 0x10b9b8c0. It
// takes the object at offset 0x9c4 of the object at offset 0x41c; when that exists, has bit 0x40
// set in its byte at offset 0x2c, and the slot at offset 0xa48 is empty, it stores it there, and
// when the slot at 0xa4c of the object at its offset 0x161c is also empty, links that object back
// to the object at offset 0x41c and sets the word at offset 0xa4c to 1. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10b9b8c0;

class UnkType_10b9b8c0_Actor
{
public:
    unsigned char unk_0[0x2c];
    unsigned char unk_2c;
    unsigned char unk_2d[0x9c4 - 0x2d];
    UnkType_10b9b8c0_Actor* unk_9c4;
    unsigned char unk_9c8[0x161c - 0x9c8];
    UnkType_10b9b8c0* unk_161c;
};

class UnkType_10b9b8c0
{
public:
    unsigned char unk_0[0x41c];
    UnkType_10b9b8c0_Actor* unk_41c;
    unsigned char unk_420[0xa48 - 0x420];
    UnkType_10b9b8c0_Actor* unk_a48;
    int unk_a4c;

    void Unk_10b9b8c0();
};

// UnkType_10b9b8c0::Unk_10b9b8c0
void UnkType_10b9b8c0::Unk_10b9b8c0()
{
    UnkType_10b9b8c0_Actor* Other = unk_41c->unk_9c4;
    if ( Other && ( Other->unk_2c & 0x40 ) && !unk_a48 )
    {
        unk_a48 = Other;
        if ( !Other->unk_161c->unk_a4c )
        {
            Other->unk_161c->unk_a48 = unk_41c;
            unk_a4c = 1;
        }
    }
}
