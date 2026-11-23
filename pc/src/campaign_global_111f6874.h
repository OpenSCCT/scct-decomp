// campaign_global_111f6874.h -- the global at VA 0x111f6874: a pointer to a reference-counted
// object (16-bit count at 0x06) that deletes itself through its virtual destructor (slot 0) when
// released to 0. Names and types invented from its uses.
#ifndef CAMPAIGN_GLOBAL_111F6874_H
#define CAMPAIGN_GLOBAL_111F6874_H

class UnkType_111f6874
{
public:
    virtual ~UnkType_111f6874();

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

extern UnkType_111f6874* GUnk_111f6874;

#endif
