// campaign_leaf_378740.cpp -- one function at file offset 0x378740, preferred VA 0x10c78740. A
// destructor: it installs the vtable at 0x1110fab8, calls the method at 0x10cd7a30, destroys the
// arrays at 0x244 (removing its 2-byte elements with the method at 0x10907710) and 0x220 (removing
// its 0x1c-byte elements with the method at 0x10a54a40), freeing their data through the allocator
// at 0x111c88a0, and ends in the base destructor at 0x10a53b70. The class, method and member names
// are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c78740_Base
{
public:
    virtual ~UnkType_10c78740_Base();

    unsigned char unk_4[0x21c];
};

class UnkType_10a54a40
{
public:
    ~UnkType_10a54a40()
    {
        Unk_10a54a40(0, unk_4, 0x1c);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10a54a40(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

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

class UnkType_10c78740 : public UnkType_10c78740_Base
{
public:
    virtual ~UnkType_10c78740();
    void Unk_10cd7a30();

    UnkType_10a54a40 unk_220;
    unsigned char unk_22c[0x18];
    UnkType_10907710 unk_244;
};

// UnkType_10c78740::~UnkType_10c78740
UnkType_10c78740::~UnkType_10c78740()
{
    Unk_10cd7a30();
}
