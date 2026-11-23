// campaign_leaf_4c3340.cpp -- one function at file offset 0x4c3340, preferred VA 0x10dc3340.
// The constructor runs the base constructor at 0x10d982f0, calls the cdecl function at 0x10d90c50
// and stores the new object in the global at 0x1131b278. The class, function and global names are
// invented; the offset and the bytes are the binary's.

#include "campaign_global_1131b278.h"

class UnkType_10dc3340_Base
{
public:
    UnkType_10dc3340_Base();
};

void Unk_10d90c50();

class UnkType_10dc3340 : public UnkType_10dc3340_Base
{
public:
    UnkType_10dc3340();
};

// UnkType_10dc3340::UnkType_10dc3340
UnkType_10dc3340::UnkType_10dc3340()
{
    Unk_10d90c50();
    GUnk_1131b278 = this;
}
