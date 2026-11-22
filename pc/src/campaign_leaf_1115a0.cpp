// campaign_leaf_1115a0.cpp -- returns bit 0 of the dword at offset 0x5c of this. File offset
// 0x1115a0, VA 0x10a115a0. The class and method names are invented; the offsets are the binary's.

class UnkType_10a115a0
{
public:
    int GetUnk5CBit0();

private:
    unsigned char unk_00[0x5c];     // not read by this function
    int unk_5c;
};

// UnkType_10a115a0::GetUnk5CBit0
int UnkType_10a115a0::GetUnk5CBit0()
{
    return unk_5c & 1;
}
