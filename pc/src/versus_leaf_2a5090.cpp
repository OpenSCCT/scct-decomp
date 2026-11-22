// versus_leaf_2a5090.cpp -- stores its member at offset 0x20 through an out-argument and returns that argument,
// at file offset 0x2a5090 (VA 0x10ba5090). The class and method names are invented; the offsets and the
// argument sizes are the binary's.

class UnkType_10ba5090
{
public:
    int *CopyField20(int *Out);

private:
    unsigned char unk_00[0x20];
    int unk_20;
};

// UnkType_10ba5090::CopyField20
// Returns Out in EAX; the function pops its argument (ret 4).
int *UnkType_10ba5090::CopyField20(int *Out)
{
    *Out = unk_20;
    return Out;
}
