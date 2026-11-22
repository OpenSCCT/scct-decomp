// campaign_leaf_1e6b20.cpp -- clears the dwords at offsets 0x08, 0x0c and 0x00 of this, sets the
// dword at offset 0x10 to 1, and returns this. File offset 0x1e6b20, VA 0x10ae6b20. The class and
// method names are invented; the offsets are the binary's. The meanings of the fields are guesses.

class UnkType_10ae6b20
{
public:
    UnkType_10ae6b20 *UnkMethod_10ae6b20();

private:
    int unk_00;
    unsigned char unk_04[0x04];     // not written by this function
    int unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_10ae6b20::UnkMethod_10ae6b20
UnkType_10ae6b20 *UnkType_10ae6b20::UnkMethod_10ae6b20()
{
    unk_08 = 0;
    unk_0c = 0;
    unk_00 = 0;
    unk_10 = 1;
    return this;
}
