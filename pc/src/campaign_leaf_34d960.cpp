// campaign_leaf_34d960.cpp -- one function at file offset 0x34d960, preferred VA 0x10c4d960. It
// copies Other into this object member by member: the words at 0x0 and 0x4, the 12-byte block at
// 0x8, the member at 0x14 (through its method at 0x10c4d160), the word at 0x20, bits 0 and 1 of
// the word at 0x24 and the word at 0x28; it returns this object. The class, method, structure,
// member and parameter names are invented; the offsets and the bytes are the binary's.

struct UnkType_10c4d960_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10c4d960_Member
{
public:
    UnkType_10c4d960_Member& Unk_10c4d160(const UnkType_10c4d960_Member& Other);

    unsigned char unk_0[0xc];
};

class UnkType_10c4d960
{
public:
    UnkType_10c4d960& Unk_10c4d960(const UnkType_10c4d960& Other);

    int unk_0;
    int unk_4;
    UnkType_10c4d960_Vector unk_8;
    UnkType_10c4d960_Member unk_14;
    int unk_20;
    unsigned int bUnk_24_0 : 1;
    unsigned int bUnk_24_1 : 1;
    int unk_28;
};

// UnkType_10c4d960::Unk_10c4d960
UnkType_10c4d960& UnkType_10c4d960::Unk_10c4d960(const UnkType_10c4d960& Other)
{
    unk_0 = Other.unk_0;
    unk_4 = Other.unk_4;
    unk_8 = Other.unk_8;
    unk_14.Unk_10c4d160(Other.unk_14);
    unk_20 = Other.unk_20;
    bUnk_24_0 = Other.bUnk_24_0;
    bUnk_24_1 = Other.bUnk_24_1;
    unk_28 = Other.unk_28;
    return *this;
}
