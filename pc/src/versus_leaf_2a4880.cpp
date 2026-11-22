// versus_leaf_2a4880.cpp -- stores the int at 0x24 through the out-pointer argument, at file offset 0x2a4880 (VA 0x10ba4880).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10ba4880
{
public:
    int *GetUnk24(int *Out);

private:
    unsigned char unk_00[0x24];         // not read by this function
    int unk_24;                         // read by GetUnk24
};

// UnkType_10ba4880::GetUnk24
// The function pops its one argument (ret 4).
int *UnkType_10ba4880::GetUnk24(int *Out)
{
    *Out = unk_24;
    return Out;
}
