// campaign_global_1120a9c4.h -- the global at VA 0x1120a9c4, a pointer to an object created on
// first use (0x90 bytes, allocation tag "mostCharacterManager"): a base part built by the
// constructor at VA 0x10b11d10, then a byte at 0x84 and words at 0x88 and 0x8c cleared. Name and
// type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_1120A9C4_H
#define CAMPAIGN_GLOBAL_1120A9C4_H

class UnkType_1120a9c4_Base
{
public:
    UnkType_1120a9c4_Base();

private:
    char unk_00[0x84];
};

class UnkType_1120a9c4 : public UnkType_1120a9c4_Base
{
public:
    // UnkType_1120a9c4::UnkType_1120a9c4
    UnkType_1120a9c4() : unk_84(false), unk_88(0), unk_8c(0) {}

private:
    bool unk_84;
    int unk_88;
    int unk_8c;
};

extern UnkType_1120a9c4* GUnk_1120a9c4;

#endif
