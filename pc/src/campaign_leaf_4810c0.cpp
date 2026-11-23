// campaign_leaf_4810c0.cpp -- function at VA 0x10d810c0. It builds a local reference from the key
// at 0x1131b1a0 (constructor at 0x10d8ef70, destructor at 0x10d8edb0) and returns 0 when the
// reference is not valid (0x10d801e0), 1 when the method at 0x10d844e0 of the referenced object
// returns true, else 2. The class and function names are invented.

#include "campaign_global_1131b1a0.h"

class UnkType_10d810c0_Object
{
public:
    bool Unk_10d844e0();
};

class UnkType_10d810c0_Ref
{
public:
    UnkType_10d810c0_Ref(UnkType_1131b1a0 Key);
    ~UnkType_10d810c0_Ref();
    bool Unk_10d801e0();

    UnkType_10d810c0_Object* operator->()
    {
        return Unk_10d801e0() ? unk_0 : 0;
    }

private:
    UnkType_10d810c0_Object* unk_0;
    int unk_4;
    int unk_8;
};

// Unk_10d810c0
unsigned char Unk_10d810c0()
{
    UnkType_10d810c0_Ref Ref(GUnk_1131b1a0);

    if ( !Ref.Unk_10d801e0() )
    {
        return 0;
    }
    if ( Ref->Unk_10d844e0() )
    {
        return 1;
    }
    return 2;
}
