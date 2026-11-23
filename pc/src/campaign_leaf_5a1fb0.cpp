// campaign_leaf_5a1fb0.cpp -- destructor at VA 0x10ea1fb0: installs this class's vtable (VA
// 0x11151c2c), destroys each 28-byte object in the array at 0x0c through its virtual destructor,
// then the array (storage through the allocator unless the top bit of the capacity word is set) and
// the base part, whose inline destructor installs the vtable at VA 0x110c1d60. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10ea1fb0_Root
{
public:
    // UnkType_10ea1fb0_Root::~UnkType_10ea1fb0_Root
    virtual ~UnkType_10ea1fb0_Root()
    {
    }
};

class UnkType_10ea1fb0_Element
{
public:
    virtual ~UnkType_10ea1fb0_Element();

private:
    int unk_04[6];
};

struct UnkType_10ea1fb0_Array
{
    UnkType_10ea1fb0_Element* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10ea1fb0_Array::DestroyElements
    void DestroyElements()
    {
        for ( int Index = 0; Index < unk_04; Index++ )
        {
            ( &unk_00[Index] )->~UnkType_10ea1fb0_Element();
        }
    }

    // UnkType_10ea1fb0_Array::~UnkType_10ea1fb0_Array
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10ea1fb0_Array()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10ea1fb0_Element), 0x12);
        }
    }
};

class UnkType_10ea1fb0 : public UnkType_10ea1fb0_Root
{
public:
    ~UnkType_10ea1fb0();

private:
    int unk_04;
    int unk_08;
    UnkType_10ea1fb0_Array unk_0c;
};

// UnkType_10ea1fb0::~UnkType_10ea1fb0
UnkType_10ea1fb0::~UnkType_10ea1fb0()
{
    unk_0c.DestroyElements();
}
