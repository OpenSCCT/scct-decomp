// campaign_leaf_71cfb0.cpp -- one function at file offset 0x71cfb0, preferred VA 0x1101cfb0. A
// destructor: it installs the vtable at VA 0x11170a28, passes this object to the first virtual
// method of every set entry of the pointer array at 0x48, last entry first, frees the storage of
// the arrays at 0x48 and 0x3c through the allocator at VA 0x1131b3d8 when they own it (a clear
// top bit in the capacity word) and runs the base destructor at VA 0x10e504c0. The class, method
// and member names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

// UnkType_1101cfb0_Array: a pointer to the elements, their count and the capacity, whose top bit
// is set when the storage is not owned.
template <class T> struct UnkType_1101cfb0_Array
{
    T* unk_0;
    int unk_4;
    int unk_8;

    // UnkType_1101cfb0_Array::~UnkType_1101cfb0_Array
    ~UnkType_1101cfb0_Array()
    {
        if ( ( unk_8 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_0, (unk_8 & 0x7fffffff) * sizeof(T), 0x12);
        }
    }
};

class UnkType_1101cfb0_Child
{
public:
    virtual void VirtualSlot0(void* Owner);
};

class UnkType_1101cfb0_Base
{
public:
    virtual ~UnkType_1101cfb0_Base();

    unsigned char unk_4[0x3c - 0x4];
};

class UnkType_1101cfb0 : public UnkType_1101cfb0_Base
{
public:
    virtual ~UnkType_1101cfb0();

    UnkType_1101cfb0_Array<int> unk_3c;
    UnkType_1101cfb0_Array<UnkType_1101cfb0_Child*> unk_48;
};

// UnkType_1101cfb0::~UnkType_1101cfb0
UnkType_1101cfb0::~UnkType_1101cfb0()
{
    int Index;
    UnkType_1101cfb0_Child* Child;

    for ( Index = unk_48.unk_4 - 1; Index >= 0; Index-- )
    {
        Child = unk_48.unk_0[Index];
        if ( Child != 0 )
        {
            Child->VirtualSlot0(this);
        }
    }
}
