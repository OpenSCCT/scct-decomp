// campaign_leaf_075d00.cpp -- method at VA 0x10975d00: when bit 0 of the value at 0xf8 is set,
// passes 1, the value at 0xe4, 0, 1.0, 0 and 0 to virtual slot 5 (vtable offset 0x14) of the object
// its argument points to, then clears the value at 0x0c of the object at 0xf4. The class, member
// and method names are invented; the offsets, the constants and the slot are the binary's.

class UnkType_10975d00_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Arg0, int Arg1, int Arg2, float Arg3, int Arg4, int Arg5);
};

class UnkType_10975d00_f4
{
public:
    unsigned char unk_00[0x0c];
    int unk_0c;
};

class UnkType_10975d00
{
public:
    void Unk_10975d00(UnkType_10975d00_Target* Target);

private:
    unsigned char unk_00[0xe4];
    int unk_e4;
    unsigned char unk_e8[0xf4 - 0xe8];
    UnkType_10975d00_f4* unk_f4;
    unsigned int unk_f8;
};

// UnkType_10975d00::Unk_10975d00
void UnkType_10975d00::Unk_10975d00(UnkType_10975d00_Target* Target)
{
    if ( unk_f8 & 1 )
    {
        Target->VirtualSlot5(1, unk_e4, 0, 1.0f, 0, 0);
        unk_f4->unk_0c = 0;
    }
}
