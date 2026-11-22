// versus_leaf_16f560.cpp -- sets the int field at 0x610 of the
// object that the member at 0x30 points to, from the function at file offset 0x16f560 (VA 0x10a6f560).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6f560
{
    unsigned char unk_00[0x610];
    int unk_610;                  // written by SetUnk610
};

class UnkType_10a6f560
{
public:
    void SetUnk610(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f560 *unk_30;
};

// UnkType_10a6f560::SetUnk610
// The function pops its one argument (ret 4).
void UnkType_10a6f560::SetUnk610(int Value)
{
    unk_30->unk_610 = Value;
}
