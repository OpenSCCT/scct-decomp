// campaign_leaf_55bf90.cpp -- constructor at VA 0x10e5bf90: runs the constructor of the empty base
// class at VA 0x10e6d280, then clears the four members at 0x00-0x0c. The class names are invented;
// the offsets and addresses are the binary's.

#include "campaign_leaf_56d280_base.h"

class UnkType_10e5bf90 : public UnkType_10e6d280
{
public:
    UnkType_10e5bf90();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10e5bf90::UnkType_10e5bf90
UnkType_10e5bf90::UnkType_10e5bf90()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
}
