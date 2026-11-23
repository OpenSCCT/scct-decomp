// campaign_leaf_747230.cpp -- one function at file offset 0x747230, preferred VA 0x11047230. It
// calls the function at VA 0x11046a10 and then clears the global at VA 0x1132bc5c. The function
// names are invented; the offset and the addresses are the binary's.

#include "campaign_global_1132bc5c.h"

void Unk_11046a10();

// Unk_11047230
void Unk_11047230()
{
    Unk_11046a10();
    GUnk_1132bc5c = 0;
}
