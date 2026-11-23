// campaign_leaf_0a3ad0.cpp -- method at VA 0x109a3ad0: unless the global at VA 0x11232794 is set,
// releases the object at 0x2b4: hands it to the method at VA 0x10e50d80 of the object reached
// through 0x7c, 0x39a8 and 0x28 (when each is set), decrements its 16-bit count at 0x06, deletes
// it through its virtual destructor when the count reaches zero, and clears the pointer. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_11232794.h"

class UnkType_109a3ad0_Resource
{
public:
    virtual ~UnkType_109a3ad0_Resource();

    unsigned short unk_04;
    unsigned short unk_06;
};

class UnkType_109a3ad0_Cache
{
public:
    void Unk_10e50d80(UnkType_109a3ad0_Resource* Resource);
};

class UnkType_109a3ad0_Device
{
public:
    unsigned char unk_00[0x28];
    UnkType_109a3ad0_Cache* unk_28;
};

class UnkType_109a3ad0_Level
{
public:
    unsigned char unk_00[0x39a8];
    UnkType_109a3ad0_Device* unk_39a8;
};

class UnkType_109a3ad0
{
public:
    void Unk_109a3ad0();

private:
    unsigned char unk_00[0x7c];
    UnkType_109a3ad0_Level* unk_7c;
    unsigned char unk_80[0x2b4 - 0x80];
    UnkType_109a3ad0_Resource* unk_2b4;
};

// UnkType_109a3ad0::Unk_109a3ad0
void UnkType_109a3ad0::Unk_109a3ad0()
{
    if ( !GUnk_11232794 )
    {
        UnkType_109a3ad0_Level* Level = unk_7c;
        UnkType_109a3ad0_Resource* Resource = unk_2b4;
        if ( Resource )
        {
            if ( Level && Level->unk_39a8 && Level->unk_39a8->unk_28 )
            {
                Level->unk_39a8->unk_28->Unk_10e50d80(Resource);
            }
            if ( --Resource->unk_06 == 0 )
            {
                delete Resource;
            }
            unk_2b4 = 0;
        }
    }
}
