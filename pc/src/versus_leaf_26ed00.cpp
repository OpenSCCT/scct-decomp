// versus_leaf_26ed00.cpp -- stores 2 through the byte pointer when the signed byte argument is 1 or 2, at file offset
// 0x26ed00 (VA 0x10b6ed00). The class and method names are invented; the offsets, the argument sizes and the
// __stdcall convention are the binary's.

class UnkType_10b6ed00
{
public:
    static void __stdcall StoreTwoForSmall(char Value, unsigned char *Out);
};

// UnkType_10b6ed00::StoreTwoForSmall
// The function pops its two arguments (ret 8).
void __stdcall UnkType_10b6ed00::StoreTwoForSmall(char Value, unsigned char *Out)
{
    if (Value > 0 && Value <= 2)
    {
        *Out = 2;
    }
}
