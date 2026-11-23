// campaign_leaf_08c800.cpp -- method at VA 0x1098c800: removes elements from an array of 0x14-byte
// elements (data at 0x00): destroys the string at 0x04 of each element from the index its first
// argument gives, as many as its second argument (empties it, reallocating its data through virtual
// slot 1 of the allocator the global at VA 0x111c88a0 points to, tagged "FArray::_WORD", removes
// its 2-byte characters with the method at VA 0x10907710, frees its data through slot 2 and clears
// it), then passes both arguments and the element size to the method at VA 0x1098b2c0. The class,
// member and method names are invented; the offsets, the sizes, the tag and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10907710_08c800
{
public:
    ~UnkType_10907710_08c800()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = static_cast<unsigned short*>(GUnk_111c88a0->Realloc(unk_00, 0,
                                                                       L"FArray::_WORD"));
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_08c800_String : public UnkType_10907710_08c800
{
public:
    ~UnkType_08c800_String()
    {
        Empty();
    }
};

class UnkType_08c800_Item
{
private:
    int unk_00;
    UnkType_08c800_String unk_04;
    unsigned char unk_10[0x14 - 0x10];
};

class UnkType_1098c800
{
public:
    void Unk_1098c800(int Index, int Count);
    void Unk_1098b2c0(int Index, int Count, int ElementSize);

private:
    UnkType_08c800_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1098c800::Unk_1098c800
void UnkType_1098c800::Unk_1098c800(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_08c800_Item();
    }
    Unk_1098b2c0(Index, Count, sizeof(UnkType_08c800_Item));
}
