// campaign_leaf_1c7a70.cpp -- thiscall method at VA 0x10ac7a70. It calls the base class's method
// at VA 0x10cd8ea0; when the object at 0x170 is set it clears the global at VA 0x1120a9b8 if that
// points to the same object, deletes the object (destructor at VA 0x10aaf880, memory freed through
// slot 2 of the allocator at VA 0x111c88a0) and clears the member. It then calls the method at VA
// 0x109b5bc0 with two zeros on every object in the pointer array at 0x28. The class, method and
// member names are invented.

#include "campaign_global_111c88a0.h"
#include "campaign_global_1120a9b8.h"

inline void operator delete(void* Original)
{
    GUnk_111c88a0->Free(Original);
}

class UnkType_10ac7a70_Item
{
public:
    void Unk_109b5bc0(int First, int Second);
};

class UnkType_10ac7a70_Base
{
public:
    void Unk_10cd8ea0();
};

class UnkType_10ac7a70 : public UnkType_10ac7a70_Base
{
public:
    void Unk_10ac7a70();

private:
    char unk_000[0x28];
    UnkType_10ac7a70_Item** unk_028;
    int unk_02c;
    char unk_030[0x170 - 0x30];
    UnkType_1120a9b8* unk_170;
};

// UnkType_10ac7a70::Unk_10ac7a70
void UnkType_10ac7a70::Unk_10ac7a70()
{
    UnkType_10ac7a70_Base::Unk_10cd8ea0();
    if ( unk_170 )
    {
        if ( GUnk_1120a9b8 == unk_170 )
        {
            GUnk_1120a9b8 = 0;
        }
        delete unk_170;
        unk_170 = 0;
    }
    for ( int i = 0; i < unk_02c; i++ )
    {
        unk_028[i]->Unk_109b5bc0(0, 0);
    }
}
