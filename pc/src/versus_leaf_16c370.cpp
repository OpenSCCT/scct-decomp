// versus_leaf_16c370.cpp -- sets the int field at 0x53c of the
// object that the member at 0x30 points to, from the function at file offset 0x16c370 (VA 0x10a6c370).
// The class, member and method names are invented; the offsets and the argument size are the binary's.

struct UnkPointee_10a6c370
{
    unsigned char unk_00[0x53c];
    int unk_53c;                  // written by SetUnk53C
};

class UnkType_10a6c370
{
public:
    void SetUnk53C(int Value);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c370 *unk_30;
};

// UnkType_10a6c370::SetUnk53C
// The function pops its one argument (ret 4).
void UnkType_10a6c370::SetUnk53C(int Value)
{
    unk_30->unk_53c = Value;
}
