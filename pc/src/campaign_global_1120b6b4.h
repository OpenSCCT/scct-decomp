// campaign_global_1120b6b4.h -- the global at VA 0x1120b6b4: a pointer to an object whose fields
// 0x48-0x68 are compared field by field with those of the object the global at VA 0x1120b6b8
// points to. Names and types invented from those uses.
#ifndef CAMPAIGN_GLOBAL_1120B6B4_H
#define CAMPAIGN_GLOBAL_1120B6B4_H

class UnkType_1120b6b4
{
public:
    char unk_0[0x48];
    int unk_48;
    float unk_4c;
    float unk_50;
    float unk_54;
    float unk_58;
    char unk_5c[0x64 - 0x5c];
    unsigned char unk_64;
    char unk_65[0x68 - 0x65];
    unsigned int unk_68_0 : 1;
};

extern UnkType_1120b6b4* GUnk_1120b6b4;

#endif
