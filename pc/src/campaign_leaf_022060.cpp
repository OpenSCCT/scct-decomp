// campaign_leaf_022060.cpp -- method at VA 0x10922060: removes elements from an array of 0x2c-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x10921fe0, then passes both arguments and the
// element size to the method at VA 0x1090b3b0. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_10921fe0_022060
{
public:
    ~UnkType_10921fe0_022060();

private:
    unsigned char unk_00[0x2c];
};

class UnkType_10922060
{
public:
    void Unk_10922060(int Index, int Count);
    void Unk_1090b3b0(int Index, int Count, int ElementSize);

private:
    UnkType_10921fe0_022060* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10922060::Unk_10922060
void UnkType_10922060::Unk_10922060(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10921fe0_022060();
    }
    Unk_1090b3b0(Index, Count, sizeof(UnkType_10921fe0_022060));
}
