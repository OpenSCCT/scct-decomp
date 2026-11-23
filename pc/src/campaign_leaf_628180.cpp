// campaign_leaf_628180.cpp -- free function at VA 0x10f28180: when the global at VA 0x11321c90 is
// set, deletes the object it points to through its virtual destructor and clears the global. All
// names are invented.

#include "campaign_global_11321c90.h"

// Unk_10f28180
void Unk_10f28180()
{
    if ( GUnk_11321c90 )
    {
        delete GUnk_11321c90;
        GUnk_11321c90 = 0;
    }
}
