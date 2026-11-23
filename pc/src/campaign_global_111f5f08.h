// campaign_global_111f5f08.h -- the global at VA 0x111f5f08, an array of pointers to objects (data at
// 0x00, count at 0x04, capacity at 0x08). Names and types invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111F5F08_H
#define CAMPAIGN_GLOBAL_111F5F08_H

class UnkType_111f5f08_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
};

class UnkType_111f5f08
{
public:
    UnkType_111f5f08_Item** unk_00;
    int unk_04;
    int unk_08;
};

extern UnkType_111f5f08 GUnk_111f5f08;

#endif
