// campaign_leaf_215860.cpp -- a member function at VA 0x10b15860 returning a vector of three floats:
// it fills the global at VA 0x111f69ec on first use (with what the free function at VA 0x109b51e0
// returns for L"Engine", then calls the free function at VA 0x109b0810), and returns the vector at
// 0xf4 of the object the pointer at 0x2b4 refers to when the chain starting at the pointer at 0x24
// (each link's next at 0x28) reaches that global (or the global is null) and that object exists;
// otherwise it returns its own vector at 0xf4. The class, method, member and global names are
// invented; the offsets, addresses and string are the binary's.

#include "campaign_global_111f69ec.h"

class UnkType_10b15860_Link
{
public:
    unsigned char unk_00[0x28];
    UnkType_10b15860_Link* unk_28;
};

UnkType_10b15860_Link* __cdecl Unk_109b51e0(const unsigned short* Package);
void __cdecl Unk_109b0810();

class UnkType_10b15860_Vector
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10b15860
{
public:
    // guess: whether the chain at 0x24 reaches the given link (an inline helper; name invented)
    int ChainReaches(void* Target)
    {
        for ( UnkType_10b15860_Link* Link = unk_024; Link; Link = Link->unk_28 )
        {
            if ( Link == Target )
            {
                return 1;
            }
        }
        return Target == 0;
    }

    UnkType_10b15860_Vector Unk_10b15860();

private:
    unsigned char unk_000[0x24];
    UnkType_10b15860_Link* unk_024;
    unsigned char unk_028[0xf4 - 0x28];
    UnkType_10b15860_Vector unk_0f4;
    unsigned char unk_100[0x2b4 - 0x100];
    UnkType_10b15860* unk_2b4;
};

// UnkType_10b15860::Unk_10b15860
UnkType_10b15860_Vector UnkType_10b15860::Unk_10b15860()
{
    if ( !GUnk_111f69ec )
    {
        GUnk_111f69ec = Unk_109b51e0(L"Engine");
        Unk_109b0810();
    }
    return ChainReaches(GUnk_111f69ec) && unk_2b4 ? unk_2b4->unk_0f4 : unk_0f4;
}
