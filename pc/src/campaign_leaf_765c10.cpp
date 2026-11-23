// campaign_leaf_765c10.cpp -- one function at file offset 0x765c10, preferred VA 0x11065c10. For
// each of the objects at 0x38 and 0x3c that is set it releases the interfaces at 0x18 and 0x14
// that are set (the third method of a COM-style interface), deletes the object through its
// virtual destructor and clears the member. The class and member names are invented; the offsets
// and the addresses are the binary's.

class UnkType_11065c10_Interface
{
public:
    virtual long __stdcall VirtualSlot0();
    virtual unsigned long __stdcall VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

class UnkType_11065c10_Object
{
public:
    virtual ~UnkType_11065c10_Object();

    unsigned char unk_4[0x14 - 0x4];
    UnkType_11065c10_Interface* unk_14;
    UnkType_11065c10_Interface* unk_18;
};

class UnkType_11065c10
{
public:
    void Unk_11065c10();

    unsigned char unk_0[0x38];
    UnkType_11065c10_Object* unk_38;
    UnkType_11065c10_Object* unk_3c;
};

// UnkType_11065c10::Unk_11065c10
void UnkType_11065c10::Unk_11065c10()
{
    UnkType_11065c10_Interface* Interface;

    if ( unk_38 != 0 )
    {
        Interface = unk_38->unk_18;
        if ( Interface != 0 )
        {
            Interface->VirtualSlot2();
        }
        Interface = unk_38->unk_14;
        if ( Interface != 0 )
        {
            Interface->VirtualSlot2();
        }
        delete unk_38;
        unk_38 = 0;
    }
    if ( unk_3c != 0 )
    {
        Interface = unk_3c->unk_18;
        if ( Interface != 0 )
        {
            Interface->VirtualSlot2();
        }
        Interface = unk_3c->unk_14;
        if ( Interface != 0 )
        {
            Interface->VirtualSlot2();
        }
        delete unk_3c;
        unk_3c = 0;
    }
}
