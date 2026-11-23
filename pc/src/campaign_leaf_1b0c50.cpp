// campaign_leaf_1b0c50.cpp -- thiscall method at VA 0x10ab0c50. It passes its argument to the base
// class's method at VA 0x10cd9030; then, when the argument's words at 0x18 and 0x1c are both zero,
// it creates the object the global at VA 0x111fa7f4 points to if there is none yet (0x64 bytes from
// the allocator at VA 0x111c88a0, tag "UTextureStreamer", constructor at VA 0x1097b7f0) and calls
// its slot 2 with the argument and two zeros. The class, method and member names are invented; the
// tag is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111fa7f4.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

struct UnkType_10ab0c50_Object
{
    char unk_00[0x18];
    int unk_18;
    int unk_1c;
};

class UnkType_10ab0c50_Base
{
public:
    void Unk_10cd9030(UnkType_10ab0c50_Object* Object);
};

class UnkType_10ab0c50 : public UnkType_10ab0c50_Base
{
public:
    void Unk_10ab0c50(UnkType_10ab0c50_Object* Object);
};

// UnkType_10ab0c50::Unk_10ab0c50
void UnkType_10ab0c50::Unk_10ab0c50(UnkType_10ab0c50_Object* Object)
{
    UnkType_10ab0c50_Base::Unk_10cd9030(Object);
    if ( Object->unk_18 == 0 && Object->unk_1c == 0 )
    {
        if ( GUnk_111fa7f4 == 0 )
        {
            GUnk_111fa7f4 = new(L"UTextureStreamer") UnkType_111fa7f4;
        }
        GUnk_111fa7f4->VirtualSlot2(Object, 0, 0);
    }
}
