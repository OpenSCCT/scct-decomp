// campaign_leaf_316880.cpp -- one function at file offset 0x316880, preferred VA 0x10c16880. It
// removes Count 0x254-byte elements from Index of the array at 0x0, destroying each first: every
// element holds at 0x8 nine 0x40-byte members, which the destructor at 0x10c14d60 destroys in
// reverse order. Then the method at 0x10c12d50 removes the elements. The class, method, member,
// local and parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10c14d60
{
public:
    ~UnkType_10c14d60();

    unsigned char unk_0[0x40];
};

class UnkType_10c16880_Element
{
public:
    unsigned char unk_0[0x8];
    UnkType_10c14d60 unk_8[9];
    unsigned char unk_248[0xc];
};

class UnkType_10c16880
{
public:
    void Unk_10c12d50(int Index, int Count, int Size);
    void Unk_10c16880(int Index, int Count);

    UnkType_10c16880_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c16880::Unk_10c16880
void UnkType_10c16880::Unk_10c16880(int Index, int Count)
{
    int Element;

    for ( Element = Index; Element < Index + Count; Element++ )
    {
        unk_0[Element].~UnkType_10c16880_Element();
    }
    Unk_10c12d50(Index, Count, sizeof(UnkType_10c16880_Element));
}
