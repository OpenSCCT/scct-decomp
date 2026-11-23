// campaign_leaf_764550.cpp -- one function at file offset 0x764550, preferred VA 0x11064550. A
// constructor: after the base constructor at VA 0x110679f0 it installs the vtable at VA
// 0x11176468, sets the word at 0x4c to -1, clears the words at 0x4 and from 0x48 to 0x6c and the
// 0xdc-byte block at 0x78, then sets the byte at 0x80 to 0x40, the word at 0x9c to 1 and the word
// at 0x78 to 0x10000. The class names are invented; the offsets and the addresses are the
// binary's.

extern "C" void* __cdecl memset(void* Block, int Value, unsigned int Size);

class UnkType_11064550_Base
{
public:
    UnkType_11064550_Base();

    virtual void VirtualSlot0();

    int unk_4;
    unsigned char unk_8[0x48 - 0x8];
};

class UnkType_11064550 : public UnkType_11064550_Base
{
public:
    UnkType_11064550();

    virtual void VirtualSlot0();

    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    unsigned char unk_70[0x78 - 0x70];
    int unk_78;
    int unk_7c;
    unsigned char unk_80;
    unsigned char unk_81[0x9c - 0x81];
    int unk_9c;
    unsigned char unk_a0[0x154 - 0xa0];
};

// UnkType_11064550::UnkType_11064550
UnkType_11064550::UnkType_11064550()
{
    unk_6c = 0;
    unk_48 = 0;
    unk_50 = 0;
    unk_54 = 0;
    unk_4c = -1;
    unk_5c = 0;
    unk_58 = 0;
    unk_60 = 0;
    unk_64 = 0;
    unk_68 = 0;
    unk_4 = 0;
    memset(&unk_78, 0, 0xdc);
    unk_80 = 0x40;
    unk_7c = 0;
    unk_9c = 1;
    unk_78 = 0x10000;
}
