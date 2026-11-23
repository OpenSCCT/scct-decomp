// campaign_leaf_4ab270.cpp -- one function at file offset 0x4ab270, preferred VA 0x10dab270.
// It returns the performance counter frequency, which it reads with QueryPerformanceFrequency into
// the global at 0x1131b17c the first time, setting the flag at 0x1131b184. The function and global
// names are invented; the offset and the bytes are the binary's.

#include "campaign_global_1131b17c.h"
#include "campaign_global_1131b184.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64* Frequency);

// Unk_10dab270
__int64 Unk_10dab270()
{
    if ( !GUnk_1131b184 )
    {
        QueryPerformanceFrequency(&GUnk_1131b17c);
        GUnk_1131b184 = true;
    }
    return GUnk_1131b17c;
}
