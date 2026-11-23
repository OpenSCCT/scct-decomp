// campaign_leaf_775be0.cpp -- one function at file offset 0x775be0, preferred VA 0x11075be0. It
// calls the eighth virtual method of the object at 0x5c with 0, sets the word at 0xd4 to 1, stores
// the result of the stdcall function at VA 0x1104b270 on its argument and the word at 0x1c at 0xd8
// and 0xd0, and zeroes the words at 0x90, 0x6c and 0xdc. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

int __stdcall Unk_1104b270(int Value, int Scale);

class UnkType_11075be0_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(int Value);
};

class UnkType_11075be0
{
public:
    void Unk_11075be0(int Value);

    unsigned char unk_0[0x1c];
    int unk_1c;
    unsigned char unk_20[0x5c - 0x20];
    UnkType_11075be0_Object* unk_5c;
    unsigned char unk_60[0x6c - 0x60];
    int unk_6c;
    unsigned char unk_70[0x90 - 0x70];
    int unk_90;
    unsigned char unk_94[0xd0 - 0x94];
    int unk_d0;
    int unk_d4;
    int unk_d8;
    int unk_dc;
};

// UnkType_11075be0::Unk_11075be0
void UnkType_11075be0::Unk_11075be0(int Value)
{
    int Scaled;

    unk_5c->VirtualSlot7(0);
    unk_d4 = 1;
    Scaled = Unk_1104b270(Value, unk_1c);
    unk_d8 = Scaled;
    unk_90 = 0;
    unk_6c = 0;
    unk_d0 = Scaled;
    unk_dc = 0;
}
