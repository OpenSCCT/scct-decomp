// campaign_leaf_013560.cpp -- method at VA 0x10913560: removes elements from an array of 0x3c-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x1090c880, then passes both arguments and the
// element size to the method at VA 0x1090b660. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_1090c880_013560
{
public:
    ~UnkType_1090c880_013560();

private:
    unsigned char unk_00[0x3c];
};

class UnkType_10913560
{
public:
    void Unk_10913560(int Index, int Count);
    void Unk_1090b660(int Index, int Count, int ElementSize);

private:
    UnkType_1090c880_013560* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10913560::Unk_10913560
void UnkType_10913560::Unk_10913560(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_1090c880_013560();
    }
    Unk_1090b660(Index, Count, sizeof(UnkType_1090c880_013560));
}
