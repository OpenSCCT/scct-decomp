// versus_leaf_16c3d0.cpp -- sets the int field at 0x54c of the
// object that the member at 0x30 points to, from the function at file offset 0x16c3d0 (VA 0x10a6c3d0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c3d0
{
    unsigned char unk_00[0x54c];
    int unk_54c;                  // written by SetUnk54C
};

class UnkType_10a6c3d0
{
public:
    void SetUnk54C(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c3d0 *unk_30;
};

// UnkType_10a6c3d0::SetUnk54C
// The function pops its one argument (ret 4).
void UnkType_10a6c3d0::SetUnk54C(int Value)
{
    unk_30->unk_54c = Value;
}
