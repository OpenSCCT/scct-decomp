// campaign_leaf_07aef0.cpp -- method at VA 0x1097aef0: removes elements from an array of 0x38-byte
// elements (data at 0x00): destroys the strings at 0x0c and 0x00 of each element from the index its
// first argument gives, as many as its second argument (each emptied, its data reallocated through
// virtual slot 1 of the allocator the global at VA 0x111c88a0 points to, tagged "FArray::_WORD",
// its 2-byte characters removed with the method at VA 0x10907710, its data freed through slot 2 and
// cleared), then passes both arguments and the element size to the method at VA 0x10977520. The
// class, member and method names are invented; the offsets, the sizes, the tag and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10907710_07aef0
{
public:
    ~UnkType_10907710_07aef0()
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

class UnkType_07aef0_String : public UnkType_10907710_07aef0
{
public:
    ~UnkType_07aef0_String()
    {
        Empty();
    }
};

class UnkType_07aef0_Item
{
private:
    UnkType_07aef0_String unk_00;
    UnkType_07aef0_String unk_0c;
    unsigned char unk_18[0x38 - 0x18];
};

class UnkType_1097aef0
{
public:
    void Unk_1097aef0(int Index, int Count);
    void Unk_10977520(int Index, int Count, int ElementSize);

private:
    UnkType_07aef0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1097aef0::Unk_1097aef0
void UnkType_1097aef0::Unk_1097aef0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_07aef0_Item();
    }
    Unk_10977520(Index, Count, sizeof(UnkType_07aef0_Item));
}
