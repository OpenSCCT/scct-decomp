// campaign_global_111f55c4.h -- the global at VA 0x111f55c4: a pointer to a 0x68-byte object with a
// virtual destructor in slot 0, the constructor at VA 0x10aa3cf0 and the method at VA 0x10aa3d60.
// Names and types invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111F55C4_H
#define CAMPAIGN_GLOBAL_111F55C4_H

class UnkType_111f55c4
{
public:
    UnkType_111f55c4();
    virtual ~UnkType_111f55c4();
    void Unk_10aa3d60(int Value, int Flag);

private:
    unsigned char unk_04[0x64];
};

extern UnkType_111f55c4* GUnk_111f55c4;

#endif
