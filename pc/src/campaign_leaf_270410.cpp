// campaign_leaf_270410.cpp -- one function at file offset 0x270410, preferred VA 0x10b70410. When
// the byte at offset 0xc is nonzero it clears the words at offsets 0x2c-0x34, the eight words at
// offset 0x38 and the bytes at offsets 0xd and 0xc. It always returns 1. The class, method and
// member names are invented; the offset and the bytes are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);

struct UnkBlock
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;

};

class UnkType_10b70410
{
public:
    unsigned char unk_0[0xc];
    unsigned char unk_c;
    unsigned char unk_d;
    unsigned char unk_e[0x2c - 0xe];
    int unk_2c;
    int unk_30;
    int unk_34;
    UnkBlock unk_38;

    bool Unk_10b70410();
};

// UnkType_10b70410::Unk_10b70410
bool UnkType_10b70410::Unk_10b70410()
{
    if ( unk_c )
    {
        unk_2c = 0;
        unk_30 = 0;
        unk_34 = 0;
        memset(&unk_38, 0, sizeof(unk_38));
        unk_d = 0;
        unk_c = 0;
    }
    return true;
}
