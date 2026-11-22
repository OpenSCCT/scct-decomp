// campaign_leaf_06a410.cpp -- one function at file offset 0x6a410, preferred VA 0x1096a410. It sets
// the byte at offset 0x4c to 0xa when the byte at offset 0x54 is 0, to 0xb when it is 1, and leaves
// it alone otherwise; it returns 0 in every case. The class and method names are invented; the
// offset and the bytes are the binary's.

class UnkType_1096a410
{
public:
    int UnkSetMode();

private:
    unsigned char unk_00[0x4c];     // not read by this function
    unsigned char unk_4c;           // set from the mode
    unsigned char unk_4d[0x7];      // not read by this function
    unsigned char unk_54;           // mode, 0 or 1 selects a value
};

// UnkType_1096a410::UnkSetMode
int UnkType_1096a410::UnkSetMode()
{
    switch ( unk_54 )
    {
    case 0:
        unk_4c = 0xa;
        break;
    case 1:
        unk_4c = 0xb;
        break;
    }
    return 0;
}
