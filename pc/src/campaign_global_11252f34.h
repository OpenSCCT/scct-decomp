// campaign_global_11252f34.h -- the global at VA 0x11252f34: a pointer to an array of 0x28-byte
// file records, each with a read cursor at 0x0, a file handle at 0x4, an end flag at 0x20 and a
// word at 0x24 that blocks reading. Names and types invented from their uses.
#ifndef CAMPAIGN_GLOBAL_11252F34_H
#define CAMPAIGN_GLOBAL_11252F34_H

#include "campaign_import_HANDLE.h"

class UnkType_11252f34
{
public:
    unsigned char* unk_0;
    HANDLE unk_4;
    unsigned char unk_8[0x18];
    int unk_20;
    int unk_24;
};

extern UnkType_11252f34* GUnk_11252f34;

#endif
