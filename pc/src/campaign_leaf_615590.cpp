// campaign_leaf_615590.cpp -- thiscall method at VA 0x10f15590: calls the method at VA 0x10f15bb0
// with the addresses of four locals; when that returns true, passes them to virtual slot 8 (vtable
// offset 0x20) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f15590_Second
{
    unsigned char unk_00[0x204];
};

struct UnkType_10f15590_Third
{
    unsigned char unk_00[0x204];
};

class UnkType_10f15590_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8(int First, UnkType_10f15590_Second* Second,
                              UnkType_10f15590_Third* Third, int Fourth);
};

class UnkType_10f15590
{
public:
    bool Unk_10f15590();
    bool Unk_10f15bb0(int* First, UnkType_10f15590_Second* Second, UnkType_10f15590_Third* Third,
                      int* Fourth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f15590_Target* unk_10;
};

// UnkType_10f15590::Unk_10f15590
bool UnkType_10f15590::Unk_10f15590()
{
    int First;
    UnkType_10f15590_Second Second;
    UnkType_10f15590_Third Third;
    int Fourth;

    if ( Unk_10f15bb0(&First, &Second, &Third, &Fourth) )
    {
        unk_10->VirtualSlot8(First, &Second, &Third, Fourth);
        return true;
    }
    return false;
}
