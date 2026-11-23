// campaign_leaf_770e00.cpp -- one function at file offset 0x770e00, preferred VA 0x11070e00. It
// returns 0 when the sixth virtual method rejects the first argument; otherwise it stores the
// third argument at 0x38 and, when the word at 0x8 of the second argument is set, stores it at 0x2c,
// stores the result of the stdcall function at VA 0x1104b1f0 on it and the third argument at 0x30,
// clears the words at 0x34 and 0x8 and returns 1 (0 when that word is clear). The class, method
// and member names are invented; the offsets and the callee's address are the binary's.

int __stdcall Unk_1104b1f0(int Value, int Divisor);

struct UnkType_11070e00_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_11070e00
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5(int Value);

    int Unk_11070e00(int Value, UnkType_11070e00_Record* Record, int Divisor);

    int unk_4;
    int unk_8;
    unsigned char unk_c[0x2c - 0xc];
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
};

// UnkType_11070e00::Unk_11070e00
int UnkType_11070e00::Unk_11070e00(int Value, UnkType_11070e00_Record* Record, int Divisor)
{
    if ( VirtualSlot5(Value) == 0 )
    {
        return 0;
    }
    unk_38 = Divisor;
    if ( Record->unk_8 != 0 )
    {
        unk_2c = Record->unk_8;
        unk_30 = Unk_1104b1f0(Record->unk_8, Divisor);
        unk_34 = 0;
        unk_8 = 0;
        return 1;
    }
    return 0;
}
