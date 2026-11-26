// campaign_leaf_4a73f0.cpp -- constructor at VA 0x10da73f0: runs the empty base constructor at
// VA 0x10d9d560 and clears the dword at offset 0. All names are invented.

#include "campaign_leaf_49d560_base.h"

class UnkType_10da73f0 : public UnkType_10d9d560
{
public:
    UnkType_10da73f0();

private:
    int unk_00;
};

// UnkType_10da73f0::UnkType_10da73f0
UnkType_10da73f0::UnkType_10da73f0()
{
    unk_00 = 0;
}
