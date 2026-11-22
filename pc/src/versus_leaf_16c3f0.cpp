// versus_leaf_16c3f0.cpp -- sets the int field at 0x550 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c3f0 (VA 0x10a6c3f0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c3f0
{
    unsigned char unk_00[0x550];
    int unk_550;                  // written by SetUnk550
};

class UnkType_10a6c3f0
{
public:
    void SetUnk550(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c3f0 *unk_30;
};

// UnkType_10a6c3f0::SetUnk550
// The function pops its one argument (ret 4).
void UnkType_10a6c3f0::SetUnk550(int Value)
{
    unk_30->unk_550 = Value;
}
