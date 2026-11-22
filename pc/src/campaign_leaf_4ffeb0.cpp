// campaign_leaf_4ffeb0.cpp -- one function at file offset 0x4ffeb0, preferred VA 0x10dffeb0. It
// fills Count bytes at Dest with Value, through the compiler's inline memset. It has no this
// pointer. The function and parameter names are invented; the bytes are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

// Unk_10dffeb0
void Unk_10dffeb0(void* Dest, int Value, unsigned int Count)
{
    memset(Dest, Value, Count);
}
