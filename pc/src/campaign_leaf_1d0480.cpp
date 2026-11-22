// campaign_leaf_1d0480.cpp -- clears the dword fields at offsets 0x08 to 0x1c, 0x24, 0x04 and 0x00
// of this, in the order the binary stores them, and returns this. File offset 0x1d0480, VA
// 0x10ad0480. The class and method names are invented; the offsets are the binary's. The field
// types are guesses.

class UnkType_10ad0480
{
public:
    UnkType_10ad0480 *UnkMethod_10ad0480();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    unsigned char unk_20[0x04];     // not written by this function
    int unk_24;
};

// UnkType_10ad0480::UnkMethod_10ad0480
UnkType_10ad0480 *UnkType_10ad0480::UnkMethod_10ad0480()
{
    unk_08 = 0;
    unk_0c = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1c = 0;
    unk_24 = 0;
    unk_04 = 0;
    unk_00 = 0;
    return this;
}
