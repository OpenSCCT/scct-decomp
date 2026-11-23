// campaign_leaf_60c550.cpp -- thiscall method at VA 0x10f0c550: calls the method at VA 0x10f084c0
// with the addresses of two locals; when that returns true, passes them to virtual slot 0 (vtable
// offset 0x00) of the object at 0x14 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f0c550_Target
{
public:
    virtual void VirtualSlot0(int First, int Second);
};

class UnkType_10f0c550
{
public:
    bool Unk_10f0c550();
    bool Unk_10f084c0(int* First, int* Second);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0c550_Target* unk_14;
};

// UnkType_10f0c550::Unk_10f0c550
bool UnkType_10f0c550::Unk_10f0c550()
{
    int First;
    int Second;

    if ( Unk_10f084c0(&First, &Second) )
    {
        unk_14->VirtualSlot0(First, Second);
        return true;
    }
    return false;
}
