// campaign_leaf_61b430.cpp -- thiscall method at VA 0x10f1b430: calls the method at VA 0x10f1b490
// with the addresses of a byte set to 0x27 and two zeroed values; when that returns true, passes the
// three values to virtual slot 0 of the object at 0x20 and returns true, otherwise returns false.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f1b430_Target
{
public:
    virtual void VirtualSlot0(char Kind, int First, int Second);
};

class UnkType_10f1b430
{
public:
    bool Unk_10f1b430();
    bool Unk_10f1b490(char* Kind, int* First, int* Second);

private:
    unsigned char unk_00[0x20];
    UnkType_10f1b430_Target* unk_20;
};

// UnkType_10f1b430::Unk_10f1b430
bool UnkType_10f1b430::Unk_10f1b430()
{
    int Second = 0;
    int First = 0;
    char Kind = 0x27;

    if ( Unk_10f1b490(&Kind, &First, &Second) )
    {
        unk_20->VirtualSlot0(Kind, First, Second);
        return true;
    }
    return false;
}
