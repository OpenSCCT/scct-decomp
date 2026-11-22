// campaign_leaf_550ea0.cpp -- one function at file offset 0x550ea0, preferred VA 0x10e50ea0.
// It fills Out from about forty of the object's fields, some read through the object at offset
// 0xcc and the one that object points to at its offset 0xc, and one computed as the quotient of
// the floats at offsets 0x248 and 0x244. The class, structure, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_10e50ea0_Inner
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15[3];
    int unk_18;
    int unk_1c;
};

struct UnkType_10e50ea0_Link
{
    int unk_0;
    int unk_4;
    int unk_8;
    UnkType_10e50ea0_Inner* unk_c;
};

struct UnkType_10e50ea0_Out
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10;
    unsigned char unk_11[0x3];
    int unk_14;
    unsigned char unk_18[0x8];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    unsigned char unk_50;
    unsigned char unk_51;
    unsigned char unk_52[0x2];
    float unk_54;
    float unk_58;
    int unk_5c;
    int unk_60;
    unsigned char unk_64;
    unsigned char unk_65[0x3];
    int unk_68;
    int unk_6c;
    int unk_70;
    unsigned char unk_74[0x4];
    unsigned char unk_78;
    unsigned char unk_79[0x3];
    int unk_7c;
    int unk_80;
    unsigned char unk_84;
    unsigned char unk_85[0x3];
    int unk_88;
    int unk_8c;
};

class UnkType_10e50ea0
{
public:
    unsigned char unk_0[0x30];
    int unk_30;
    int unk_34;
    unsigned char unk_38[0x94];
    UnkType_10e50ea0_Link* unk_cc;
    unsigned char unk_d0[0x10];
    int unk_e0;
    int unk_e4;
    int unk_e8;
    int unk_ec;
    unsigned char unk_f0[0x74];
    int unk_164;
    int unk_168;
    unsigned char unk_16c[0x10];
    int unk_17c;
    unsigned char unk_180[0x90];
    int unk_210;
    int unk_214;
    int unk_218;
    int unk_21c;
    int unk_220;
    int unk_224;
    int unk_228;
    int unk_22c;
    int unk_230;
    int unk_234;
    unsigned char unk_238[0x4];
    unsigned char unk_23c;
    unsigned char unk_23d;
    unsigned char unk_23e;
    unsigned char unk_23f;
    unsigned char unk_240[0x4];
    float unk_244;
    float unk_248;
    int unk_24c;

    void Unk_10e50ea0(UnkType_10e50ea0_Out& Out);
};

// UnkType_10e50ea0::Unk_10e50ea0
void UnkType_10e50ea0::Unk_10e50ea0(UnkType_10e50ea0_Out& Out)
{
    Out.unk_0 = unk_e0;
    Out.unk_4 = unk_e4;
    Out.unk_8 = unk_e8;
    Out.unk_c = unk_ec;
    Out.unk_10 = unk_23c;
    Out.unk_20 = unk_210;
    Out.unk_24 = unk_214;
    Out.unk_28 = unk_218;
    Out.unk_2c = unk_21c;
    Out.unk_30 = unk_220;
    Out.unk_34 = unk_224;
    Out.unk_38 = unk_228;
    Out.unk_3c = unk_22c;
    Out.unk_14 = unk_234;
    Out.unk_40 = unk_230;
    Out.unk_44 = unk_164;
    Out.unk_48 = unk_168;
    Out.unk_4c = unk_17c;
    Out.unk_60 = unk_cc->unk_8;
    Out.unk_68 = unk_cc->unk_c->unk_4;
    Out.unk_6c = unk_cc->unk_c->unk_8;
    Out.unk_70 = unk_cc->unk_c->unk_c;
    Out.unk_64 = unk_cc->unk_c->unk_0;
    Out.unk_78 = unk_cc->unk_c->unk_14;
    Out.unk_7c = unk_cc->unk_c->unk_18;
    Out.unk_80 = unk_cc->unk_c->unk_1c;
    Out.unk_50 = unk_23e;
    Out.unk_51 = unk_23f;
    Out.unk_54 = unk_244;
    Out.unk_58 = unk_248 / unk_244;
    Out.unk_5c = unk_24c;
    Out.unk_84 = unk_23d;
    Out.unk_88 = unk_30;
    Out.unk_8c = unk_34;
}
