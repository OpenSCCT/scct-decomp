// campaign_leaf_186110.cpp -- one function at file offset 0x186110, preferred VA 0x10a86110.
// guess: sets the object at offset 0x228 to its argument when the argument is non-null and the
// check at VA 0x10a85b50 accepts it. While flag 0x2000000 at 0x30 is set, the listener at 0x3a10
// of the owner at 0x7c is told before (virtual slot 3) and after (virtual slot 2) the change.
// It then calls its method at VA 0x10993770.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a86110;

class UnkType_10a86110_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10a86110* Object);
    virtual void VirtualSlot3(UnkType_10a86110* Object);
};

class UnkType_10a86110_Owner
{
public:
    unsigned char unk_0[0x3a10];
    UnkType_10a86110_Listener* unk_3a10;
};

class UnkType_10a86110_Value;

int Unk_10a85b50(UnkType_10a86110_Value* Value);

class UnkType_10a86110
{
public:
    unsigned char unk_0[0x30];
    unsigned int unk_30;
    unsigned char unk_34[0x7c - 0x34];
    UnkType_10a86110_Owner* unk_7c;
    unsigned char unk_80[0x228 - 0x80];
    UnkType_10a86110_Value* unk_228;

    void Unk_10a86110(UnkType_10a86110_Value* Value);
    void Unk_10993770();
};

// UnkType_10a86110::Unk_10a86110
void UnkType_10a86110::Unk_10a86110(UnkType_10a86110_Value* Value)
{
    if ( Value && Unk_10a85b50(Value) )
    {
        if ( unk_30 & 0x2000000 )
        {
            UnkType_10a86110_Listener* Listener = unk_7c->unk_3a10;
            if ( Listener )
            {
                Listener->VirtualSlot3(this);
            }
        }
        unk_228 = Value;
        if ( unk_30 & 0x2000000 )
        {
            UnkType_10a86110_Listener* Listener = unk_7c->unk_3a10;
            if ( Listener )
            {
                Listener->VirtualSlot2(this);
            }
        }
        Unk_10993770();
    }
}
