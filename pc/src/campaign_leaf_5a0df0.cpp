// campaign_leaf_5a0df0.cpp -- one function at file offset 0x5a0df0, preferred VA 0x10ea0df0. It
// copies the ten ints of Value, one by one, into the object at offset 0x14. The class, structure,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10ea0df0_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
};

class UnkType_10ea0df0
{
public:
    unsigned char unk_0[0x14];
    UnkType_10ea0df0_Value unk_14;

    void SetUnk14(const UnkType_10ea0df0_Value& Value);
};

// UnkType_10ea0df0::SetUnk14
void UnkType_10ea0df0::SetUnk14(const UnkType_10ea0df0_Value& Value)
{
    unk_14.unk_0 = Value.unk_0;
    unk_14.unk_4 = Value.unk_4;
    unk_14.unk_8 = Value.unk_8;
    unk_14.unk_c = Value.unk_c;
    unk_14.unk_10 = Value.unk_10;
    unk_14.unk_14 = Value.unk_14;
    unk_14.unk_18 = Value.unk_18;
    unk_14.unk_1c = Value.unk_1c;
    unk_14.unk_20 = Value.unk_20;
    unk_14.unk_24 = Value.unk_24;
}
