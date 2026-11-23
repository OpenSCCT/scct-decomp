// campaign_leaf_0db430.cpp -- method at VA 0x109db430 taking a key: when virtual slot 45 (vtable
// offset 0xb4) accepts the key and the method at VA 0x109dad90 finds an entry for it, finds that
// entry in the pointer array at 0x78 (count at 0x7c), calls virtual slot 26 (vtable offset 0x68) of
// the entry stored there with the key and returns the word at 0x34 of the result; otherwise 0. The
// class, member and method names are invented; the offsets and the slots are the binary's.

class UnkType_109db430_Result
{
public:
    unsigned char unk_00[0x34];
    int unk_34;
};

class UnkType_109db430_Entry
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
    virtual UnkType_109db430_Result* VirtualSlot26(int Key);
};

struct UnkType_109db430_List
{
    // guess: an inline copy of the engine's TArray<T>::FindItemIndex
    int FindItemIndex(UnkType_109db430_Entry* Item) const
    {
        for ( int i = 0; i < unk_04; i++ )
        {
            if ( unk_00[i] == Item )
            {
                return i;
            }
        }
        return -1;
    }

    UnkType_109db430_Entry** unk_00;
    int unk_04;
};

class UnkType_109db430
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
    virtual int VirtualSlot45(int Key);

    int Unk_109db430(const int& Key);
    UnkType_109db430_Entry* Unk_109dad90(int Key);

private:
    unsigned char unk_04[0x78 - 0x04];
    UnkType_109db430_List unk_78;
};

// UnkType_109db430::Unk_109db430
int UnkType_109db430::Unk_109db430(const int& Key)
{
    if ( VirtualSlot45(Key) )
    {
        UnkType_109db430_Entry* Entry = Unk_109dad90(Key);
        if ( Entry )
        {
            UnkType_109db430_Result* Result =
                unk_78.unk_00[unk_78.FindItemIndex(Entry)]->VirtualSlot26(Key);
            if ( Result )
            {
                return Result->unk_34;
            }
        }
    }
    return 0;
}
