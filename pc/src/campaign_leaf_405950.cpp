// campaign_leaf_405950.cpp -- thiscall at VA 0x10d05950: calls the stdcall function pointer at
// VA 0x110b7504, then the one at VA 0x110b7524 with the dword at offset 4, 0 and 0. All names are
// invented.

#include "campaign_global_110b7504.h"
#include "campaign_global_110b7524.h"

class UnkType_10d05950
{
public:
    void Unk_10d05950();

private:
    int unk_00;
    int unk_04;
};

// UnkType_10d05950::Unk_10d05950
void UnkType_10d05950::Unk_10d05950()
{
    GUnk_110b7504();
    GUnk_110b7524(unk_04, 0, 0);
}
