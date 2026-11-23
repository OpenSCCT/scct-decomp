// campaign_leaf_01d320.cpp -- method at VA 0x1091d320: removes elements from an array of 0x2c-byte
// elements (data at 0x00): destroys the elements from the index its first argument gives, as many
// as its second argument, with the destructor at VA 0x1091b570, then passes both arguments and the
// element size to the method at VA 0x1091d370. The class, member and method names are invented; the
// offsets, the size and the addresses are the binary's.

class UnkType_1091b570_01d320
{
public:
    ~UnkType_1091b570_01d320();

private:
    unsigned char unk_00[0x2c];
};

class UnkType_1091d320
{
public:
    void Unk_1091d320(int Index, int Count);
    void Unk_1091d370(int Index, int Count, int ElementSize);

private:
    UnkType_1091b570_01d320* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1091d320::Unk_1091d320
void UnkType_1091d320::Unk_1091d320(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_1091b570_01d320();
    }
    Unk_1091d370(Index, Count, sizeof(UnkType_1091b570_01d320));
}
