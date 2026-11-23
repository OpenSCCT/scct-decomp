// campaign_leaf_73e600.cpp -- one function at file offset 0x73e600, preferred VA 0x1103e600. It
// reports an error through the stdcall function at VA 0x1103c7d0 and returns 0 when the flag at
// VA 0x1132b970 is clear. Otherwise it returns 0 when the function at VA 0x1103dab0 rejects its
// arguments with 0; when the flag at VA 0x1132ba68 is set and that function rejects them with 1
// it passes them and 0 to the function at VA 0x1103df30 and returns 0; it returns 1 otherwise.
// The function name is invented; the addresses are the binary's.

#include "campaign_global_1132b970.h"
#include "campaign_global_1132ba68.h"

void __stdcall Unk_1103c7d0(int Level, const char* Message);
int Unk_1103dab0(int First, int Second, int Mode);
void Unk_1103df30(int First, int Second, int Mode);

// Unk_1103e600
int Unk_1103e600(int First, int Second)
{
    if ( GUnk_1132b970 == 0 )
    {
        Unk_1103c7d0(8, "ERROR: Project has not been initialized yet.");
        return 0;
    }
    if ( Unk_1103dab0(First, Second, 0) == 0 )
    {
        return 0;
    }
    if ( GUnk_1132ba68 != 0 && Unk_1103dab0(First, Second, 1) == 0 )
    {
        Unk_1103df30(First, Second, 0);
        return 0;
    }
    return 1;
}
