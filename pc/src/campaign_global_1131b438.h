// campaign_global_1131b438.h -- the global at VA 0x1131b438: a pointer to a reference-counted object
// (count at 0x06, deleted through its virtual destructor when the count drops to zero). Name and
// type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_1131B438_H
#define CAMPAIGN_GLOBAL_1131B438_H

class UnkType_1131b438
{
public:
    virtual ~UnkType_1131b438();

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

extern UnkType_1131b438* GUnk_1131b438;

#endif
