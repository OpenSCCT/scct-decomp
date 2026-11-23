// campaign_leaf_568530.cpp -- method at VA 0x10e68530: scales the four floats at 0x0-0xc to unit
// length, or to zero when they are all zero. The class, member, method and local names are
// invented.

#include "campaign_crt_sqrt.h"

class UnkType_10e68530
{
public:
    void Unk_10e68530();

private:
    float unk_0;
    float unk_4;
    float unk_8;
    float unk_c;
};

// UnkType_10e68530::Unk_10e68530
void UnkType_10e68530::Unk_10e68530()
{
    float SquareSum = unk_0 * unk_0 + unk_4 * unk_4 + unk_8 * unk_8 + unk_c * unk_c;
    float Scale = SquareSum != 0.0f ? 1.0f / (float)sqrt(SquareSum) : 0.0f;

    unk_0 *= Scale;
    unk_4 *= Scale;
    unk_8 *= Scale;
    unk_c *= Scale;
}
