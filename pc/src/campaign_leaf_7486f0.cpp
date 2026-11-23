// campaign_leaf_7486f0.cpp -- one function at file offset 0x7486f0, preferred VA 0x110486f0. It
// releases the pointers at VA 0x1132c7b0, 0x1132c748, 0x1132c730, 0x1132c740 and 0x1132c738 that
// are set through the stdcall function at VA 0x1103c870, clears the first of them and the word at
// VA 0x1132c7ac. The function name is invented; the addresses are the binary's.

#include "campaign_global_1132c730.h"
#include "campaign_global_1132c738.h"
#include "campaign_global_1132c740.h"
#include "campaign_global_1132c748.h"
#include "campaign_global_1132c7ac.h"
#include "campaign_global_1132c7b0.h"

void __stdcall Unk_1103c870(void* Pointer);

// Unk_110486f0
void Unk_110486f0()
{
    if ( GUnk_1132c7b0 != 0 )
    {
        Unk_1103c870(GUnk_1132c7b0);
    }
    GUnk_1132c7b0 = 0;
    if ( GUnk_1132c748 != 0 )
    {
        Unk_1103c870(GUnk_1132c748);
    }
    if ( GUnk_1132c730 != 0 )
    {
        Unk_1103c870(GUnk_1132c730);
    }
    if ( GUnk_1132c740 != 0 )
    {
        Unk_1103c870(GUnk_1132c740);
    }
    if ( GUnk_1132c738 != 0 )
    {
        Unk_1103c870(GUnk_1132c738);
    }
    GUnk_1132c7ac = 0;
}
