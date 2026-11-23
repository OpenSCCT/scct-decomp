// campaign_global_111fa7f8.h -- the global at VA 0x111fa7f8, an array of object pointers (data,
// count at VA 0x111fa7fc, capacity at VA 0x111fa800) whose objects have virtual destructors. Name
// and type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111FA7F8_H
#define CAMPAIGN_GLOBAL_111FA7F8_H

class UnkType_111fa7f8_Item
{
public:
    virtual ~UnkType_111fa7f8_Item();
};

class UnkType_111fa7f8
{
public:
    UnkType_111fa7f8_Item** unk_0;
    int unk_4;
    int unk_8;
};

extern UnkType_111fa7f8 GUnk_111fa7f8;

#endif
