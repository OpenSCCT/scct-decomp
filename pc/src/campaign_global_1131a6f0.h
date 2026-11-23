// campaign_global_1131a6f0.h -- the global at VA 0x1131a6f0. A table whose method at 0x10d97620
// returns the word stored for a key, keyed by the value of 0x10dbfa10. Name and type invented
// from its uses.
#ifndef CAMPAIGN_GLOBAL_1131A6F0_H
#define CAMPAIGN_GLOBAL_1131A6F0_H
class UnkType_1131a6f0
{
public:
    unsigned int& Unk_10d97620(const unsigned int& Key);

private:
    int unk_0;
    int unk_4;
    int unk_8;
};

extern UnkType_1131a6f0 GUnk_1131a6f0;
#endif
