// campaign_leaf_07c340.cpp -- constructor at VA 0x1097c340 of a class whose vtable is at VA
// 0x110c1508: runs the base constructor at VA 0x1097b210, then stores at 0xe8 a new 0x14-byte
// object (allocated through slot 0 of the allocator the global at VA 0x111c88a0 points to, tagged
// "FStaticVolumeTexture"; vtable at VA 0x110c0e28) that points back to this one at 0x0c, holds
// 0x100 times the value at 0x04 of this object plus 0x34 as a 64-bit value at 0x04 and 1 at 0x10,
// or 0 when the allocation fails. The class and member names are invented; the offsets, the sizes,
// the constants, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_1097c340_Base
{
public:
    UnkType_1097c340_Base();
    virtual ~UnkType_1097c340_Base();

    int unk_04;

private:
    unsigned char unk_08[0xe8 - 0x08];
};

#pragma pack(push, 4)

class UnkType_110c0e28_07c340_Base
{
public:
    UnkType_110c0e28_07c340_Base(UnkType_1097c340_Base* Owner)
    : unk_08(Owner)
    {
    }

    unsigned __int64 unk_00;
    UnkType_1097c340_Base* unk_08;
    int unk_0c;
};

class UnkType_110c0e28_07c340 : public UnkType_110c0e28_07c340_Base
{
public:
    UnkType_110c0e28_07c340(UnkType_1097c340_Base* Owner)
    : UnkType_110c0e28_07c340_Base(Owner)
    {
        unk_00 = (unsigned __int64)(unsigned int)Owner->unk_04 * 0x100 + 0x34;
        unk_0c = 1;
    }

    virtual ~UnkType_110c0e28_07c340();
};

#pragma pack(pop)

class UnkType_1097c340 : public UnkType_1097c340_Base
{
public:
    UnkType_1097c340();
    virtual ~UnkType_1097c340();

private:
    UnkType_110c0e28_07c340* unk_e8;
};

// UnkType_1097c340::UnkType_1097c340
UnkType_1097c340::UnkType_1097c340()
{
    unk_e8 = new(L"FStaticVolumeTexture") UnkType_110c0e28_07c340(this);
}
