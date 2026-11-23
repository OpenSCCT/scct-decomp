// campaign_leaf_35d740.cpp -- a member function at VA 0x10c5d740 that calls the member at VA
// 0x10be9960 and then, when the global at VA 0x11232794 is not zero, the member at VA 0x10c5d5b0.
// The class, method and global names are invented; the addresses are the binary's.

#include "campaign_global_11232794.h"

class UnkType_10c5d740
{
public:
    void Unk_10be9960();
    void Unk_10c5d5b0();
    void Unk_10c5d740();
};

// UnkType_10c5d740::Unk_10c5d740
void UnkType_10c5d740::Unk_10c5d740()
{
    Unk_10be9960();
    if ( GUnk_11232794 )
    {
        Unk_10c5d5b0();
    }
}
