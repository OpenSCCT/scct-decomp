// campaign_leaf_1ef930.cpp -- function at VA 0x10aef930 with no this pointer. Given a stack allocator
// and a count, it takes count words (8-byte aligned) from the allocator, starting a new chunk
// through its method at VA 0x10d01de0 when the current one is full, fills them with zeros and
// returns them. The function name is invented.

#include "campaign_global_1120a99c.h"

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);

// Unk_10aef930
int* Unk_10aef930(UnkType_1120a99c& Mem, int Count)
{
    unsigned char* Result = Mem.PushBytes(Count * sizeof(int), 8);
    memset(Result, 0, Count * sizeof(int));
    return (int*)Result;
}
