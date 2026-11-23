// campaign_leaf_4fde80.cpp -- function at VA 0x10dfde80: when the flag at VA 0x1131b420 is set,
// calls the function at VA 0x10dfdda0, releases and clears the objects at VA 0x1131b43c, 0x1131b424
// and 0x1131b438, calls the function at VA 0x10dfbc90 with null and clears the flag; returns zero.
// The function names are invented; the addresses are the binary's.

#include "campaign_global_1131b420.h"
#include "campaign_global_1131b424.h"
#include "campaign_global_1131b438.h"
#include "campaign_global_1131b43c.h"

void Unk_10dfdda0();
void Unk_10dfbc90(void* Arg);

template<class T> inline void Unk_10dfde80_Release(T*& Object)
{
    if ( Object != 0 )
    {
        Object->Release();
    }
    Object = 0;
}

// Unk_10dfde80
int Unk_10dfde80()
{
    if ( GUnk_1131b420 == true )
    {
        Unk_10dfdda0();
        Unk_10dfde80_Release(GUnk_1131b43c);
        Unk_10dfde80_Release(GUnk_1131b424);
        Unk_10dfde80_Release(GUnk_1131b438);
        Unk_10dfbc90(0);
        GUnk_1131b420 = false;
    }
    return 0;
}
