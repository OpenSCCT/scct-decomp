// versus_leaf_16c390.cpp -- sets the int field at 0x540 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c390 (VA 0x10a6c390).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c390
{
    unsigned char unk_00[0x540];
    int unk_540;                  // written by SetUnk540
};

class UnkType_10a6c390
{
public:
    void SetUnk540(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c390 *unk_30;
};

// UnkType_10a6c390::SetUnk540
// The function pops its one argument (ret 4).
void UnkType_10a6c390::SetUnk540(int Value)
{
    unk_30->unk_540 = Value;
}
