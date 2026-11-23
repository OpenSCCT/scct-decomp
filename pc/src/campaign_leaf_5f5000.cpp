// campaign_leaf_5f5000.cpp -- free function at VA 0x10ef5000: when the global at VA 0x11321b3c is
// set, deletes the object it points to through its virtual destructor and clears the global. All
// names are invented.

#include "campaign_global_11321b3c.h"

// Unk_10ef5000
void Unk_10ef5000()
{
    if ( GUnk_11321b3c )
    {
        delete GUnk_11321b3c;
        GUnk_11321b3c = 0;
    }
}
