// campaign_leaf_2802d0.cpp -- method at VA 0x10b802d0 taking one argument: when the object at 0x184
// is set and its chain of pointers (from 0x24, following 0x28) reaches the object the global at VA
// 0x111f8ae8 holds (filled in first from L"Engine" by the function at VA 0x10a031a0 followed by
// the function at VA 0x109d0630), passes the argument on to the method at VA 0x10ad00c0 of the
// object at 0x15d0 when that is set. The class, member and method names are invented; the
// offsets, the string and the addresses are the binary's.

#include "campaign_global_111f8ae8.h"

UnkType_111f8ae8* Unk_10a031a0(const unsigned short* Package);
void Unk_109d0630();

class UnkType_10b802d0_184
{
public:
    int UnkInheritsFrom(UnkType_111f8ae8* Target)
    {
        for ( UnkType_111f8ae8* Link = unk_24; Link; Link = Link->unk_28 )
        {
            if ( Link == Target )
            {
                return 1;
            }
        }
        return Target == 0;
    }

    unsigned char unk_00[0x24];
    UnkType_111f8ae8* unk_24;
};

class UnkType_10b802d0_15d0
{
public:
    void Unk_10ad00c0(int Value);
};

class UnkType_10b802d0
{
public:
    void Unk_10b802d0(int Value);

    static UnkType_111f8ae8* UnkLazyTarget()
    {
        if ( !GUnk_111f8ae8 )
        {
            GUnk_111f8ae8 = Unk_10a031a0(L"Engine");
            Unk_109d0630();
        }
        return GUnk_111f8ae8;
    }

private:
    unsigned char unk_00[0x184];
    UnkType_10b802d0_184* unk_184;
    unsigned char unk_188[0x15d0 - 0x188];
    UnkType_10b802d0_15d0* unk_15d0;
};

// UnkType_10b802d0::Unk_10b802d0
void UnkType_10b802d0::Unk_10b802d0(int Value)
{
    if ( unk_184 && unk_184->UnkInheritsFrom(UnkLazyTarget()) && unk_15d0 )
    {
        unk_15d0->Unk_10ad00c0(Value);
    }
}
