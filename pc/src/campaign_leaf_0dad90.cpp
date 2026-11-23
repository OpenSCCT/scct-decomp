// campaign_leaf_0dad90.cpp -- method at VA 0x109dad90 taking a key: when the pointer array at 0x78
// (count at 0x7c) is empty and the object virtual slot 34 returns holds a pointer at 0x210, first
// passes that pointer to the method at VA 0x109dac30; then returns the first entry of the array
// whose virtual slot 24 (vtable offset 0x60) accepts the key, or 0. The class, member and method
// names are invented; the offsets and the slots are the binary's.

class UnkType_109dad90_Source;

class UnkType_109dad90_Entry
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
    virtual int VirtualSlot24(int Key);
};

class UnkType_109dad90_Default
{
public:
    unsigned char unk_00[0x210];
    UnkType_109dad90_Source* unk_210;
};

class UnkType_109dad90
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
    virtual UnkType_109dad90_Default* VirtualSlot34();

    UnkType_109dad90_Entry* Unk_109dad90(int Key);
    void Unk_109dac30(UnkType_109dad90_Source* Source);

private:
    unsigned char unk_04[0x78 - 0x04];
    UnkType_109dad90_Entry** unk_78;
    int unk_7c;
};

// UnkType_109dad90::Unk_109dad90
UnkType_109dad90_Entry* UnkType_109dad90::Unk_109dad90(int Key)
{
    if ( !unk_7c && VirtualSlot34()->unk_210 )
    {
        Unk_109dac30(VirtualSlot34()->unk_210);
    }
    for ( int i = 0; i < unk_7c; i++ )
    {
        if ( unk_78[i]->VirtualSlot24(Key) )
        {
            return unk_78[i];
        }
    }
    return 0;
}
