// campaign_leaf_0d1af0.cpp -- method at VA 0x109d1af0: for an index within the 128-byte entry array
// at 0x94 (count at 0x98), reads the byte at 0x44 of that entry as a second index and, when it is
// within the pointer array at 0x78 (count at 0x7c) and the pointer there is set, returns it;
// otherwise returns the value at 0x210 of the object virtual slot 34 (vtable offset 0x88) returns.
// The class, member and method names are invented; the offsets, the sizes and the slot are the
// binary's.

class UnkType_109d1af0_Entry
{
public:
    unsigned char unk_00[0x44];
    unsigned char unk_44;
    unsigned char unk_45[0x80 - 0x45];
};

class UnkType_109d1af0_Default
{
public:
    unsigned char unk_000[0x210];
    void* unk_210;
};

class UnkType_109d1af0
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
    virtual UnkType_109d1af0_Default* VirtualSlot34();

    void* Unk_109d1af0(int Index);

private:
    unsigned char unk_04[0x74];
    void** unk_78;
    int unk_7c;
    unsigned char unk_80[0x14];
    UnkType_109d1af0_Entry* unk_94;
    int unk_98;
};

// UnkType_109d1af0::Unk_109d1af0
void* UnkType_109d1af0::Unk_109d1af0(int Index)
{
    if ( Index >= 0 && Index < unk_98 )
    {
        int Slot = unk_94[Index].unk_44;
        if ( Slot > -1 && unk_7c > Slot && unk_78[Slot] )
        {
            return unk_78[Slot];
        }
        return VirtualSlot34()->unk_210;
    }
    return VirtualSlot34()->unk_210;
}
