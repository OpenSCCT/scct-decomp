// campaign_global_1131b3d8.h -- the global at VA 0x1131b3d8. A pointer to the memory allocator:
// the second virtual method frees a block, the fifth allocates a block of a size with a tag and
// the sixth frees a block given its size and tag. The third method's signature is not recovered
// (no call through it was found); the fourth takes a pointer. The names are invented.
#ifndef CAMPAIGN_GLOBAL_1131B3D8_H
#define CAMPAIGN_GLOBAL_1131B3D8_H

class UnkType_1131b3d8
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Pointer);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(void* Pointer);
    virtual void* VirtualSlot4(int Size, int Tag);
    virtual void VirtualSlot5(void* Pointer, int Size, int Tag);
};

extern UnkType_1131b3d8* GUnk_1131b3d8;

#endif
