// campaign_leaf_3ae100.cpp -- one function at file offset 0x3ae100, preferred VA 0x10cae100. It
// copies the byte at 0x4 and the bytes at 0x5 to 0x11 from In to Out. The function, structure,
// member and parameter names are invented; the offsets and the bytes are the binary's.

struct UnkType_10cae100_Record
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

// Unk_10cae100
void Unk_10cae100(UnkType_10cae100_Record* Out, const UnkType_10cae100_Record* In)
{
    Out->unk_4 = In->unk_4;
    Out->unk_5 = In->unk_5;
    Out->unk_6 = In->unk_6;
    Out->unk_7 = In->unk_7;
    Out->unk_8 = In->unk_8;
    Out->unk_9 = In->unk_9;
    Out->unk_a = In->unk_a;
    Out->unk_b = In->unk_b;
    Out->unk_c = In->unk_c;
    Out->unk_d = In->unk_d;
    Out->unk_e = In->unk_e;
    Out->unk_f = In->unk_f;
    Out->unk_10 = In->unk_10;
    Out->unk_11 = In->unk_11;
}
