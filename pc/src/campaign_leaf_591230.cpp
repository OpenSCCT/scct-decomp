// campaign_leaf_591230.cpp -- cdecl function at VA 0x10e91230: constructs a 1040-byte local object
// (constructor at VA 0x10e98960), passes it with its two arguments to the cdecl functions at VA
// 0x10e90ee0 and VA 0x10e95ca0, then destroys it, which frees the storage of its array of 8-byte
// entries at 0x04 through the allocator (sixth virtual method) unless the top bit of its capacity
// word is set. All names are invented.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e91230_Element8
{
    int unk_00;
    int unk_04;
};

struct UnkType_10e91230_Array
{
    UnkType_10e91230_Element8* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e91230_Array::~UnkType_10e91230_Array
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e91230_Array()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e91230_Element8), 0x12);
        }
    }
};

class UnkType_10e91230_Local
{
public:
    UnkType_10e91230_Local();

private:
    int unk_00;
    UnkType_10e91230_Array unk_04;
    int unk_10[0x400 / 4];
};

void Unk_10e90ee0(int First, UnkType_10e91230_Local* Local, int Second);
void Unk_10e95ca0(UnkType_10e91230_Local* Local, int Second);

// Unk_10e91230
void Unk_10e91230(int First, int Second)
{
    UnkType_10e91230_Local Local;
    Unk_10e90ee0(First, &Local, Second);
    Unk_10e95ca0(&Local, Second);
}
