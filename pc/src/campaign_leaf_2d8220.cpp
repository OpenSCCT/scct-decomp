// campaign_leaf_2d8220.cpp -- destructor at VA 0x10bd8220 of a class without a vtable: destroys the
// dynamic array at 0x0c (contents removed through the method at VA 0x10bd8070; data freed through
// slot 2 of the allocator at VA 0x111c88a0; three words cleared), then the string at 0x00
// (destructor at VA 0x1090ba70). The class, member and method names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bd8220_String
{
public:
    ~UnkType_10bd8220_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bd8220_Array
{
public:
    ~UnkType_10bd8220_Array()
    {
        Unk_10bd8070(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10bd8070(int Index, int Count);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bd8220
{
public:
    ~UnkType_10bd8220();

private:
    UnkType_10bd8220_String unk_00;
    UnkType_10bd8220_Array unk_0c;
};

// UnkType_10bd8220::~UnkType_10bd8220
UnkType_10bd8220::~UnkType_10bd8220()
{
}
