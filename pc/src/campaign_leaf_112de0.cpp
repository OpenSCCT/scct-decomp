// campaign_leaf_112de0.cpp -- returns bit 0 of the dword at offset 0x4c of this. File offset
// 0x112de0, VA 0x10a12de0. The class and method names are invented; the offsets are the binary's.

class UnkType_10a12de0
{
public:
    int GetUnk4CBit0();

private:
    unsigned char unk_00[0x4c];     // not read by this function
    int unk_4c;
};

// UnkType_10a12de0::GetUnk4CBit0
int UnkType_10a12de0::GetUnk4CBit0()
{
    return unk_4c & 1;
}
