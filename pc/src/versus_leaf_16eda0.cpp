// versus_leaf_16eda0.cpp -- returns the int field at 0xc90 of the
// object that the member at 0x30 points to, from the function at file offset 0x16eda0 (VA 0x10a6eda0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6eda0
{
    unsigned char unk_00[0xc90];
    int unk_c90;                  // read by GetUnkC90
};

class UnkType_10a6eda0
{
public:
    int GetUnkC90();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6eda0 *unk_30;
};

// UnkType_10a6eda0::GetUnkC90
// The function takes no argument.
int UnkType_10a6eda0::GetUnkC90()
{
    return unk_30->unk_c90;
}
