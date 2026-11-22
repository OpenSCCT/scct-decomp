// campaign_leaf_5a3540.cpp -- one function at file offset 0x5a3540, preferred VA 0x10ea3540.
// It copies ten ints of the object, from offsets 0x10, 0xc and 0x14-0x30, into Out, with the
// first two and the pair at 0x28 and 0x2c exchanged. The class, structure, method and member
// names are invented; the offset and the bytes are the binary's.

struct UnkType_10ea3540_Out
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

class UnkType_10ea3540
{
public:
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
    int unk_28;
    int unk_2c;
    int unk_30;

    void Unk_10ea3540(UnkType_10ea3540_Out& Out) const;
};

// UnkType_10ea3540::Unk_10ea3540
void UnkType_10ea3540::Unk_10ea3540(UnkType_10ea3540_Out& Out) const
{
    Out.unk_0 = unk_10;
    Out.unk_4 = unk_c;
    Out.unk_8 = unk_14;
    Out.unk_c = unk_18;
    Out.unk_10 = unk_1c;
    Out.unk_14 = unk_20;
    Out.unk_18 = unk_24;
    Out.unk_20 = unk_28;
    Out.unk_1c = unk_2c;
    Out.unk_24 = unk_30;
}
