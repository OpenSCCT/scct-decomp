// campaign_leaf_273640.cpp -- destructor at VA 0x10b73640 of a class with a vtable (VA 0x110e7188):
// destroys the dynamic array at 0x0c (contents removed through the method at VA 0x10929170, element
// size 4; data freed through slot 2 of the allocator at VA 0x111c88a0; three words cleared); then
// its base class's inline destructor stores that class's vtable (VA 0x110e6f2c). The class, member
// and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b73640_Base
{
public:
    virtual ~UnkType_10b73640_Base()
    {
    }

private:
    int unk_04;
    int unk_08;
};

class UnkType_10b73640_Array
{
public:
    ~UnkType_10b73640_Array()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b73640 : public UnkType_10b73640_Base
{
public:
    virtual ~UnkType_10b73640();

private:
    UnkType_10b73640_Array unk_0c;
};

// UnkType_10b73640::~UnkType_10b73640
UnkType_10b73640::~UnkType_10b73640()
{
}
