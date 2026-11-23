// campaign_leaf_1da9c0.cpp -- free function at VA 0x10ada9c0: returns whether the objects the
// globals at VA 0x1120b6b8 and 0x1120b6b4 point to differ in their integer at 0x48, their floats
// at 0x4c-0x58, their byte at 0x64 or bit 0 of 0x68. The function name is invented; the offsets
// and addresses are the binary's.

#include "campaign_global_1120b6b8.h"

// Unk_10ada9c0
int Unk_10ada9c0()
{
    return GUnk_1120b6b8->unk_48 != GUnk_1120b6b4->unk_48
        || GUnk_1120b6b8->unk_4c != GUnk_1120b6b4->unk_4c
        || GUnk_1120b6b8->unk_50 != GUnk_1120b6b4->unk_50
        || GUnk_1120b6b8->unk_54 != GUnk_1120b6b4->unk_54
        || GUnk_1120b6b8->unk_58 != GUnk_1120b6b4->unk_58
        || GUnk_1120b6b8->unk_64 != GUnk_1120b6b4->unk_64
        || GUnk_1120b6b8->unk_68_0 != GUnk_1120b6b4->unk_68_0;
}
