// campaign_leaf_38d0d0.cpp -- a member function at VA 0x10c8d0d0 that decrements the int at 0x10
// and, when the interface pointer at 0x24 is not null, calls its __stdcall virtual slot 2 and
// clears it. guess: releases a COM interface. The class, method and member names are invented; the
// offsets and the slot are the binary's.

class UnkType_10c8d0d0_Interface
{
public:
    virtual void __stdcall VirtualSlot0();
    virtual void __stdcall VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

class UnkType_10c8d0d0
{
public:
    void Unk_10c8d0d0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    unsigned char unk_14[0x24 - 0x14];
    UnkType_10c8d0d0_Interface* unk_24;
};

// UnkType_10c8d0d0::Unk_10c8d0d0
void UnkType_10c8d0d0::Unk_10c8d0d0()
{
    unk_10--;
    if ( unk_24 )
    {
        unk_24->VirtualSlot2();
        unk_24 = 0;
    }
}
