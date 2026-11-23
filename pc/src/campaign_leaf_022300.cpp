// campaign_leaf_022300.cpp -- method at VA 0x10922300 taking three values: passes the first two,
// the value the free function at VA 0x10ccb530 returns, 0x400 and the third to its virtual slot 4
// (vtable offset 0x10), and returns that value. The class and function names are invented; the
// constant, the slot and the address are the binary's.

int Unk_10ccb530();

class UnkType_10922300
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int Arg0, int Arg1, int Value, int Size, int Arg2);

    int Unk_10922300(int Arg0, int Arg1, int Arg2);
};

// UnkType_10922300::Unk_10922300
int UnkType_10922300::Unk_10922300(int Arg0, int Arg1, int Arg2)
{
    int Value = Unk_10ccb530();
    VirtualSlot4(Arg0, Arg1, Value, 0x400, Arg2);
    return Value;
}
