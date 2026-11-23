// campaign_leaf_1db350.cpp -- free function at VA 0x10adb350: passes the result of the free
// function at VA 0x10b12dd0 to the free function at VA 0x10d38eb0, then sets the flag at VA
// 0x1120b700. The function and global names are invented; the addresses are the binary's.

#include "campaign_global_1120b700.h"

int Unk_10b12dd0();
void Unk_10d38eb0(int Value);

// Unk_10adb350
void Unk_10adb350()
{
    Unk_10d38eb0(Unk_10b12dd0());
    GUnk_1120b700 = true;
}
