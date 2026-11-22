// campaign_leaf_29a8a0.cpp -- one function at file offset 0x29a8a0, preferred VA 0x10b9a8a0. It
// follows the pointer at offset 0x4d0 and then the one at 0x28 of that object, and returns the
// second object when its byte at 0x28 is 2 and its flags at 0xc8 have bit 0x10000 set and none of
// 0x15; otherwise null. The class, method and member names are invented; the offset and the bytes
// are the binary's.

class UnkType_10b9a8a0;

class UnkOwner_10b9a8a0
{
public:
    unsigned char unk_0[0x28];
    UnkType_10b9a8a0* unk_28;
};

class UnkType_10b9a8a0
{
public:
    unsigned char unk_0[0x28];
    unsigned char unk_28;
    unsigned char unk_29[0xc8 - 0x29];
    int unk_c8;
    unsigned char unk_cc[0x4d0 - 0xcc];
    UnkOwner_10b9a8a0* unk_4d0;

    UnkType_10b9a8a0* Unk_10b9a8a0();
};

// UnkType_10b9a8a0::Unk_10b9a8a0
UnkType_10b9a8a0* UnkType_10b9a8a0::Unk_10b9a8a0()
{
    if ( unk_4d0 )
    {
        UnkType_10b9a8a0* Other = unk_4d0->unk_28;
        if ( Other && Other->unk_28 == 2 && ( Other->unk_c8 & 0x10000 )
            && !( Other->unk_c8 & 0x15 ) )
        {
            return Other;
        }
    }
    return 0;
}
