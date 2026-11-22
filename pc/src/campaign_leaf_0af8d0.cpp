// campaign_leaf_0af8d0.cpp -- one function at file offset 0xaf8d0, preferred VA 0x109af8d0. It
// copies the block at offset 0xe8 to offset 0x3cc and the block at offset 0xf4 to offset 0x3f0.
// The class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109af8d0_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109af8d0
{
public:
    void UnkCopyVecs();

private:
    unsigned char unk_00[0xe8];     // not read by this function
    UnkType_109af8d0_Triple unk_e8;
    UnkType_109af8d0_Triple unk_f4;
    unsigned char unk_100[0x2cc];   // not read by this function
    UnkType_109af8d0_Triple unk_3cc;
    unsigned char unk_3d8[0x18];    // not read by this function
    UnkType_109af8d0_Triple unk_3f0;
};

// UnkType_109af8d0::UnkCopyVecs
void UnkType_109af8d0::UnkCopyVecs()
{
    unk_3cc = unk_e8;
    unk_3f0 = unk_f4;
}
