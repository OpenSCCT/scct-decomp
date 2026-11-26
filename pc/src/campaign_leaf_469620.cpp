#include "campaign_global_1131a5b4.h"

// campaign_leaf_469620.cpp -- free function at VA 0x10d69620: calls the stdcall function at
// VA 0x1103c5d0 with the address of the global at VA 0x1131a5b4, its argument and 0x2c, and
// returns its result. All names are invented.

int __stdcall Unk_1103c5d0(void* Target, int Value, int Size);

// Unk_10d69620
int Unk_10d69620(int Value)
{
    return Unk_1103c5d0(&GUnk_1131a5b4, Value, 0x2c);
}
