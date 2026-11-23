// campaign_leaf_068430.cpp -- constructor at VA 0x10968430 of a class whose vtable is at VA
// 0x110beeb8: runs the base constructor at VA 0x10cd7930 and stores its three arguments at 0x2c,
// 0x30 and 0x34. The class and member names are invented; the offsets and the addresses are the
// binary's.

class UnkType_10968430_Base
{
public:
    UnkType_10968430_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x28];
};

class UnkType_10968430 : public UnkType_10968430_Base
{
public:
    UnkType_10968430(int Arg0, int Arg1, int Arg2);
    virtual void VirtualSlot0();

private:
    int unk_2c;
    int unk_30;
    int unk_34;
};

// UnkType_10968430::UnkType_10968430
UnkType_10968430::UnkType_10968430(int Arg0, int Arg1, int Arg2)
: unk_2c(Arg0)
, unk_30(Arg1)
, unk_34(Arg2)
{
}
