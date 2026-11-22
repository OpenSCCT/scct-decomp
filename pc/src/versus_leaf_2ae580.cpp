// versus_leaf_2ae580.cpp -- stores either the dword at 4 or its address through the out-argument, as the count at
// 0x18 is below 8, and returns the out-argument, at file offset 0x2ae580 (VA 0x10bae580). The class and method
// names are invented; the offsets, the argument size and the unsigned compare are the binary's.

class UnkType_10bae580
{
public:
    int *GetUnk04(int *Out);

private:
    unsigned char unk_00[0x4];
    int unk_04;                         // read, or addressed, by GetUnk04
    unsigned char unk_08[0x18 - 0x8];
    unsigned int unk_18;                // compared with 8 by GetUnk04
};

// UnkType_10bae580::GetUnk04
// Returns Out in EAX; the function pops its one argument (ret 4).
int *UnkType_10bae580::GetUnk04(int *Out)
{
    if (unk_18 >= 8)
    {
        *Out = unk_04;
        return Out;
    }
    *Out = (int)&unk_04;
    return Out;
}
