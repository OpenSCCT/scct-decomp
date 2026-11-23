// campaign_leaf_4f45e0.cpp -- method at VA 0x10df45e0: when the mode is 0 or 1, calls virtual slot
// 7 of the object with 1; then passes the object and the mode to the method at VA 0x10da0960. The
// class, method and parameter names are invented; the slot and the address are the binary's.

class UnkType_10df45e0_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(int Value);
};

class UnkType_10df45e0
{
public:
    void Unk_10df45e0(UnkType_10df45e0_Object* Object, int Mode);
    void Unk_10da0960(UnkType_10df45e0_Object* Object, int Mode);
};

// UnkType_10df45e0::Unk_10df45e0
void UnkType_10df45e0::Unk_10df45e0(UnkType_10df45e0_Object* Object, int Mode)
{
    if ( Mode == 0 )
    {
        Object->VirtualSlot7(1);
    }
    else if ( Mode == 1 )
    {
        Object->VirtualSlot7(1);
    }
    Unk_10da0960(Object, Mode);
}
