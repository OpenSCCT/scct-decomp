// campaign_leaf_77c7b0.cpp -- one function at file offset 0x77c7b0, preferred VA 0x1107c7b0. With
// no block it passes the size, or 1 when the size is zero, to the stdcall function at VA
// 0x1103c830; otherwise it passes the block and the size to the stdcall function at VA 0x1103c850
// (both forward to the object at VA 0x111c88a0). It returns the callee's result. The function
// names are invented; the offset and the addresses are the binary's.

void* __stdcall Unk_1103c830(int Size);
void* __stdcall Unk_1103c850(void* Block, int Size);

// Unk_1107c7b0
void* Unk_1107c7b0(void* Block, int Size)
{
    if ( Block == 0 )
    {
        if ( Size == 0 )
        {
            Size = 1;
        }
        return Unk_1103c830(Size);
    }
    return Unk_1103c850(Block, Size);
}
