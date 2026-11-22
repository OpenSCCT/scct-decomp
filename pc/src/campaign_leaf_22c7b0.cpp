// campaign_leaf_22c7b0.cpp -- one function at file offset 0x22c7b0, preferred VA 0x10b2c7b0. A
// three-way comparison of two objects: 0 when either is null, otherwise ordered by the byte at
// offset 0x3c (larger first) and then by the word at offset 0x40 (smaller first). It has no this
// pointer. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10b2c7b0
{
public:
    unsigned char unk_0[0x3c];
    unsigned char unk_3c;
    unsigned char unk_3d[3];
    int unk_40;

    static int Unk_10b2c7b0(const UnkType_10b2c7b0* A, const UnkType_10b2c7b0* B);
};

// UnkType_10b2c7b0::Unk_10b2c7b0
int UnkType_10b2c7b0::Unk_10b2c7b0(const UnkType_10b2c7b0* A, const UnkType_10b2c7b0* B)
{
    if ( !A || !B )
    {
        return 0;
    }
    if ( A->unk_3c > B->unk_3c )
    {
        return 1;
    }
    if ( A->unk_3c < B->unk_3c )
    {
        return -1;
    }
    if ( A->unk_40 > B->unk_40 )
    {
        return -1;
    }
    return A->unk_40 < B->unk_40;
}
