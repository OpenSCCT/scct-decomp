// campaign_leaf_511a10.cpp -- one function at file offset 0x511a10, preferred VA 0x10e11a10.
// The constructor runs the base constructor at 0x10e119f0 and copies the global at 0x111cf3fc into
// the int at offset 4. The class, member and global names are invented; the offset and the bytes
// are the binary's.

#include "campaign_global_111cf3fc.h"

class UnkType_10e11a10_Base
{
public:
    UnkType_10e11a10_Base();
};

class UnkType_10e11a10 : public UnkType_10e11a10_Base
{
public:
    int unk_0;
    int unk_4;

    UnkType_10e11a10();
};

// UnkType_10e11a10::UnkType_10e11a10
UnkType_10e11a10::UnkType_10e11a10()
{
    unk_4 = GUnk_111cf3fc;
}
