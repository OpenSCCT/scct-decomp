// campaign_leaf_27e600.cpp -- method at VA 0x10b7e600 taking two arguments: when the object at 0x184
// is set and its chain of pointers (from 0x24, following 0x28) reaches the object the global at VA
// 0x111f8ae8 holds (filled in first from L"Engine" by the function at VA 0x10a031a0 followed by
// the function at VA 0x109d0630), passes both arguments to the method at VA 0x109ee4a0 of what
// that object's virtual slot 33 (vtable offset 0x84) returns for this object. The class, member and
// method names are invented; the offsets, the slot, the string and the addresses are the binary's.

#include "campaign_global_111f8ae8.h"

UnkType_111f8ae8* Unk_10a031a0(const unsigned short* Package);
void Unk_109d0630();

class UnkType_10b7e600;

class UnkType_10b7e600_Result
{
public:
    void Unk_109ee4a0(int First, int Second);
};

class UnkType_10b7e600_184
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
    virtual UnkType_10b7e600_Result* VirtualSlot33(UnkType_10b7e600* Owner);

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

    unsigned char unk_04[0x24 - 0x04];
    UnkType_111f8ae8* unk_24;
};

class UnkType_10b7e600
{
public:
    void Unk_10b7e600(int First, int Second);

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
    UnkType_10b7e600_184* unk_184;
};

// UnkType_10b7e600::Unk_10b7e600
void UnkType_10b7e600::Unk_10b7e600(int First, int Second)
{
    if ( unk_184 && unk_184->UnkInheritsFrom(UnkLazyTarget()) )
    {
        UnkType_10b7e600_Result* Result = unk_184->VirtualSlot33(this);
        Result->Unk_109ee4a0(First, Second);
    }
}
