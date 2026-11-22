// versus_leaf_16c400.cpp -- sets the int field at 0x554 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c400 (VA 0x10a6c400).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c400
{
    unsigned char unk_00[0x554];
    int unk_554;                  // written by SetUnk554
};

class UnkType_10a6c400
{
public:
    void SetUnk554(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c400 *unk_30;
};

// UnkType_10a6c400::SetUnk554
// The function pops its one argument (ret 4).
void UnkType_10a6c400::SetUnk554(int Value)
{
    unk_30->unk_554 = Value;
}
