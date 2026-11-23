// campaign_leaf_24e8d0.cpp -- a virtual member function at VA 0x10b4e8d0 taking an int it does not
// read and a float, overriding one of the base at 0x08 (so it is entered with that base's
// address): when the float at 0x80 is above the float at 0x84 it clears it and calls the member at
// VA 0x10b4e430, otherwise it adds the float argument to it; then, while the float at 0x7c is
// above zero, it lowers it by the float argument, and once it reaches zero it clears it and calls
// the member at VA 0x10d32e70 of the object the pointer at 0x44 refers to with 1. It returns
// false. guess: steps two timers. The class, method, member and parameter names are invented; the
// offsets, addresses and constants are the binary's.

class UnkType_10b4e8d0_Item
{
public:
    void Unk_10d32e70(int Value);
};

class UnkType_10b4e8d0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b4e8d0_Face8
{
public:
    virtual bool Unk_10b4e8d0(int Unused, float Delta);
};

class UnkType_10b4e8d0 : public UnkType_10b4e8d0_Face0, public UnkType_10b4e8d0_Face8
{
public:
    bool Unk_10b4e430();
    virtual bool Unk_10b4e8d0(int Unused, float Delta);

private:
    unsigned char unk_0c[0x44 - 0x0c];
    UnkType_10b4e8d0_Item* unk_44;
    unsigned char unk_48[0x7c - 0x48];
    float unk_7c;
    float unk_80;
    float unk_84;
};

// UnkType_10b4e8d0::Unk_10b4e8d0
bool UnkType_10b4e8d0::Unk_10b4e8d0(int Unused, float Delta)
{
    if ( unk_80 > unk_84 )
    {
        unk_80 = 0.0f;
        Unk_10b4e430();
    }
    else
    {
        unk_80 += Delta;
    }
    if ( 0.0f < unk_7c )
    {
        unk_7c -= Delta;
        if ( 0.0f >= unk_7c )
        {
            unk_7c = 0.0f;
            unk_44->Unk_10d32e70(1);
        }
    }
    return false;
}
