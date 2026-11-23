// campaign_leaf_482420.cpp -- function at VA 0x10d82420. It builds a local reference from the key
// at 0x1131b1a0 (constructor at 0x10d8ef70, destructor at 0x10d8edb0) and, when the reference is
// valid (0x10d801e0) and the method at 0x10d844e0 of the referenced object returns true, calls
// that object's method at 0x10d82230. The class and function names are invented.

#include "campaign_global_1131b1a0.h"

class UnkType_10d82420_Object
{
public:
    bool Unk_10d844e0();
    void Unk_10d82230();
};

class UnkType_10d82420_Ref
{
public:
    UnkType_10d82420_Ref(UnkType_1131b1a0 Key);
    ~UnkType_10d82420_Ref();
    bool Unk_10d801e0();

    UnkType_10d82420_Object* operator->()
    {
        return Unk_10d801e0() ? unk_0 : 0;
    }

private:
    UnkType_10d82420_Object* unk_0;
    int unk_4;
    int unk_8;
};

// Unk_10d82420
void Unk_10d82420()
{
    UnkType_10d82420_Ref Ref(GUnk_1131b1a0);

    if ( Ref.Unk_10d801e0() && Ref->Unk_10d844e0() )
    {
        Ref->Unk_10d82230();
    }
}
