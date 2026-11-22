// campaign_leaf_1fe9a0.cpp -- copies the byte at offset 0x04 of the argument to this and the 24 bytes
// at offset 0x05 of the argument to offset 0x05 of this, then returns this. File offset 0x1fe9a0,
// VA 0x10afe9a0. The class and method names are invented; the offsets are the binary's. The field
// types and the meaning of the copied block are guesses.

class UnkType_10afe9a0
{
public:
    UnkType_10afe9a0 *UnkMethod_10afe9a0(UnkType_10afe9a0 *src);

private:
    unsigned char unk_00[0x04];     // not read by this function
    unsigned char unk_04;
    unsigned char unk_05[0x18];
};

// UnkType_10afe9a0::UnkMethod_10afe9a0
UnkType_10afe9a0 *UnkType_10afe9a0::UnkMethod_10afe9a0(UnkType_10afe9a0 *src)
{
    int i;

    unk_04 = src->unk_04;
    for (i = 0; i < 0x18; i++)
        unk_05[i] = src->unk_05[i];
    return this;
}
