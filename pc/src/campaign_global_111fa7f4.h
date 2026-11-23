// campaign_global_111fa7f4.h -- the global at VA 0x111fa7f4, a pointer to an object created on
// first use (0x64 bytes, allocation tag "UTextureStreamer", constructor at VA 0x1097b7f0). Name and
// type invented from its uses; slot 2 takes an object and two zero words.
#ifndef CAMPAIGN_GLOBAL_111FA7F4_H
#define CAMPAIGN_GLOBAL_111FA7F4_H

class UnkType_111fa7f4
{
public:
    UnkType_111fa7f4();

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(void* Object, int First, int Second);

private:
    char unk_04[0x64 - 0x04];
};

extern UnkType_111fa7f4* GUnk_111fa7f4;

#endif
