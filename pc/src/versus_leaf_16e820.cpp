// versus_leaf_16e820.cpp -- stores whether its argument is 1 and whether it is 2 in the bytes at 0x52c and 0x52d of the object at 0x30, at file offset 0x16e820 (VA 0x10a6e820).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6e820
{
    unsigned char unk_00[0x52c];
    unsigned char unk_52c;              // written by SetUnk52C_52D
    unsigned char unk_52d;              // written by SetUnk52C_52D
};

class UnkType_10a6e820
{
public:
    void SetUnk52C_52D(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6e820 *unk_30;
};

// UnkType_10a6e820::SetUnk52C_52D
// The function pops its one argument (ret 4).
void UnkType_10a6e820::SetUnk52C_52D(int Value)
{
    unk_30->unk_52c = Value == 1;
    unk_30->unk_52d = Value == 2;
}
