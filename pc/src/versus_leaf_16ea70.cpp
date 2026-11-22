// versus_leaf_16ea70.cpp -- returns the int field at 0x4f0 of the
// object that the member at 0x30 points to, from the function at file offset 0x16ea70 (VA 0x10a6ea70).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6ea70
{
    unsigned char unk_00[0x4f0];
    int unk_4f0;                  // read by GetUnk4F0
};

class UnkType_10a6ea70
{
public:
    int GetUnk4F0();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ea70 *unk_30;
};

// UnkType_10a6ea70::GetUnk4F0
// The function takes no argument.
int UnkType_10a6ea70::GetUnk4F0()
{
    return unk_30->unk_4f0;
}
