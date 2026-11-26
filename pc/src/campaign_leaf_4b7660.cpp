#include "campaign_global_1131b1fc.h"

// campaign_leaf_4b7660.cpp -- free function at VA 0x10db7660: calls the free function at
// VA 0x10f331b9 with the address of the global at VA 0x1131b1fc and its argument, and returns
// the result. All names are invented.

int Unk_10f331b9(void* Target, int Value);

// Unk_10db7660
int Unk_10db7660(int Value)
{
    return Unk_10f331b9(&GUnk_1131b1fc, Value);
}
