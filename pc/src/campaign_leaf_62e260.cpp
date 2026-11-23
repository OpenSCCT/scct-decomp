// campaign_leaf_62e260.cpp -- free function at VA 0x10f2e260: when the global at VA 0x11321c98 is
// set, calls the method at VA 0x10f2e3d0 on it and returns 0x2220000; otherwise returns
// 0x82225001. guess: the two values are result codes. All names are invented.

#include "campaign_global_11321c98.h"

// Unk_10f2e260
int Unk_10f2e260()
{
    if ( GUnk_11321c98 )
    {
        GUnk_11321c98->Unk_10f2e3d0();
        return 0x2220000;
    }
    return 0x82225001;
}
