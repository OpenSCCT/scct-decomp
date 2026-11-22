// campaign_leaf_3ae0a0.cpp -- one function at file offset 0x3ae0a0, preferred VA 0x10cae0a0. It
// copies In's byte at 0x60 and its bytes at 0x68 to 0x74 to Out's bytes at 0x4 to 0x11. The
// function, structure, member and parameter names are invented; the offsets and the bytes are
// the binary's.

struct UnkType_10cae0a0_Record
{
    int unk_0;
    unsigned char unk_4;
    unsigned char unk_5;
    unsigned char unk_6;
    unsigned char unk_7;
    unsigned char unk_8;
    unsigned char unk_9;
    unsigned char unk_a;
    unsigned char unk_b;
    unsigned char unk_c;
    unsigned char unk_d;
    unsigned char unk_e;
    unsigned char unk_f;
    unsigned char unk_10;
    unsigned char unk_11;
};

struct UnkType_10cae0a0_Source
{
    unsigned char unk_0[0x60];
    unsigned char unk_60;
    unsigned char unk_61[7];
    unsigned char unk_68;
    unsigned char unk_69;
    unsigned char unk_6a;
    unsigned char unk_6b;
    unsigned char unk_6c;
    unsigned char unk_6d;
    unsigned char unk_6e;
    unsigned char unk_6f;
    unsigned char unk_70;
    unsigned char unk_71;
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
};

// Unk_10cae0a0
void Unk_10cae0a0(UnkType_10cae0a0_Record* Out, const UnkType_10cae0a0_Source* In)
{
    Out->unk_4 = In->unk_60;
    Out->unk_5 = In->unk_68;
    Out->unk_6 = In->unk_69;
    Out->unk_7 = In->unk_6a;
    Out->unk_8 = In->unk_6b;
    Out->unk_9 = In->unk_6c;
    Out->unk_a = In->unk_6d;
    Out->unk_b = In->unk_6e;
    Out->unk_c = In->unk_6f;
    Out->unk_d = In->unk_70;
    Out->unk_e = In->unk_71;
    Out->unk_f = In->unk_72;
    Out->unk_10 = In->unk_73;
    Out->unk_11 = In->unk_74;
}
