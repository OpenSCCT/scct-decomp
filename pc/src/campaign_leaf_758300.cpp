// campaign_leaf_758300.cpp -- one function at file offset 0x758300, preferred VA 0x11058300. It
// returns 0 when the tenth virtual method of the record's object at 0xc gives 0. Otherwise it
// stores at 0x14 of the record a handle for that result: from the first virtual method of the
// object at 0x50 when the record's word at 0x10 is set (failing on -1), and from the function at
// VA 0x11053c40 with the word the second argument points to and the third argument otherwise
// (failing on 0xffff). It returns 1, or 0 on failure. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11058300_Source
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
    virtual int VirtualSlot9();
};

class UnkType_11058300_Opener
{
public:
    virtual int VirtualSlot0(int Value);
};

struct UnkType_11058300_Record
{
    unsigned char unk_0[0xc];
    UnkType_11058300_Source* unk_c;
    int unk_10;
    int unk_14;
};

int Unk_11053c40(int Value, int Key, int Extra);

class UnkType_11058300
{
public:
    int Unk_11058300(UnkType_11058300_Record* Record, int* Key, int Extra);

    unsigned char unk_0[0x50];
    UnkType_11058300_Opener* unk_50;
};

// UnkType_11058300::Unk_11058300
int UnkType_11058300::Unk_11058300(UnkType_11058300_Record* Record, int* Key, int Extra)
{
    int Value;

    Value = Record->unk_c->VirtualSlot9();
    if ( Value != 0 )
    {
        if ( Record->unk_10 != 0 )
        {
            Record->unk_14 = unk_50->VirtualSlot0(Value);
            if ( Record->unk_14 != -1 )
            {
                return 1;
            }
        }
        else
        {
            Record->unk_14 = Unk_11053c40(Value, *Key, Extra);
            if ( Record->unk_14 != 0xffff )
            {
                return 1;
            }
        }
    }
    return 0;
}
