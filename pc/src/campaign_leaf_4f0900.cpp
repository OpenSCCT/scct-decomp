// campaign_leaf_4f0900.cpp -- function at VA 0x10df0900: sets the setting at VA 0x111cdd68 to its
// argument, after the one-time setup at VA 0x10df08c0 has stored the defaults (10 at 0x111cdd64,
// 2000 at 0x111cdd60, 10 at 0x111cdd68); refuses zero through the function at VA 0x10d977f0 with
// code 0xe0000012 and returns false. The function names are invented; the codes, the defaults and
// the addresses are the binary's.

#include "campaign_global_111cdd60.h"
#include "campaign_global_111cdd64.h"
#include "campaign_global_111cdd68.h"

void Unk_10d977f0(int Arg0, int Arg1, unsigned int Code, int Arg3);

void Unk_10df08c0();
bool Unk_10df0900(unsigned int Value);

inline void Unk_10df08c0_SetB(unsigned int Value)
{
    Unk_10df08c0();
    GUnk_111cdd64 = Value;
}

inline void Unk_10df08c0_SetA(unsigned int Value)
{
    Unk_10df08c0();
    GUnk_111cdd60 = Value;
}

// Unk_10df08c0
void Unk_10df08c0()
{
    static bool Done = false;
    if ( !Done )
    {
        Done = true;
        Unk_10df08c0_SetB(10);
        Unk_10df08c0_SetA(2000);
        Unk_10df0900(10);
    }
}

// Unk_10df0900
bool Unk_10df0900(unsigned int Value)
{
    Unk_10df08c0();
    if ( !( Value > 0 ) )
    {
        Unk_10d977f0(0, 0, 0xe0000012, 0);
        return false;
    }
    GUnk_111cdd68 = Value;
    return true;
}
