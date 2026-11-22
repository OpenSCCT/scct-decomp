// campaign_leaf_59ad80.cpp -- one function at file offset 0x59ad80, preferred VA 0x10e9ad80. It
// fills Out from four of the object's fields (one read through the pointer at offset 0x38) and
// copies the object's 32-byte array at offset 0xc byte by byte. The class, structure, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_10e9ad80_Inner
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

struct UnkType_10e9ad80_Out
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    char unk_10[32];
};

class UnkType_10e9ad80
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    char unk_c[32];
    int unk_2c;
    int unk_30;
    int unk_34;
    UnkType_10e9ad80_Inner* unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;

    void Unk_10e9ad80(UnkType_10e9ad80_Out* Out);
};

// UnkType_10e9ad80::Unk_10e9ad80
void UnkType_10e9ad80::Unk_10e9ad80(UnkType_10e9ad80_Out* Out)
{
    int i;

    Out->unk_8 = unk_44;
    Out->unk_c = unk_48;
    Out->unk_4 = unk_38->unk_c;
    Out->unk_0 = unk_8;
    for ( i = 0; i < 32; i++ )
    {
        Out->unk_10[i] = unk_c[i];
    }
}
