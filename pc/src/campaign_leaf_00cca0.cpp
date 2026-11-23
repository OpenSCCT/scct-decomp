// campaign_leaf_00cca0.cpp -- method at VA 0x1090cca0: removes elements from an array of 0x1c-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x1090c6b0, then passes both arguments and the
// element size to the method at VA 0x1090b4d0. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_1090c6b0_00cca0
{
public:
    ~UnkType_1090c6b0_00cca0();

private:
    unsigned char unk_00[0x1c];
};

class UnkType_1090cca0
{
public:
    void Unk_1090cca0(int Index, int Count);
    void Unk_1090b4d0(int Index, int Count, int ElementSize);

private:
    UnkType_1090c6b0_00cca0* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1090cca0::Unk_1090cca0
void UnkType_1090cca0::Unk_1090cca0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_1090c6b0_00cca0();
    }
    Unk_1090b4d0(Index, Count, sizeof(UnkType_1090c6b0_00cca0));
}
