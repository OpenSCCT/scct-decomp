// campaign_leaf_338450.cpp -- a free function at VA 0x10c38450 that deletes the object the global
// pointer at VA 0x1122f8a8 refers to, through its virtual destructor, and clears the pointer. The
// class, function and global names are invented; the address is the binary's.

#include "campaign_global_1122f8a8.h"

// Unk_10c38450
void Unk_10c38450()
{
    delete GUnk_1122f8a8;
    GUnk_1122f8a8 = 0;
}
