// campaign_leaf_47d7b0.cpp -- thiscall method at VA 0x10d7d7b0. It passes the object to its own
// method at 0x10d85930; then, when the 16-bit state at 0x80 is 4 or 5, it calls the object's
// method at 0x10da4810 if the object's second virtual method returns 2, or returns 10 and the
// flag at 0x2c of the object (seen as the kind-10 class) is set. The class, method and parameter
// names are invented.

class UnkType_10d7d7b0_Base
{
public:
    virtual void VirtualSlot0();
    virtual int VirtualSlot1();

    void Unk_10da4810();
};

class UnkType_10d7d7b0_Kind10 : public UnkType_10d7d7b0_Base
{
public:
    unsigned char unk_4[0x28];
    bool unk_2c;
};

class UnkType_10d7d7b0
{
public:
    void Unk_10d7d7b0(UnkType_10d7d7b0_Base* Object);
    void Unk_10d85930(UnkType_10d7d7b0_Base* Object);

private:
    unsigned char unk_0[0x80];
    short unk_80;
};

// UnkType_10d7d7b0::Unk_10d7d7b0
void UnkType_10d7d7b0::Unk_10d7d7b0(UnkType_10d7d7b0_Base* Object)
{
    short State;

    Unk_10d85930(Object);
    State = unk_80;
    if ( State == 4 || State == 5 )
    {
        switch ( Object->VirtualSlot1() )
        {
        case 2:
            Object->Unk_10da4810();
            break;
        case 10:
            if ( ( Object->VirtualSlot1() == 10 ? (UnkType_10d7d7b0_Kind10*)Object : 0 )->unk_2c )
            {
                Object->Unk_10da4810();
            }
            break;
        }
    }
}
