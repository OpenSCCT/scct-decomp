// campaign_leaf_4688b0.cpp -- free function at VA 0x10d688b0: when the global pointer at
// VA 0x1131a5ac is set, calls the method at VA 0x10d6f910 of the object it points to with its
// three arguments. All names are invented.

#include "campaign_global_1131a5ac.h"

// Unk_10d688b0
void Unk_10d688b0(int First, int Second, int Third)
{
    if (GUnk_1131a5ac) {
        GUnk_1131a5ac->Unk_10d6f910(First, Second, Third);
    }
}
