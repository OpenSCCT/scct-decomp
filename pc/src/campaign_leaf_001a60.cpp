// campaign_leaf_001a60.cpp -- method at VA 0x10901a60: when the handle at 0x04 is not -1, calls
// virtual slot 5 (vtable offset 0x14), closes the handle with CloseHandle and sets it to -1. The
// class, member and method names are invented; the offset, the constant and the slot are the
// binary's.

#include "campaign_import_CloseHandle.h"

class UnkType_10901a60
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();

    void Unk_10901a60();

private:
    HANDLE unk_04;
};

// UnkType_10901a60::Unk_10901a60
void UnkType_10901a60::Unk_10901a60()
{
    if ( unk_04 != (HANDLE)-1 )
    {
        VirtualSlot5();
        CloseHandle(unk_04);
        unk_04 = (HANDLE)-1;
    }
}
