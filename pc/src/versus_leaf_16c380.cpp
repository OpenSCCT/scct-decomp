// versus_leaf_16c380.cpp -- sets the int field at 0x544 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c380 (VA 0x10a6c380).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c380
{
    unsigned char unk_00[0x544];
    int unk_544;                  // written by SetUnk544
};

class UnkType_10a6c380
{
public:
    void SetUnk544(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c380 *unk_30;
};

// UnkType_10a6c380::SetUnk544
// The function pops its one argument (ret 4).
void UnkType_10a6c380::SetUnk544(int Value)
{
    unk_30->unk_544 = Value;
}
