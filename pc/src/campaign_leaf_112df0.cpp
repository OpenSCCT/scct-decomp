// campaign_leaf_112df0.cpp -- returns the complement of bit 0 of the dword at offset 0x4c of this.
// File offset 0x112df0, VA 0x10a12df0. The class and method names are invented; the offsets are
// the binary's.

class UnkType_10a12df0
{
public:
    int GetUnk4CBit0Not();

private:
    unsigned char unk_00[0x4c];     // not read by this function
    int unk_4c;
};

// UnkType_10a12df0::GetUnk4CBit0Not
int UnkType_10a12df0::GetUnk4CBit0Not()
{
    return ( ~unk_4c ) & 1;
}
