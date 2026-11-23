// campaign_leaf_613640.cpp -- thiscall method at VA 0x10f13640: calls the method at VA 0x10f12630
// with the addresses of two locals; when that returns true, passes them to virtual slot 0 (vtable
// offset 0x00) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f13640_Target
{
public:
    virtual void VirtualSlot0(int First, int Second);
};

class UnkType_10f13640
{
public:
    bool Unk_10f13640();
    bool Unk_10f12630(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f13640_Target* unk_10;
};

// UnkType_10f13640::Unk_10f13640
bool UnkType_10f13640::Unk_10f13640()
{
    int First;
    int Second;

    if ( Unk_10f12630(&First, &Second) )
    {
        unk_10->VirtualSlot0(First, Second);
        return true;
    }
    return false;
}
