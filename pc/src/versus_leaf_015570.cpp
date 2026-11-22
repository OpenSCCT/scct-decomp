// versus_leaf_015570.cpp -- the function at file offset 0x15570, VA 0x10915570, 16 bytes. It compares
// the int at +0x00 of the object with the int that its one stack argument points to, and returns
// 1 when they are equal and 0 otherwise.
// The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10915570
{
public:
    int UnkFunc_10915570(int *Other);

private:
    int unk_00;
};

// UnkType_10915570::UnkFunc_10915570
int UnkType_10915570::UnkFunc_10915570(int *Other)
{
    return unk_00 == *Other;
}
