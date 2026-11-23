// campaign_leaf_1e73e0.cpp -- method at VA 0x10ae73e0: stores Value at the global at VA 0x1122377c
// and, for Ratio in 0..1, stores at the global at VA 0x1122378c 0.4 plus 0.35 times Ratio above
// one half, and Ratio over 0.55 times 0.6 otherwise. It does not read its this pointer. The
// class, method and parameter names are invented; the constants and addresses are the binary's.

#include "campaign_global_1122377c.h"
#include "campaign_global_1122378c.h"

class UnkType_10ae73e0
{
public:
    void Unk_10ae73e0(int Value, float Ratio);
};

// UnkType_10ae73e0::Unk_10ae73e0
void UnkType_10ae73e0::Unk_10ae73e0(int Value, float Ratio)
{
    GUnk_1122377c = Value;
    if ( Ratio >= 0.0f && Ratio <= 1.0f )
    {
        if ( Ratio > 0.5f )
        {
            GUnk_1122378c = Ratio * 0.35f + 0.4f;
        }
        else
        {
            float Scaled = Ratio / 0.55f;

            GUnk_1122378c = Scaled * 0.6f;
        }
    }
}
