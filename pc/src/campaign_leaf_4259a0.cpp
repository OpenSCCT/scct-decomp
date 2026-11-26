// campaign_leaf_4259a0.cpp -- free function at VA 0x10d259a0: deletes the object the global at
// VA 0x11317ab0 points to through its virtual destructor and clears the global. All names are
// invented.

#include "campaign_global_11317ab0.h"

// Unk_10d259a0
void Unk_10d259a0()
{
    delete GUnk_11317ab0;
    GUnk_11317ab0 = 0;
}
