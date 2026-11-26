#include "campaign_global_1131a5c8.h"

// campaign_leaf_469890.cpp -- thiscall at VA 0x10d69890: calls the stdcall function pointer at
// VA 0x1131a5c8 with the dword at offset 0 and its two arguments. All names are invented.

class UnkType_10d69890
{
public:
    void Unk_10d69890(int First, int Second);

private:
    int unk_00;
};

// UnkType_10d69890::Unk_10d69890
void UnkType_10d69890::Unk_10d69890(int First, int Second)
{
    GUnk_1131a5c8(unk_00, First, Second);
}
