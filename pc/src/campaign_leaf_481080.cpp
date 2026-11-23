// campaign_leaf_481080.cpp -- function at VA 0x10d81080. It builds a local reference from the key
// at 0x1131b1a0 (constructor at 0x10d8ef70, destructor at 0x10d8edb0) and returns the referenced
// object when the reference is valid (0x10d801e0), else null. The class and function names are
// invented.

#include "campaign_global_1131b1a0.h"

class UnkType_10d81080_Object;

class UnkType_10d81080_Ref
{
public:
    UnkType_10d81080_Ref(UnkType_1131b1a0 Key);
    ~UnkType_10d81080_Ref();
    bool Unk_10d801e0();

    UnkType_10d81080_Object* operator->()
    {
        return Unk_10d801e0() ? unk_0 : 0;
    }

private:
    UnkType_10d81080_Object* unk_0;
    int unk_4;
    int unk_8;
};

// Unk_10d81080
UnkType_10d81080_Object* Unk_10d81080()
{
    UnkType_10d81080_Ref Ref(GUnk_1131b1a0);

    return Ref.operator->();
}
