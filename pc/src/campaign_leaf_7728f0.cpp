// campaign_leaf_7728f0.cpp -- one function at file offset 0x7728f0, preferred VA 0x110728f0. It
// calls the method at VA 0x110728a0 when the word its third argument points to is set, or when
// the method at VA 0x110727a0 returns zero for the first two arguments. The class, method and
// parameter names are invented; the offset and the addresses are the binary's.

class UnkType_110728f0
{
public:
    int Unk_110727a0(int First, int Second);
    void Unk_110728a0();
    void Unk_110728f0(int First, int Second, int* Third);
};

// UnkType_110728f0::Unk_110728f0
void UnkType_110728f0::Unk_110728f0(int First, int Second, int* Third)
{
    if ( *Third != 0 || Unk_110727a0(First, Second) == 0 )
    {
        Unk_110728a0();
    }
}
