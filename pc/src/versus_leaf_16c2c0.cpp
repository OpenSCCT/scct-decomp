// versus_leaf_16c2c0.cpp -- sets the int field at 0x88 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c2c0 (VA 0x10a6c2c0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c2c0
{
    unsigned char unk_00[0x88];
    int unk_88;                  // written by SetUnk88
};

class UnkType_10a6c2c0
{
public:
    void SetUnk88(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c2c0 *unk_30;
};

// UnkType_10a6c2c0::SetUnk88
// The function pops its one argument (ret 4).
void UnkType_10a6c2c0::SetUnk88(int Value)
{
    unk_30->unk_88 = Value;
}
