// campaign_global_1131b43c.h -- the global at VA 0x1131b43c: a pointer to a reference-counted object
// (count at 0x06, deleted through its virtual destructor when the count drops to zero). Name and
// type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_1131B43C_H
#define CAMPAIGN_GLOBAL_1131B43C_H

class UnkType_1131b43c
{
public:
    virtual ~UnkType_1131b43c();

    void Release()
    {
        if ( --unk_06 == 0 )
        {
            delete this;
        }
    }

    unsigned short unk_04;
    unsigned short unk_06;
};

extern UnkType_1131b43c* GUnk_1131b43c;

#endif
