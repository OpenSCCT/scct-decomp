// campaign_leaf_02c0b0.cpp -- one function at file offset 0x2c0b0, preferred VA 0x1092c0b0. It
// stores its sixteen word arguments into the sixteen words of this object, in order, and returns
// this object. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_1092c0b0
{
public:
    UnkType_1092c0b0 *UnkSetAll(int Value00, int Value04, int Value08, int Value0c, int Value10,
                                int Value14, int Value18, int Value1c, int Value20, int Value24,
                                int Value28, int Value2c, int Value30, int Value34, int Value38,
                                int Value3c);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_1092c0b0::UnkSetAll
UnkType_1092c0b0 *UnkType_1092c0b0::UnkSetAll(int Value00, int Value04, int Value08, int Value0c,
                                              int Value10, int Value14, int Value18, int Value1c,
                                              int Value20, int Value24, int Value28, int Value2c,
                                              int Value30, int Value34, int Value38, int Value3c)
{
    unk_00 = Value00;
    unk_04 = Value04;
    unk_08 = Value08;
    unk_0c = Value0c;
    unk_10 = Value10;
    unk_14 = Value14;
    unk_18 = Value18;
    unk_1c = Value1c;
    unk_20 = Value20;
    unk_24 = Value24;
    unk_28 = Value28;
    unk_2c = Value2c;
    unk_30 = Value30;
    unk_34 = Value34;
    unk_38 = Value38;
    unk_3c = Value3c;
    return this;
}
