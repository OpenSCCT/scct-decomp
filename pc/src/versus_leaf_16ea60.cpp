// versus_leaf_16ea60.cpp -- returns the int field at 0x4c0 of the
// object that the member at 0x30 points to, from the function at file offset 0x16ea60 (VA 0x10a6ea60).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6ea60
{
    unsigned char unk_00[0x4c0];
    int unk_4c0;                  // read by GetUnk4C0
};

class UnkType_10a6ea60
{
public:
    int GetUnk4C0();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ea60 *unk_30;
};

// UnkType_10a6ea60::GetUnk4C0
// The function takes no argument.
int UnkType_10a6ea60::GetUnk4C0()
{
    return unk_30->unk_4c0;
}
