// campaign_leaf_276250.cpp -- destructor at VA 0x10b76250 of a class with a vtable (VA 0x110e74cc):
// calls the method at VA 0x10b76120, then destroys the dynamic array at 0x04 (contents removed
// through the method at VA 0x10b75d00, element size 4; data freed through slot 2 of the allocator
// at VA 0x111c88a0; three words cleared). The class, member and method names are invented; the
// offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b76250_Array
{
public:
    ~UnkType_10b76250_Array()
    {
        Unk_10b75d00(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10b75d00(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b76250
{
public:
    virtual ~UnkType_10b76250();

    void Unk_10b76120();

private:
    UnkType_10b76250_Array unk_04;
};

// UnkType_10b76250::~UnkType_10b76250
UnkType_10b76250::~UnkType_10b76250()
{
    Unk_10b76120();
}
