// versus_leaf_16f570.cpp -- sets the int field at 0x614 of the
// object that the member at 0x30 points to, from the function at file offset 0x16f570 (VA 0x10a6f570).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6f570
{
    unsigned char unk_00[0x614];
    int unk_614;                  // written by SetUnk614
};

class UnkType_10a6f570
{
public:
    void SetUnk614(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f570 *unk_30;
};

// UnkType_10a6f570::SetUnk614
// The function pops its one argument (ret 4).
void UnkType_10a6f570::SetUnk614(int Value)
{
    unk_30->unk_614 = Value;
}
