// campaign_leaf_11c720.cpp -- one function at file offset 0x11c720, preferred VA 0x10a1c720.
// When the word at offset 0x2f0 differs from the one at offset 0x11c, or bit 0 of the word at
// offset 0x120 is set, it calls its own virtual slot 25 and then slot 24 with the word at offset
// 0x11c; then, when bit 0 of the word at offset 0x68 is set, it calls the method at VA 0x1092d230
// on every 16-byte element of the array at offset 0x6c (count at 0x70).
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a1c720_Element
{
public:
    unsigned char unk_0[0x10];

    void Unk_1092d230();
};

class UnkType_10a1c720
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
    virtual void VirtualSlot24(int Value);
    virtual void VirtualSlot25();

    unsigned char unk_4[0x68 - 0x4];
    unsigned int unk_68_0 : 1;
    UnkType_10a1c720_Element* unk_6c;
    int unk_70;
    unsigned char unk_74[0x11c - 0x74];
    int unk_11c;
    unsigned int unk_120_0 : 1;
    unsigned char unk_124[0x2f0 - 0x124];
    int unk_2f0;

    void Unk_10a1c720();
};

// UnkType_10a1c720::Unk_10a1c720
void UnkType_10a1c720::Unk_10a1c720()
{
    if ( unk_2f0 != unk_11c || unk_120_0 )
    {
        VirtualSlot25();
        VirtualSlot24(unk_11c);
    }
    if ( unk_68_0 )
    {
        for ( int i = 0; i < unk_70; i++ )
        {
            unk_6c[i].Unk_1092d230();
        }
    }
}
