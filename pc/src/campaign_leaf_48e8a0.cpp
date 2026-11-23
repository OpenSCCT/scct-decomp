// campaign_leaf_48e8a0.cpp -- function at VA 0x10d8e8a0. While the flag at 0x111ca734 is clear it
// only passes its argument to the function at 0x10d8e7e0. Otherwise it saves the value returned by
// 0x10d98f30, and for every index from 0 to the count returned by 0x10d98d50 that 0x10d98e80
// accepts, selects the index (0x10d98ef0) and calls 0x10d8e7e0 with its argument; it then selects
// the saved value again. The function and parameter names are invented.

#include "campaign_global_111ca734.h"

void Unk_10d8e7e0(int Value);
unsigned int Unk_10d98f30();
unsigned int Unk_10d98d50();
bool Unk_10d98e80(unsigned int Index);
void Unk_10d98ef0(unsigned int Index);

// Unk_10d8e8a0
void Unk_10d8e8a0(int Value)
{
    unsigned int Saved;
    unsigned int Count;
    unsigned int Index;

    if ( !GUnk_111ca734 )
    {
        Unk_10d8e7e0(Value);
        return;
    }
    Saved = Unk_10d98f30();
    Count = Unk_10d98d50();
    for ( Index = 0; Index <= Count; Index++ )
    {
        if ( Unk_10d98e80(Index) )
        {
            Unk_10d98ef0(Index);
            Unk_10d8e7e0(Value);
        }
    }
    Unk_10d98ef0(Saved);
}
