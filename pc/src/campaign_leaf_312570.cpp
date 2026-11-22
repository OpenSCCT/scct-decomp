// campaign_leaf_312570.cpp -- one function at file offset 0x312570, preferred VA 0x10c12570. When
// the index its first argument points to is below the count at offset 0x894, it copies the first
// word of that 16-byte entry of the array at offset 0x890 through its second argument and returns
// 1; otherwise it returns 0. The class, method and member names are invented; the offset and the
// bytes are the binary's.

struct UnkEntry_10c12570
{
    int unk_0;
    int unk_4[3];
};

class UnkType_10c12570
{
public:
    unsigned char unk_0[0x890];
    UnkEntry_10c12570* unk_890;
    int unk_894;

    int Unk_10c12570(const int* Index, int* Out);
};

// UnkType_10c12570::Unk_10c12570
int UnkType_10c12570::Unk_10c12570(const int* Index, int* Out)
{
    if ( *Index < unk_894 )
    {
        *Out = unk_890[*Index].unk_0;
        return 1;
    }
    return 0;
}
