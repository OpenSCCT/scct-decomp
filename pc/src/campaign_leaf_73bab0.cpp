// campaign_leaf_73bab0.cpp -- one function at file offset 0x73bab0, preferred VA 0x1103bab0. A
// constructor with the same body as the one at 0x73ba90: it runs the empty base's constructor at
// VA 0x10d9d560, then the constructor at VA 0x1103b1d0 on the 0x60-byte members at 0x0 and 0x60.
// The class names are invented; the offsets and the addresses are the binary's.

#include "campaign_leaf_49d560_base.h"

class UnkType_1103b1d0
{
public:
    UnkType_1103b1d0();

    unsigned char unk_0[0x60];
};

class UnkType_1103bab0 : public UnkType_10d9d560
{
public:
    UnkType_1103bab0();

    UnkType_1103b1d0 unk_0;
    UnkType_1103b1d0 unk_60;
};

// UnkType_1103bab0::UnkType_1103bab0
UnkType_1103bab0::UnkType_1103bab0()
{
}
