// versus_leaf_16c3c0.cpp -- sets the int field at 0x608 of the
// object that the member at 0x30 points to, from the function at file offset 0x16c3c0 (VA 0x10a6c3c0).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c3c0
{
    unsigned char unk_00[0x608];
    int unk_608;                  // written by SetUnk608
};

class UnkType_10a6c3c0
{
public:
    void SetUnk608(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c3c0 *unk_30;
};

// UnkType_10a6c3c0::SetUnk608
// The function pops its one argument (ret 4).
void UnkType_10a6c3c0::SetUnk608(int Value)
{
    unk_30->unk_608 = Value;
}
