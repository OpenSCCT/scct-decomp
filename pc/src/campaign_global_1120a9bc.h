// campaign_global_1120a9bc.h -- the global at VA 0x1120a9bc, a pointer to an object created on
// first use (0x64 bytes, allocation tag "USMStreamer", constructor at VA 0x109c4600). Name and type
// invented from its uses; slot 2 takes an object and two zero words.
#ifndef CAMPAIGN_GLOBAL_1120A9BC_H
#define CAMPAIGN_GLOBAL_1120A9BC_H

class UnkType_1120a9bc
{
public:
    UnkType_1120a9bc();

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(void* Object, int First, int Second);

private:
    char unk_04[0x64 - 0x04];
};

extern UnkType_1120a9bc* GUnk_1120a9bc;

#endif
