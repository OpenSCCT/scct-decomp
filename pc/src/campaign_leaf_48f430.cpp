// campaign_leaf_48f430.cpp -- free function at VA 0x10d8f430: calls the free function at
// VA 0x10d86a90 with the global at VA 0x1131a698 and its argument, and returns the result. All
// names are invented.

#include "campaign_global_1131a698.h"

int Unk_10d86a90(int Global, int Value);

// Unk_10d8f430
int Unk_10d8f430(int Value)
{
    return Unk_10d86a90(GUnk_1131a698, Value);
}
