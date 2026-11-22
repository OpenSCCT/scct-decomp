// campaign_leaf_1cd4c0.cpp -- clears the eight dwords at offsets 0x60 to 0x7c of this and sets the
// float at offset 0x80 to 1.0. File offset 0x1cd4c0, VA 0x10acd4c0. The class and method names are
// invented; the offsets are the binary's. The field types are guesses.

class UnkType_10acd4c0
{
public:
    void UnkMethod_10acd4c0();

private:
    unsigned char unk_00[0x60];     // not read by this function
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7c;
    float unk_80;
};

// UnkType_10acd4c0::UnkMethod_10acd4c0
void UnkType_10acd4c0::UnkMethod_10acd4c0()
{
    unk_60 = 0;
    unk_64 = 0;
    unk_68 = 0;
    unk_6c = 0;
    unk_70 = 0;
    unk_74 = 0;
    unk_78 = 0;
    unk_7c = 0;
    unk_80 = 1.0f;
}
