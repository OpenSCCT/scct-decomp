// campaign_leaf_4b9f80.cpp -- one function at file offset 0x4b9f80, preferred VA 0x10db9f80.
// It passes its 12-byte argument by reference to the method at 0x10dab130 of the member at offset
// 0x9c and then calls the method at 0x10dc14d0 with 2. The class, structure, method and member
// names are invented; the offset and the bytes are the binary's.

struct UnkType_10db9f80_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10db9f80_Member
{
public:
    void Unk_10dab130(const UnkType_10db9f80_Value& Value);
};

class UnkType_10db9f80
{
public:
    unsigned char unk_0[0x9c];
    UnkType_10db9f80_Member unk_9c;

    void Unk_10dc14d0(int Value);
    void Unk_10db9f80(UnkType_10db9f80_Value Value);
};

// UnkType_10db9f80::Unk_10db9f80
void UnkType_10db9f80::Unk_10db9f80(UnkType_10db9f80_Value Value)
{
    unk_9c.Unk_10dab130(Value);
    Unk_10dc14d0(2);
}
