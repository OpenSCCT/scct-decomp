// campaign_leaf_014990.cpp -- method at VA 0x10914990: when IsWindow accepts the window handle at
// 0x44 and the method at VA 0x10d09f20 of the member at 0x40 returns nonzero, passes the 8-byte
// value the method at VA 0x10914a00 returns to the method at VA 0x10d09f90 of that member and, when
// that returns a positive value, returns what virtual slot 8 (vtable offset 0x20) of the object its
// own virtual slot 63 (offset 0xfc) returns for it returns; otherwise returns 0. The class, member
// and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_import_IsWindow.h"

class UnkType_10914a00_014990
{
public:
    UnkType_10914a00_014990();

private:
    int unk_00;
    int unk_04;
};

class UnkType_10d09f20_014990
{
public:
    int Unk_10d09f20();
    int Unk_10d09f90(UnkType_10914a00_014990 Value);
};

class UnkType_10914990_Object
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
    virtual int VirtualSlot8();
};

class UnkType_10914990
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
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual UnkType_10914990_Object* VirtualSlot63(int Index);

    int Unk_10914990();
    UnkType_10914a00_014990 Unk_10914a00();

private:
    unsigned char unk_04[0x3c];
    UnkType_10d09f20_014990 unk_40;
    unsigned char unk_41[0x03];
    HWND unk_44;
};

// UnkType_10914990::Unk_10914990
int UnkType_10914990::Unk_10914990()
{
    if ( IsWindow(unk_44) && unk_40.Unk_10d09f20() )
    {
        UnkType_10914a00_014990 Value = Unk_10914a00();
        int Index = unk_40.Unk_10d09f90(Value);
        if ( Index > 0 )
        {
            return VirtualSlot63(Index)->VirtualSlot8();
        }
    }
    return 0;
}
