// versus_leaf_16ee10.cpp -- returns the int field at 0x63c of the
// object that the member at 0x30 points to, from the function at file offset 0x16ee10 (VA 0x10a6ee10).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6ee10
{
    unsigned char unk_00[0x63c];
    int unk_63c;                  // read by GetUnk63C
};

class UnkType_10a6ee10
{
public:
    int GetUnk63C();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ee10 *unk_30;
};

// UnkType_10a6ee10::GetUnk63C
// The function takes no argument.
int UnkType_10a6ee10::GetUnk63C()
{
    return unk_30->unk_63c;
}
