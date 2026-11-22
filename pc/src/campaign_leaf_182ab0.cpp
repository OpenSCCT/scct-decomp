// campaign_leaf_182ab0.cpp -- one function at file offset 0x182ab0, preferred VA 0x10a82ab0. When
// its argument is non-null it returns the first non-null entry of the pointer array at offset 0x28
// (count at 0x2c) of the object at offset 0x7c whose word at offset 0x54 is the argument; otherwise
// null. The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x54];
    void* unk_54;
};

class UnkList
{
public:
    unsigned char unk_0[0x28];
    UnkItem** unk_28;
    int unk_2c;
};

class UnkType_10a82ab0
{
public:
    unsigned char unk_0[0x7c];
    UnkList* unk_7c;

    UnkItem* Unk_10a82ab0(void* Key);
};

// UnkType_10a82ab0::Unk_10a82ab0
UnkItem* UnkType_10a82ab0::Unk_10a82ab0(void* Key)
{
    if ( Key )
    {
        for ( int i = 0; i < unk_7c->unk_2c; i++ )
        {
            if ( unk_7c->unk_28[i] && unk_7c->unk_28[i]->unk_54 == Key )
            {
                return unk_7c->unk_28[i];
            }
        }
    }
    return 0;
}
