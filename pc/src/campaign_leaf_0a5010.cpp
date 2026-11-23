// campaign_leaf_0a5010.cpp -- method at VA 0x109a5010: when the pointer at 0x2c0 is set, walks the
// pointer array at 0x2c (count at 0x30) of the object reached through 0x7c, 0x38 and 0x44, and for
// the first entry whose pointer at 0x190 is set calls virtual slot 36 (vtable offset 0x90) of the
// object at 0x2c0 with that pointer. The class, member and method names are invented; the offsets
// and the slot are the binary's.

class UnkType_109a5010_Target;

class UnkType_109a5010_Entry
{
public:
    unsigned char unk_00[0x190];
    UnkType_109a5010_Target* unk_190;
};

class UnkType_109a5010_List
{
public:
    unsigned char unk_00[0x2c];
    UnkType_109a5010_Entry** unk_2c;
    int unk_30;
};

class UnkType_109a5010_Inner
{
public:
    unsigned char unk_00[0x44];
    UnkType_109a5010_List* unk_44;
};

class UnkType_109a5010_Outer
{
public:
    unsigned char unk_00[0x38];
    UnkType_109a5010_Inner* unk_38;
};

class UnkType_109a5010_Handler
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
    virtual void VirtualSlot36(UnkType_109a5010_Target* Target);
};

class UnkType_109a5010
{
public:
    void Unk_109a5010();

private:
    unsigned char unk_00[0x7c];
    UnkType_109a5010_Outer* unk_7c;
    unsigned char unk_80[0x2c0 - 0x80];
    UnkType_109a5010_Handler* unk_2c0;
};

// UnkType_109a5010::Unk_109a5010
void UnkType_109a5010::Unk_109a5010()
{
    if ( unk_2c0 )
    {
        for ( int i = 0; i < unk_7c->unk_38->unk_44->unk_30; i++ )
        {
            UnkType_109a5010_Entry* Entry = unk_7c->unk_38->unk_44->unk_2c[i];
            if ( Entry && Entry->unk_190 )
            {
                unk_2c0->VirtualSlot36(Entry->unk_190);
                return;
            }
        }
    }
}
