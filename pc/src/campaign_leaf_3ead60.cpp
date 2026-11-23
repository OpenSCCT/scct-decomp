// campaign_leaf_3ead60.cpp -- one function at file offset 0x3ead60, preferred VA 0x10cead60. When
// either word at 0x18 or 0x1c of Ar is set and the word at 0x20 of the object at 0x54 is none of
// 0x57, 0x58 and 0x5a, it passes Ar, Data and 0 to virtual slot 31 of that object; otherwise it
// passes the object to virtual slot 4 of Ar and Ar, Data and Third to virtual slot 30 of the
// object. The class, method, member and parameter names are invented; the offsets, the
// constants, the slots and the bytes are the binary's.

class UnkType_10cead60_Archive;

class UnkType_10cead60_Inner
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
    virtual void VirtualSlot30(UnkType_10cead60_Archive& Ar, unsigned char* Data, int Third);
    virtual void VirtualSlot31(UnkType_10cead60_Archive& Ar, unsigned char* Data, int Third);

    unsigned char unk_4[0x1c];
    int unk_20;
};

class UnkType_10cead60_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10cead60_Inner* Object);

    unsigned char unk_4[0x14];
    int unk_18;
    int unk_1c;
};

class UnkType_10cead60
{
public:
    void Unk_10cead60(UnkType_10cead60_Archive& Ar, unsigned char* Data, int Third);

    unsigned char unk_0[0x54];
    UnkType_10cead60_Inner* unk_54;
};

// UnkType_10cead60::Unk_10cead60
void UnkType_10cead60::Unk_10cead60(UnkType_10cead60_Archive& Ar, unsigned char* Data, int Third)
{
    if ( (Ar.unk_18 || Ar.unk_1c) && unk_54->unk_20 != 0x57 && unk_54->unk_20 != 0x58
        && unk_54->unk_20 != 0x5a )
    {
        unk_54->VirtualSlot31(Ar, Data, 0);
    }
    else
    {
        Ar.VirtualSlot4(unk_54);
        unk_54->VirtualSlot30(Ar, Data, Third);
    }
}
