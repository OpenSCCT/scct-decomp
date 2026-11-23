// campaign_leaf_580e30.cpp -- thiscall method at VA 0x10e80e30: when the pointer at 0x00 is set,
// passes it to the second virtual method of the object the global at VA 0x1131b3d8 points to. The
// class, method and global names are invented.

#include "campaign_global_1131b3d8.h"

class UnkType_10e80e30
{
public:
    void Unk_10e80e30();

private:
    void* unk_00;
};

// UnkType_10e80e30::Unk_10e80e30
void UnkType_10e80e30::Unk_10e80e30()
{
    if ( unk_00 )
    {
        GUnk_1131b3d8->VirtualSlot1(unk_00);
    }
}
