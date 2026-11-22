// campaign_leaf_112e00.cpp -- returns bit 0 of the dword at offset 0x4c of this. File offset
// 0x112e00, VA 0x10a12e00. The class and method names are invented; the offsets are the binary's.

class UnkType_10a12e00
{
public:
    int GetUnk4CBit0();

private:
    unsigned char unk_00[0x4c];     // not read by this function
    int unk_4c;
};

// UnkType_10a12e00::GetUnk4CBit0
int UnkType_10a12e00::GetUnk4CBit0()
{
    return unk_4c & 1;
}
