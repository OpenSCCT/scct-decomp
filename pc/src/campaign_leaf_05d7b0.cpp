// campaign_leaf_05d7b0.cpp -- free function at VA 0x1095d7b0: if its first argument is not null,
// passes it to the method at VA 0x1095c6d0 of the global object at VA 0x111f5630 and stores its
// second argument in the global at VA 0x111f55ac. The class, function and global names are
// invented; the addresses are the binary's.

#include "campaign_global_111f5630.h"
#include "campaign_global_111f55ac.h"

// Unk_1095d7b0
void Unk_1095d7b0(void* Value, int Arg)
{
    if ( Value )
    {
        GUnk_111f5630.Unk_1095c6d0(Value);
        GUnk_111f55ac = Arg;
    }
}
