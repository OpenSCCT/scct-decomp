// campaign_leaf_1cfba0.cpp -- thiscall method at VA 0x10acfba0 of an array of 12-byte arrays of
// 16-bit words. It destroys every element (each is emptied, its data reallocated to nothing through
// slot 1 of the allocator at VA 0x111c88a0; its method at VA 0x10907710 then removes all its words,
// its data is freed through slot 2 and its three words are cleared) and sets the count to zero. The
// class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10907710
{
public:
    // UnkType_10907710::~UnkType_10907710
    ~UnkType_10907710()
    {
        Unk_10907710(0, unk_4, 2);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    // UnkType_10907710::Empty
    void Empty(int Slack = 0)
    {
        unk_4 = 0;
        unk_8 = Slack;
        unk_0 = (unsigned short*)GUnk_111c88a0->Realloc(unk_0, unk_8 * 2, L"FArray::_WORD");
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10acfba0_String : public UnkType_10907710
{
public:
    // UnkType_10acfba0_String::~UnkType_10acfba0_String
    ~UnkType_10acfba0_String()
    {
        Empty();
    }
};

class UnkType_10acfba0
{
public:
    void Unk_10acfba0();

private:
    UnkType_10acfba0_String* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10acfba0::Unk_10acfba0
void UnkType_10acfba0::Unk_10acfba0()
{
    for ( int i = 0; i < unk_4; i++ )
    {
        (&unk_0[i])->~UnkType_10acfba0_String();
    }
    unk_4 = 0;
}
