// versus_leaf_16f580.cpp -- sets the int field at 0x61c of the
// object that the member at 0x30 points to, from the function at file offset 0x16f580 (VA 0x10a6f580).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6f580
{
    unsigned char unk_00[0x61c];
    int unk_61c;                  // written by SetUnk61C
};

class UnkType_10a6f580
{
public:
    void SetUnk61C(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f580 *unk_30;
};

// UnkType_10a6f580::SetUnk61C
// The function pops its one argument (ret 4).
void UnkType_10a6f580::SetUnk61C(int Value)
{
    unk_30->unk_61c = Value;
}
