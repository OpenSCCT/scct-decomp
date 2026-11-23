// campaign_leaf_08d5b0.cpp -- method at VA 0x1098d5b0: removes elements from an array of 0x40-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x1098cac0, then passes both arguments and the
// element size to the method at VA 0x1098bd10. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_1098cac0_08d5b0
{
public:
    ~UnkType_1098cac0_08d5b0();

private:
    unsigned char unk_00[0x40];
};

class UnkType_1098d5b0
{
public:
    void Unk_1098d5b0(int Index, int Count);
    void Unk_1098bd10(int Index, int Count, int ElementSize);

private:
    UnkType_1098cac0_08d5b0* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1098d5b0::Unk_1098d5b0
void UnkType_1098d5b0::Unk_1098d5b0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_1098cac0_08d5b0();
    }
    Unk_1098bd10(Index, Count, sizeof(UnkType_1098cac0_08d5b0));
}
