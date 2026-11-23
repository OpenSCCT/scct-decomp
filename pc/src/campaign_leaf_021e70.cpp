// campaign_leaf_021e70.cpp -- method at VA 0x10921e70: removes elements from an array of 0x24-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x10921410, then passes both arguments and the
// element size to the method at VA 0x1090b560. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_10921410_021e70
{
public:
    ~UnkType_10921410_021e70();

private:
    unsigned char unk_00[0x24];
};

class UnkType_10921e70
{
public:
    void Unk_10921e70(int Index, int Count);
    void Unk_1090b560(int Index, int Count, int ElementSize);

private:
    UnkType_10921410_021e70* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10921e70::Unk_10921e70
void UnkType_10921e70::Unk_10921e70(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10921410_021e70();
    }
    Unk_1090b560(Index, Count, sizeof(UnkType_10921410_021e70));
}
