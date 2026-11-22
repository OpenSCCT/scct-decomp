// campaign_leaf_6abf40.cpp -- stdcall function at VA 0x10fabf40 taking three arguments: when the
// second is not null, frees the block it lies in with the C runtime free (VA 0x10f3256a, named in
// pc/evidence/library-functions.tsv); the byte just before the pointer holds its distance from the
// start of the block. The first and third arguments are unused. All other names are invented.

extern "C" void __cdecl free(void* Block);

// Unk_10fabf40
void __stdcall Unk_10fabf40(void* Unused, unsigned char* Pointer, int UnusedSize)
{
    if ( Pointer )
    {
        free(Pointer - Pointer[-1]);
    }
}
