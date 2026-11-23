// campaign_leaf_051d30.cpp -- method at VA 0x10951d30: removes elements from an array of 0x98-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x10951330, then passes both arguments and the
// element size to the method at VA 0x1094bdf0. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_10951330_051d30
{
public:
    ~UnkType_10951330_051d30();

private:
    unsigned char unk_00[0x98];
};

class UnkType_10951d30
{
public:
    void Unk_10951d30(int Index, int Count);
    void Unk_1094bdf0(int Index, int Count, int ElementSize);

private:
    UnkType_10951330_051d30* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10951d30::Unk_10951d30
void UnkType_10951d30::Unk_10951d30(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10951330_051d30();
    }
    Unk_1094bdf0(Index, Count, sizeof(UnkType_10951330_051d30));
}
