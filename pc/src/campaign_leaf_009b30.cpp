// campaign_leaf_009b30.cpp -- constructor at VA 0x10909b30 of a class whose vtable is at VA
// 0x110b7e68: sets the values at 0x04 and 0x08 to 100 and 600, clears the values at 0x18 to 0x24
// and 0x34, sets those at 0x28 to 0x30 to 1 and the one at 0x38 to -1, and stores the results of
// the functions at VA 0x10cca040, 0x10cca050 and 0x10cca060 at 0x0c, 0x10 and 0x14. The class,
// member and function names are invented; the offsets, the constants and the addresses are the
// binary's.

int Unk_10cca040();
int Unk_10cca050();
int Unk_10cca060();

class UnkType_10909b30
{
public:
    UnkType_10909b30();

    virtual void VirtualSlot0();

private:
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
};

// UnkType_10909b30::UnkType_10909b30
UnkType_10909b30::UnkType_10909b30()
: unk_04(100)
, unk_08(600)
, unk_18(0)
, unk_1c(0)
, unk_20(0)
, unk_24(0)
, unk_28(1)
, unk_2c(1)
, unk_30(1)
, unk_34(0)
, unk_38(-1)
{
    unk_0c = Unk_10cca040();
    unk_10 = Unk_10cca050();
    unk_14 = Unk_10cca060();
}
