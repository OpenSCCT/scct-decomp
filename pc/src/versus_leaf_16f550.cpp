// versus_leaf_16f550.cpp -- sets the int field at 0x60c of the
// object that the member at 0x30 points to, from the function at file offset 0x16f550 (VA 0x10a6f550).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6f550
{
    unsigned char unk_00[0x60c];
    int unk_60c;                  // written by SetUnk60C
};

class UnkType_10a6f550
{
public:
    void SetUnk60C(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f550 *unk_30;
};

// UnkType_10a6f550::SetUnk60C
// The function pops its one argument (ret 4).
void UnkType_10a6f550::SetUnk60C(int Value)
{
    unk_30->unk_60c = Value;
}
