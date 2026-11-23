// campaign_leaf_009ca0.cpp -- method at VA 0x10909ca0: closes the handle at 0x3c with CloseHandle
// when it is set and clears it; returns whether the value at 0x34 is 0. The class, member and
// method names are invented; the offsets are the binary's.

#include "campaign_import_CloseHandle.h"

class UnkType_10909ca0
{
public:
    int Unk_10909ca0();

private:
    unsigned char unk_00[0x34];
    int unk_34;
    int unk_38;
    HANDLE unk_3c;
};

// UnkType_10909ca0::Unk_10909ca0
int UnkType_10909ca0::Unk_10909ca0()
{
    if ( unk_3c )
    {
        CloseHandle(unk_3c);
    }
    unk_3c = 0;
    return unk_34 == 0;
}
