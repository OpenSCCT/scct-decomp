// campaign_leaf_48e2c0.cpp -- thiscall method at VA 0x10d8e2c0. After a first call of its method
// at 0x10d8de20 it repeats, while holding its lock object at 0x20 (skipped while the flag at
// 0x1131a67c is set): take the next item from 0x10d8d180 and hand it with the address of the
// 64-bit argument to 0x10d8e090, or, with no item, stop once 0x10d8de20 returns false; stop also
// once 0x10d8bef0 returns 0 for the argument. The class, method and parameter names are invented.

#include "campaign_global_1131a678.h"
#include "campaign_global_1131a67c.h"

class UnkType_10d8e2c0
{
public:
    void Unk_10d8e2c0(unsigned __int64 Time);
    bool Unk_10d8de20();
    void* Unk_10d8d180();
    void Unk_10d8e090(void* Item, unsigned __int64* Time);
    int Unk_10d8bef0(unsigned __int64 Time);

private:
    unsigned char unk_0[0x20];
    UnkType_1131a678 unk_20;
};

// UnkType_10d8e2c0::Unk_10d8e2c0
void UnkType_10d8e2c0::Unk_10d8e2c0(unsigned __int64 Time)
{
    bool bMore = true;
    void* Item;
    UnkType_1131a678* Lock;

    Unk_10d8de20();
    Lock = &unk_20;
    do
    {
        if ( !GUnk_1131a67c )
        {
            Lock->Unk_10d8b2f0();
        }
        Item = Unk_10d8d180();
        if ( Item )
        {
            Unk_10d8e090(Item, &Time);
        }
        else if ( !Unk_10d8de20() )
        {
            bMore = false;
        }
        if ( !Unk_10d8bef0(Time) )
        {
            bMore = false;
        }
        if ( !GUnk_1131a67c )
        {
            Lock->Unk_10d8b300();
        }
    }
    while ( bMore );
}
