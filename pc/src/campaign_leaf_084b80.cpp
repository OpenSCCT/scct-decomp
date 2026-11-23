// campaign_leaf_084b80.cpp -- method at VA 0x10984b80: passes each index below the count at 0x9c,
// with its argument, to the method at VA 0x10984af0. The class, member and method names are
// invented; the offset and the address are the binary's.

class UnkType_10984b80
{
public:
    void Unk_10984b80(int Value);
    void Unk_10984af0(int Index, int Value);

private:
    unsigned char unk_00[0x9c];
    int unk_9c;
};

// UnkType_10984b80::Unk_10984b80
void UnkType_10984b80::Unk_10984b80(int Value)
{
    for ( int i = 0; i < unk_9c; i++ )
    {
        Unk_10984af0(i, Value);
    }
}
