// campaign_leaf_5e8380.cpp -- free function at VA 0x10ee8380: deletes the object the global at
// VA 0x1131fb20 points to through its virtual destructor and clears the global. All names are
// invented.

#include "campaign_global_1131fb20.h"

// Unk_10ee8380
void Unk_10ee8380()
{
    delete GUnk_1131fb20;
    GUnk_1131fb20 = 0;
}
