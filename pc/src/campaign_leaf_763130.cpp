// campaign_leaf_763130.cpp -- one function at file offset 0x763130, preferred VA 0x11063130. A
// constructor: after the base constructor at VA 0x110679f0 it installs the vtable at VA
// 0x11176380, sets the word at 0x7c to -1, clears the words at 0x4 and from 0x74 to 0x88 and the
// 0xdc-byte block at 0x8c, then sets the byte at 0x94 to 0x40, the word at 0xb0 to 1 and the word
// at 0x8c to 0x10000. The class names are invented; the offsets and the addresses are the
// binary's.

extern "C" void* __cdecl memset(void* Block, int Value, unsigned int Size);

class UnkType_11063130_Base
{
public:
    UnkType_11063130_Base();

    virtual void VirtualSlot0();

    int unk_4;
    unsigned char unk_8[0x74 - 0x8];
};

class UnkType_11063130 : public UnkType_11063130_Base
{
public:
    UnkType_11063130();

    virtual void VirtualSlot0();

    int unk_74;
    int unk_78;
    int unk_7c;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8c;
    int unk_90;
    unsigned char unk_94;
    unsigned char unk_95[0xb0 - 0x95];
    int unk_b0;
    unsigned char unk_b4[0x168 - 0xb4];
};

// UnkType_11063130::UnkType_11063130
UnkType_11063130::UnkType_11063130()
{
    unk_80 = 0;
    unk_84 = 0;
    unk_7c = -1;
    unk_78 = 0;
    unk_88 = 0;
    unk_74 = 0;
    unk_4 = 0;
    memset(&unk_8c, 0, 0xdc);
    unk_94 = 0x40;
    unk_90 = 0;
    unk_b0 = 1;
    unk_8c = 0x10000;
}
