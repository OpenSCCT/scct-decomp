// campaign_leaf_6abf60.cpp -- stdcall function at VA 0x10fabf60 taking an unused pointer and a size:
// allocates the size plus 16 bytes with the cdecl function at VA 0x10f32558, rounds the block up to
// the next 16-byte boundary past its start, stores the distance in the byte before it and returns
// the rounded address, or null when the allocation fails. The function names are invented; the
// addresses are the binary's.

void* __cdecl Unk_10f32558(unsigned int Size);

// Unk_10fabf60
void* __stdcall Unk_10fabf60(void* Info, unsigned int Size)
{
    unsigned char* Block = (unsigned char*)Unk_10f32558(Size + 16);
    unsigned char* Aligned;

    if ( Block == 0 )
    {
        return 0;
    }
    Aligned = (unsigned char*)( ( (unsigned int)Block + 16 ) & ~15 );
    Aligned[-1] = (unsigned char)( Aligned - Block );
    return Aligned;
}
