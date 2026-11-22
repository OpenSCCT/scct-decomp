// campaign_leaf_5a0da0.cpp -- one function at file offset 0x5a0da0, preferred VA 0x10ea0da0. It
// copies the ten ints at offset 0x14 of the object, one by one, to Out. The class, structure,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10ea0da0_Value
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

class UnkType_10ea0da0
{
public:
    unsigned char unk_0[0x14];
    UnkType_10ea0da0_Value unk_14;

    void GetUnk14(UnkType_10ea0da0_Value& Out) const;
};

// UnkType_10ea0da0::GetUnk14
void UnkType_10ea0da0::GetUnk14(UnkType_10ea0da0_Value& Out) const
{
    Out.unk_0 = unk_14.unk_0;
    Out.unk_4 = unk_14.unk_4;
    Out.unk_8 = unk_14.unk_8;
    Out.unk_c = unk_14.unk_c;
    Out.unk_10 = unk_14.unk_10;
    Out.unk_14 = unk_14.unk_14;
    Out.unk_18 = unk_14.unk_18;
    Out.unk_1c = unk_14.unk_1c;
    Out.unk_20 = unk_14.unk_20;
    Out.unk_24 = unk_14.unk_24;
}
