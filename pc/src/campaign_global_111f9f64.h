// campaign_global_111f9f64.h -- the global at VA 0x111f9f64, a pointer to an object whose bytes
// at 0x28 and 0x29 are read as settings. Name and type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111F9F64_H
#define CAMPAIGN_GLOBAL_111F9F64_H

class UnkType_111f9f64
{
public:
    unsigned char unk_00[0x28];
    unsigned char unk_28;
    unsigned char unk_29;
};

extern UnkType_111f9f64* GUnk_111f9f64;

#endif
