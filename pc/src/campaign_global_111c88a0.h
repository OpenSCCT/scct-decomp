// campaign_global_111c88a0.h -- the global at VA 0x111c88a0, a pointer to an allocator object. Name
// and type invented from its uses: slot 0 takes a byte count and a tag string and returns memory,
// slot 2 takes a pointer and frees it.
#ifndef CAMPAIGN_GLOBAL_111C88A0_H
#define CAMPAIGN_GLOBAL_111C88A0_H

class UnkType_111c88a0
{
public:
    virtual void* Malloc(unsigned long Count, const unsigned short* Tag);
    virtual void* Realloc(void* Original, unsigned long Count, const unsigned short* Tag);
    virtual void Free(void* Original);
};

extern UnkType_111c88a0* GUnk_111c88a0;

#endif
