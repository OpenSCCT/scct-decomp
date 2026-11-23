// campaign_leaf_4b3cb0.cpp -- one function at file offset 0x4b3cb0, preferred VA 0x10db3cb0.
// It deletes the object the global at 0x1131b198 points to, if any, through its destructor at
// 0x10db3b10 and the operator delete at 0x10d87b90 and clears the global. The function and global
// names are invented; the offset and the bytes are the binary's.

#include "campaign_global_1131b198.h"

// Unk_10db3cb0
void Unk_10db3cb0()
{
    if ( GUnk_1131b198 != 0 )
    {
        delete GUnk_1131b198;
        GUnk_1131b198 = 0;
    }
}
