// campaign_global_111f8ae8.h -- the global at VA 0x111f8ae8, a pointer to an object filled in on
// first use (from L"Engine" by the function at VA 0x10a031a0). Each such object links to another
// of its kind through its pointer at 0x28; code walks that chain from an object's pointer at 0x24
// looking for this one. Name and type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111F8AE8_H
#define CAMPAIGN_GLOBAL_111F8AE8_H

class UnkType_111f8ae8
{
public:
    unsigned char unk_00[0x28];
    UnkType_111f8ae8* unk_28;
};

extern UnkType_111f8ae8* GUnk_111f8ae8;

#endif
