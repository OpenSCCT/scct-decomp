// campaign_leaf_178450.cpp -- returns bit 0x20 of the dword at offset 0x2c of this, shifted down to
// bit 0. File offset 0x178450, VA 0x10a78450. The class and method names are invented; the offsets
// are the binary's.

class UnkType_10a78450
{
public:
    int GetUnk2CBit5();

private:
    unsigned char unk_00[0x2c];     // not read by this function
    unsigned int unk_2c;
};

// UnkType_10a78450::GetUnk2CBit5
int UnkType_10a78450::GetUnk2CBit5()
{
    return ( unk_2c >> 5 ) & 1;
}
