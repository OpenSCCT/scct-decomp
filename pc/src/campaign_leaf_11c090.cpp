// campaign_leaf_11c090.cpp -- clears bit 0x02 of the dword at offset 0x2e4 of this and returns 0.
// The five arguments are not read. File offset 0x11c090, VA 0x10a1c090. The class and method names
// are invented; the offsets are the binary's.

class UnkType_10a1c090
{
public:
    int UnkMethod_10a1c090(int, int, int, int, int);

private:
    unsigned char unk_00[0x2e4];    // not read by this function
    unsigned int unk_2e4;           // bit 0x02 is cleared
};

// UnkType_10a1c090::UnkMethod_10a1c090
int UnkType_10a1c090::UnkMethod_10a1c090(int, int, int, int, int)
{
    unk_2e4 &= 0xfffffffd;
    return 0;
}
