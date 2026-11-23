// campaign_leaf_775160.cpp -- one function at file offset 0x775160, preferred VA 0x11075160. It
// returns 0xfffe0000 when the word at 0x8 is 2; otherwise it calls the ninth virtual method of the
// object at 0x24 and, when that is not negative, shifts it right by the word at 0x30 and passes it
// with the word at 0x1c to the stdcall function at VA 0x1104b1f0, returning the result. The class,
// method and member names are invented; the offsets and the callee's address are the binary's.

int __stdcall Unk_1104b1f0(int Value, int Divisor);

class UnkType_11075160_Object
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
    virtual int VirtualSlot8();
};

class UnkType_11075160
{
public:
    int Unk_11075160();

    int unk_0;
    int unk_4;
    int unk_8;
    unsigned char unk_c[0x1c - 0xc];
    int unk_1c;
    int unk_20;
    UnkType_11075160_Object* unk_24;
    unsigned char unk_28[0x30 - 0x28];
    int unk_30;
};

// UnkType_11075160::Unk_11075160
int UnkType_11075160::Unk_11075160()
{
    int Result;
    int Shifted;

    if ( unk_8 == 2 )
    {
        return 0xfffe0000;
    }
    Result = unk_24->VirtualSlot8();
    if ( Result >= 0 )
    {
        Shifted = Result >> unk_30;
        Result = Unk_1104b1f0(Shifted, unk_1c);
    }
    return Result;
}
