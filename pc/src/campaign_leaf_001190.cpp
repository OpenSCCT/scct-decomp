// campaign_leaf_001190.cpp -- free function at VA 0x10901190: when the thread identifier the
// global at VA 0x111f2d18 holds is set, posts message 0x12 to that thread with PostThreadMessageW
// when the global at VA 0x112327f8 is set and PostThreadMessageA otherwise. The function name is
// invented; the constant and the addresses are the binary's.

#include "campaign_global_111f2d18.h"
#include "campaign_global_112327f8.h"
#include "campaign_import_PostThreadMessageA.h"
#include "campaign_import_PostThreadMessageW.h"

// Unk_10901190
void Unk_10901190()
{
    if ( GUnk_111f2d18 )
    {
        if ( GUnk_112327f8 )
        {
            PostThreadMessageW(GUnk_111f2d18, 0x12, 0, 0);
        }
        else
        {
            PostThreadMessageA(GUnk_111f2d18, 0x12, 0, 0);
        }
    }
}
