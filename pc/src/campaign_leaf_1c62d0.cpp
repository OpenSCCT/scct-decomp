// campaign_leaf_1c62d0.cpp -- fills the 5-dword output with the dword at offset 0x44 of this, a
// count of the elements of the 20-byte array at offset 0x4c whose byte at offset 0x0c has bit 0
// clear (the count is taken over the number at offset 0x50), the dword at offset 0x38, and the
// dwords at offsets 0x16c and 0x68 of this. File offset 0x1c62d0, VA 0x10ac62d0. The class and
// method names are invented; the offsets are the binary's. The meanings of the fields are guesses.

class UnkType_10ac62d0Out
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

class UnkType_10ac62d0Elem
{
public:
    unsigned char unk_00[0x0c];     // not read by this function
    unsigned char unk_0c;
    unsigned char unk_0d[0x07];     // not read by this function
};

class UnkType_10ac62d0
{
public:
    void UnkMethod_10ac62d0(UnkType_10ac62d0Out *out);

private:
    unsigned char unk_00[0x38];     // not read by this function
    int unk_38;
    unsigned char unk_3c[0x08];     // not read by this function
    int unk_44;
    unsigned char unk_48[0x04];     // not read by this function
    UnkType_10ac62d0Elem *unk_4c;
    int unk_50;
    unsigned char unk_54[0x14];     // not read by this function
    int unk_68;
    unsigned char unk_6c[0x100];    // not read by this function
    int unk_16c;
};

// UnkType_10ac62d0::UnkMethod_10ac62d0
void UnkType_10ac62d0::UnkMethod_10ac62d0(UnkType_10ac62d0Out *out)
{
    int i;

    out->unk_00 = unk_44;
    out->unk_08 = unk_38;
    out->unk_04 = 0;
    for (i = 0; i < unk_50; i++)
        out->unk_04 += (unk_4c[i].unk_0c & 1) == 0;
    out->unk_0c = unk_16c;
    out->unk_10 = unk_68;
}
