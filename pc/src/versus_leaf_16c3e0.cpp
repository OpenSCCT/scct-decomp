// versus_leaf_16c3e0.cpp -- sets the int field at 0x558 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c3e0 (VA 0x10a6c3e0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c3e0
{
    unsigned char unk_00[0x558];
    int unk_558;                  // written by SetUnk558
};

class UnkType_10a6c3e0
{
public:
    void SetUnk558(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c3e0 *unk_30;
};

// UnkType_10a6c3e0::SetUnk558
// The function pops its one argument (ret 4).
void UnkType_10a6c3e0::SetUnk558(int Value)
{
    unk_30->unk_558 = Value;
}
