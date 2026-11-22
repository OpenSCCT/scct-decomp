// versus_leaf_16dd80.cpp -- returns the int field at 0xc84 of the
// object that the member at 0x30 points to, from the function at file offset 0x16dd80 (VA 0x10a6dd80).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6dd80
{
    unsigned char unk_00[0xc84];
    int unk_c84;                  // read by GetUnkC84
};

class UnkType_10a6dd80
{
public:
    int GetUnkC84();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6dd80 *unk_30;
};

// UnkType_10a6dd80::GetUnkC84
// The function takes no argument.
int UnkType_10a6dd80::GetUnkC84()
{
    return unk_30->unk_c84;
}
