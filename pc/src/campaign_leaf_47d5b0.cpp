// campaign_leaf_47d5b0.cpp -- constructor at VA 0x10d7d5b0: runs the empty base constructor at
// VA 0x10d9d560, then constructs the members at offsets 0 and 4 with the constructor at
// VA 0x10d7ce90. All names are invented.

#include "campaign_leaf_49d560_base.h"

class UnkType_10d7ce90
{
public:
    UnkType_10d7ce90();

private:
    int unk_00;
};

class UnkType_10d7d5b0 : public UnkType_10d9d560
{
public:
    UnkType_10d7d5b0();

private:
    UnkType_10d7ce90 unk_00;
    UnkType_10d7ce90 unk_04;
};

// UnkType_10d7d5b0::UnkType_10d7d5b0
UnkType_10d7d5b0::UnkType_10d7d5b0()
{
}
