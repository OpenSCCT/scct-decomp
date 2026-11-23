// campaign_leaf_61a690.cpp -- thiscall method at VA 0x10f1a690: calls the method at VA 0x10f1a1d0
// with the addresses of a zeroed byte and two zeroed values; when that returns true, passes the
// three values to virtual slot 3 of the object at 0x18 and returns true, otherwise returns false.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f1a690_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(char Kind, int First, int Second);
};

class UnkType_10f1a690
{
public:
    bool Unk_10f1a690();
    bool Unk_10f1a1d0(char* Kind, int* First, int* Second);

private:
    unsigned char unk_00[0x18];
    UnkType_10f1a690_Target* unk_18;
};

// UnkType_10f1a690::Unk_10f1a690
bool UnkType_10f1a690::Unk_10f1a690()
{
    int Second = 0;
    int First = 0;
    char Kind = 0;

    if ( Unk_10f1a1d0(&Kind, &First, &Second) )
    {
        unk_18->VirtualSlot3(Kind, First, Second);
        return true;
    }
    return false;
}
