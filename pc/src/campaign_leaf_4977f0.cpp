// campaign_leaf_4977f0.cpp -- function at VA 0x10d977f0. Under the lock at 0x1131a6ec it stores
// the given code in the table at 0x1131a6f0 under the key returned by 0x10dbfa10, and under the
// lock at 0x1131a6d4 the fourth argument in the table at 0x1131a6d8 under the same kind of key.
// The locks are skipped while the flag at 0x1131a67c is set. The first two arguments are not
// read. The function and parameter names are invented.

#include "campaign_global_1131a67c.h"
#include "campaign_global_1131a6d4.h"
#include "campaign_global_1131a6d8.h"
#include "campaign_global_1131a6ec.h"
#include "campaign_global_1131a6f0.h"

unsigned int Unk_10dbfa10();

// Unk_10d977f0
void Unk_10d977f0(int First, int Second, unsigned int Code, int Fourth)
{
    if ( !GUnk_1131a67c )
    {
        GUnk_1131a6ec.Unk_10d8b2f0();
    }
    GUnk_1131a6f0.Unk_10d97620(Unk_10dbfa10()) = Code;
    if ( !GUnk_1131a67c )
    {
        GUnk_1131a6ec.Unk_10d8b300();
    }
    if ( !GUnk_1131a67c )
    {
        GUnk_1131a6d4.Unk_10d8b2f0();
    }
    GUnk_1131a6d8.Unk_10d97620(Unk_10dbfa10()) = Fourth;
    if ( !GUnk_1131a67c )
    {
        GUnk_1131a6d4.Unk_10d8b300();
    }
}
