// campaign_leaf_348210.cpp -- one function at file offset 0x348210, preferred VA 0x10c48210. It
// clears bit field 0 and sets bit field 1 of the word at offset 0x44c, clears the word at offset
// 0x410, and sets bit 0x80 of the flags at offset 0x30 of the object reached through offsets 0x474
// and 0x470 when both pointers are non-null. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10c48210_Target
{
public:
    unsigned char unk_0[0x30];
    int unk_30;
};

class UnkType_10c48210_Owner
{
public:
    unsigned char unk_0[0x470];
    UnkType_10c48210_Target* unk_470;
};

class UnkType_10c48210
{
public:
    unsigned char unk_0[0x410];
    int unk_410;
    unsigned char unk_414[0x44c - 0x414];
    unsigned int unk_44c_0 : 1;
    unsigned int unk_44c_1 : 1;
    unsigned char unk_450[0x474 - 0x450];
    UnkType_10c48210_Owner* unk_474;

    void Unk_10c48210();
};

// UnkType_10c48210::Unk_10c48210
void UnkType_10c48210::Unk_10c48210()
{
    unk_44c_0 = 0;
    unk_44c_1 = 1;
    unk_410 = 0;
    if ( unk_474 && unk_474->unk_470 )
    {
        unk_474->unk_470->unk_30 |= 0x80;
    }
}
