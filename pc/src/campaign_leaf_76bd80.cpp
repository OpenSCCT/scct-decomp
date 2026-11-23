// campaign_leaf_76bd80.cpp -- one function at file offset 0x76bd80, preferred VA 0x1106bd80. It
// returns 0 when the member at 0x64 is clear and the function at VA 0x11064fc0 fails to fill it
// from the block at 0x48 and its argument, or when the member at 0x6c is clear and the function
// at VA 0x11070cb0 fails to fill it from the word at 0xa4. Otherwise it stores at 0x88 the result
// of the first virtual method of the member at 0x6c on the member at 0x64 and returns 0 when that
// is -1 and 1 otherwise. The class, method and member names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1106bd80_Opener
{
public:
    virtual int VirtualSlot0(void* Source);
};

int Unk_11064fc0(void** Object, void* Block, int Value);
int Unk_11070cb0(UnkType_1106bd80_Opener** Object, int Value);

class UnkType_1106bd80
{
public:
    int Unk_1106bd80(int Value);

    unsigned char unk_0[0x48];
    unsigned char unk_48[0x64 - 0x48];
    void* unk_64;
    unsigned char unk_68[0x6c - 0x68];
    UnkType_1106bd80_Opener* unk_6c;
    unsigned char unk_70[0x88 - 0x70];
    int unk_88;
    unsigned char unk_8c[0xa4 - 0x8c];
    int unk_a4;
};

// UnkType_1106bd80::Unk_1106bd80
int UnkType_1106bd80::Unk_1106bd80(int Value)
{
    if ( unk_64 != 0 || Unk_11064fc0(&unk_64, unk_48, Value) == 0 )
    {
        if ( unk_6c != 0 || Unk_11070cb0(&unk_6c, unk_a4) == 0 )
        {
            unk_88 = unk_6c->VirtualSlot0(unk_64);
            if ( unk_88 != -1 )
            {
                return 1;
            }
        }
    }
    return 0;
}
