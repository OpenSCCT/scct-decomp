// versus_leaf_16ea50.cpp -- returns the int field at 0x500 of the
// object that the member at 0x30 points to, from the function at file offset 0x16ea50 (VA 0x10a6ea50).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6ea50
{
    unsigned char unk_00[0x500];
    int unk_500;                  // read by GetUnk500
};

class UnkType_10a6ea50
{
public:
    int GetUnk500();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ea50 *unk_30;
};

// UnkType_10a6ea50::GetUnk500
// The function takes no argument.
int UnkType_10a6ea50::GetUnk500()
{
    return unk_30->unk_500;
}
