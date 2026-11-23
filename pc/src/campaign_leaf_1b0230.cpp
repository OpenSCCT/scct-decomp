// campaign_leaf_1b0230.cpp -- thiscall method at VA 0x10ab0230. It calls the base class's method
// at VA 0x10cd8ea0; when the object at 0x170 is set it clears the global at VA 0x111fa7f0 if that
// points to the same object, deletes the object (destructor at VA 0x10aaf880, memory freed through
// slot 2 of the allocator at VA 0x111c88a0) and clears the member. It then calls virtual slot 58
// with two zeros on every object in the pointer array at 0x28. The class, method and member names
// are invented.

#include "campaign_global_111c88a0.h"
#include "campaign_global_1120a9b8.h"
#include "campaign_global_111fa7f0.h"

inline void operator delete(void* Original)
{
    GUnk_111c88a0->Free(Original);
}

class UnkType_10ab0230_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58(int First, int Second);
};

class UnkType_10ab0230_Base
{
public:
    void Unk_10cd8ea0();
};

class UnkType_10ab0230 : public UnkType_10ab0230_Base
{
public:
    void Unk_10ab0230();

private:
    char unk_000[0x28];
    UnkType_10ab0230_Item** unk_028;
    int unk_02c;
    char unk_030[0x170 - 0x30];
    UnkType_1120a9b8* unk_170;
};

// UnkType_10ab0230::Unk_10ab0230
void UnkType_10ab0230::Unk_10ab0230()
{
    UnkType_10ab0230_Base::Unk_10cd8ea0();
    if ( unk_170 )
    {
        if ( GUnk_111fa7f0 == unk_170 )
        {
            GUnk_111fa7f0 = 0;
        }
        delete unk_170;
        unk_170 = 0;
    }
    for ( int i = 0; i < unk_02c; i++ )
    {
        unk_028[i]->VirtualSlot58(0, 0);
    }
}
