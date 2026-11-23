// campaign_leaf_0742f0.cpp -- destructor at VA 0x109742f0: frees the data at 0xcc through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to and clears it, then runs the base
// destructor at VA 0x10cd8ea0. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109742f0_Base
{
public:
    ~UnkType_109742f0_Base();

private:
    unsigned char unk_00[0xcc];
};

class UnkType_109742f0 : public UnkType_109742f0_Base
{
public:
    ~UnkType_109742f0();

private:
    void* unk_cc;
};

// UnkType_109742f0::~UnkType_109742f0
UnkType_109742f0::~UnkType_109742f0()
{
    GUnk_111c88a0->Free(unk_cc);
    unk_cc = 0;
}
