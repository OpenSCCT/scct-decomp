// campaign_leaf_1c83f0.cpp -- thiscall method at VA 0x10ac83f0. It passes its argument to the base
// class's method at VA 0x10cd9030; then, when the argument's words at 0x18 and 0x1c are both zero,
// it creates the object the global at VA 0x1120a9bc points to if there is none yet (0x64 bytes from
// the allocator at VA 0x111c88a0, tag "USMStreamer", constructor at VA 0x109c4600) and calls its
// slot 2 with the argument and two zeros. The class, method and member names are invented; the tag
// is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_1120a9bc.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

struct UnkType_10ac83f0_Object
{
    char unk_00[0x18];
    int unk_18;
    int unk_1c;
};

class UnkType_10ac83f0_Base
{
public:
    void Unk_10cd9030(UnkType_10ac83f0_Object* Object);
};

class UnkType_10ac83f0 : public UnkType_10ac83f0_Base
{
public:
    void Unk_10ac83f0(UnkType_10ac83f0_Object* Object);
};

// UnkType_10ac83f0::Unk_10ac83f0
void UnkType_10ac83f0::Unk_10ac83f0(UnkType_10ac83f0_Object* Object)
{
    UnkType_10ac83f0_Base::Unk_10cd9030(Object);
    if ( Object->unk_18 == 0 && Object->unk_1c == 0 )
    {
        if ( GUnk_1120a9bc == 0 )
        {
            GUnk_1120a9bc = new(L"USMStreamer") UnkType_1120a9bc;
        }
        GUnk_1120a9bc->VirtualSlot2(Object, 0, 0);
    }
}
