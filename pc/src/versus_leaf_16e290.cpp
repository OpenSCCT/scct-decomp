// versus_leaf_16e290.cpp -- returns the int field at 0xc78 of the
// object that the member at 0x30 points to, from the function at file offset 0x16e290 (VA 0x10a6e290).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6e290
{
    unsigned char unk_00[0xc78];
    int unk_c78;                  // read by GetUnkC78
};

class UnkType_10a6e290
{
public:
    int GetUnkC78();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6e290 *unk_30;
};

// UnkType_10a6e290::GetUnkC78
// The function takes no argument.
int UnkType_10a6e290::GetUnkC78()
{
    return unk_30->unk_c78;
}
