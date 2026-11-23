// campaign_leaf_48ec20.cpp -- thiscall method at VA 0x10d8ec20. It releases the object at 0x00,
// if any, through its method at 0x10d8eb50 when the flag at 0x08 is set or 0x10d86130 otherwise,
// and clears 0x00. Given a new object it stores it at 0x00 and, under the object at 0x1131a678
// (skipped while the flag at 0x1131a67c is set), increments its 16-bit count at 0x04, and also
// the one at 0x06 when the flag at 0x08 is set. The class, method and member names are invented.

#include "campaign_global_1131a678.h"
#include "campaign_global_1131a67c.h"

class UnkType_10d8ec20_Target
{
public:
    void Unk_10d86130();
    void Unk_10d8eb50();

    void IncrementUnk4()
    {
        if ( !GUnk_1131a67c )
        {
            GUnk_1131a678.Unk_10d8b2f0();
        }
        unk_4++;
        if ( !GUnk_1131a67c )
        {
            GUnk_1131a678.Unk_10d8b300();
        }
    }

    void IncrementUnk4And6()
    {
        if ( !GUnk_1131a67c )
        {
            GUnk_1131a678.Unk_10d8b2f0();
        }
        unk_4++;
        unk_6++;
        if ( !GUnk_1131a67c )
        {
            GUnk_1131a678.Unk_10d8b300();
        }
    }

    int unk_0;
    short unk_4;
    short unk_6;
};

class UnkType_10d8ec20
{
public:
    void Unk_10d8ec20(UnkType_10d8ec20_Target* Target);

private:
    UnkType_10d8ec20_Target* unk_0;
    int unk_4;
    bool unk_8;
};

// UnkType_10d8ec20::Unk_10d8ec20
void UnkType_10d8ec20::Unk_10d8ec20(UnkType_10d8ec20_Target* Target)
{
    if ( unk_0 )
    {
        if ( unk_8 )
        {
            unk_0->Unk_10d8eb50();
        }
        else
        {
            unk_0->Unk_10d86130();
        }
        unk_0 = 0;
    }
    if ( Target )
    {
        unk_0 = Target;
        if ( unk_8 )
        {
            Target->IncrementUnk4And6();
        }
        else
        {
            Target->IncrementUnk4();
        }
    }
}
