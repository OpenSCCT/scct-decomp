// versus_leaf_16c3a0.cpp -- sets the int field at 0x618 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c3a0 (VA 0x10a6c3a0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c3a0
{
    unsigned char unk_00[0x618];
    int unk_618;                  // written by SetUnk618
};

class UnkType_10a6c3a0
{
public:
    void SetUnk618(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c3a0 *unk_30;
};

// UnkType_10a6c3a0::SetUnk618
// The function pops its one argument (ret 4).
void UnkType_10a6c3a0::SetUnk618(int Value)
{
    unk_30->unk_618 = Value;
}
