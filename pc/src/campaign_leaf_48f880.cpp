// campaign_leaf_48f880.cpp -- constructor at VA 0x10d8f880. After the base constructor at
// 0x10da2720 it constructs its parts at 0x44 (0x10daafa0), 0x68 (an empty base at 0x10d9d560 and
// two words at 0x10d7ce90), 0x78 (0x10da7450) and 0x80 (0x10dab3e0), then sets its key at 0x2c
// from the global at 0x1131a698 (0x10d9d3c0). The class and member names are invented.

#include "campaign_global_1131a698.h"

class UnkType_10d8f880_Base
{
public:
    UnkType_10d8f880_Base();
    virtual ~UnkType_10d8f880_Base();

private:
    unsigned char unk_4[0x28];
};

struct UnkType_10d8f880_Key
{
    void Unk_10d9d3c0(int Value);

    int unk_0;
};

class UnkType_10d8f880_Part44
{
public:
    UnkType_10d8f880_Part44();

private:
    unsigned char unk_0[0x24];
};

class UnkType_10d8f880_PartBase
{
public:
    UnkType_10d8f880_PartBase();
};

class UnkType_10d8f880_Word
{
public:
    UnkType_10d8f880_Word();

private:
    int unk_0;
};

class UnkType_10d8f880_Part68 : public UnkType_10d8f880_PartBase
{
private:
    UnkType_10d8f880_Word unk_0;
    UnkType_10d8f880_Word unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10d8f880_Part78
{
public:
    UnkType_10d8f880_Part78();

private:
    unsigned char unk_0[0x8];
};

class UnkType_10d8f880_Part80
{
public:
    UnkType_10d8f880_Part80();

private:
    int unk_0;
};

class UnkType_10d8f880 : public UnkType_10d8f880_Base
{
public:
    UnkType_10d8f880();

private:
    UnkType_10d8f880_Key unk_2c;
    unsigned char unk_30[0x14];
    UnkType_10d8f880_Part44 unk_44;
    UnkType_10d8f880_Part68 unk_68;
    UnkType_10d8f880_Part78 unk_78;
    UnkType_10d8f880_Part80 unk_80;
};

// UnkType_10d8f880::UnkType_10d8f880
UnkType_10d8f880::UnkType_10d8f880()
{
    unk_2c.Unk_10d9d3c0(GUnk_1131a698);
}
