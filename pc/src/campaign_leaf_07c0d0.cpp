// campaign_leaf_07c0d0.cpp -- constructor at VA 0x1097c0d0 of a class whose vtable is at VA
// 0x110c1270: runs the base constructor at VA 0x1097b210, sets the byte at 0x48 to 5, copies the
// width at 0xe8 to 0x54 and 0x5c and the height at 0xec to 0x58 and 0x60, stores at 0x50 and 0x51
// the power of two each of them is (12 when it is none below 12), then stores at 0xf4 a new
// 0x20-byte object (allocated through slot 0 of the allocator the global at VA 0x111c88a0 points
// to, tagged "FAuxRenderTarget") built by the constructor at VA 0x10aa5ff0 from the values at 0x54,
// 0x58 and 0x48, or 0 when the allocation fails. The class, member and function names are invented;
// the offsets, the sizes, the constants, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10aa5ff0_07c0d0
{
public:
    UnkType_10aa5ff0_07c0d0(int Width, int Height, int Format);

private:
    unsigned char unk_00[0x20];
};

class UnkType_1097c0d0_Base
{
public:
    UnkType_1097c0d0_Base();
    virtual ~UnkType_1097c0d0_Base();

protected:
    unsigned char unk_04[0x48 - 0x04];
    unsigned char unk_48;
    unsigned char unk_49[0x50 - 0x49];
    unsigned char unk_50;
    unsigned char unk_51;
    unsigned char unk_52[0x54 - 0x52];
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    unsigned char unk_64[0xe8 - 0x64];
};

inline int Unk_07c0d0_Bits(int Size)
{
    int Power = 1;
    for ( int i = 0; i < 12; i++, Power += Power )
    {
        if ( Size == Power )
        {
            return i;
        }
    }
    return 12;
}

class UnkType_1097c0d0 : public UnkType_1097c0d0_Base
{
public:
    UnkType_1097c0d0();
    virtual ~UnkType_1097c0d0();

private:
    int unk_e8;
    int unk_ec;
    int unk_f0;
    UnkType_10aa5ff0_07c0d0* unk_f4;
};

// UnkType_1097c0d0::UnkType_1097c0d0
UnkType_1097c0d0::UnkType_1097c0d0()
{
    unk_48 = 5;
    unk_54 = unk_e8;
    unk_5c = unk_e8;
    unk_58 = unk_ec;
    unk_60 = unk_ec;
    unk_50 = Unk_07c0d0_Bits(unk_e8);
    unk_51 = Unk_07c0d0_Bits(unk_ec);
    unk_f4 = new(L"FAuxRenderTarget") UnkType_10aa5ff0_07c0d0(unk_54, unk_58, unk_48);
}
