// campaign_leaf_483b40.cpp -- thiscall method at VA 0x10d83b40. When the second virtual method of
// the given object returns 2, it passes this object's key (its word at 0x2c, or 0 after reporting
// the code 0xe000000e through 0x10d977f0 when the low 22 bits are zero) and 0x80010006 to the
// method at 0x10da6440 of the object returned by 0x10da5460. The class, method and parameter
// names are invented.

struct UnkType_10d83b40_Key
{
    UnkType_10d83b40_Key(unsigned int Value) : unk_0(Value) {}
    UnkType_10d83b40_Key(const UnkType_10d83b40_Key& Other) : unk_0(Other.unk_0) {}

    unsigned int unk_0;
};

class UnkType_10d83b40_Object
{
public:
    virtual void VirtualSlot0();
    virtual int VirtualSlot1();
};

class UnkType_10d83b40_Target
{
public:
    void Unk_10da6440(UnkType_10d83b40_Key Key, unsigned int Code);
};

void Unk_10d977f0(int First, int Second, unsigned int Code, int Fourth);
UnkType_10d83b40_Target* Unk_10da5460();

class UnkType_10d83b40
{
public:
    void Unk_10d83b40(UnkType_10d83b40_Object* Object);

    UnkType_10d83b40_Key GetKey()
    {
        if ( ( unk_2c & 0x3fffff ) == 0 )
        {
            Unk_10d977f0(0, 0, 0xe000000e, 0);
            return UnkType_10d83b40_Key(0);
        }
        return UnkType_10d83b40_Key(unk_2c);
    }

private:
    unsigned char unk_0[0x2c];
    unsigned int unk_2c;
};

// UnkType_10d83b40::Unk_10d83b40
void UnkType_10d83b40::Unk_10d83b40(UnkType_10d83b40_Object* Object)
{
    if ( Object->VirtualSlot1() == 2 )
    {
        Unk_10da5460()->Unk_10da6440(GetKey(), 0x80010006);
    }
}
