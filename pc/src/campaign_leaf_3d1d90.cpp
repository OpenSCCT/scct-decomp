// campaign_leaf_3d1d90.cpp -- one function at file offset 0x3d1d90, preferred VA 0x10cd1d90. When
// record Index of the table at 0x11252f34 has a file and a cursor and is not blocked, it reads
// Size bytes from the file to the cursor with ReadFile, advances the cursor by the bytes read on
// success, sets the record's end flag when fewer than Size were read, and returns the ReadFile
// result; otherwise it returns 0. The function, local and parameter names are invented; the
// import is named by the retail import table, and the offsets and the bytes are the binary's.

#include "campaign_global_11252f34.h"
#include "campaign_import_ReadFile.h"

// Unk_10cd1d90
int __stdcall Unk_10cd1d90(int Index, unsigned long Size)
{
    unsigned long Read;
    int Result;

    if ( GUnk_11252f34[Index].unk_4 == 0 || GUnk_11252f34[Index].unk_0 == 0
        || GUnk_11252f34[Index].unk_24 != 0 )
    {
        return 0;
    }
    Read = 0;
    Result = ReadFile(GUnk_11252f34[Index].unk_4, GUnk_11252f34[Index].unk_0, Size, &Read, 0);
    if ( Result )
    {
        GUnk_11252f34[Index].unk_0 += Read;
    }
    if ( Read != Size )
    {
        GUnk_11252f34[Index].unk_20 = 1;
    }
    return Result;
}
