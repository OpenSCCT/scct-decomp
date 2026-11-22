// versus_leaf_2558e0.cpp -- copies the int at 0 of two argument records into the object's first two ints and returns the object, at file offset 0x2558e0 (VA 0x10b558e0).
// The class, member, argument and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

struct UnkInt_10b558e0
{
    int unk_00;                         // read by CopyPair
};

class UnkType_10b558e0
{
public:
    UnkType_10b558e0 &CopyPair(UnkInt_10b558e0 *A, UnkInt_10b558e0 *B);

private:
    int unk_00;                         // written by CopyPair
    int unk_04;                         // written by CopyPair
};

// UnkType_10b558e0::CopyPair
// The function pops both arguments (ret 8) and returns *this.
UnkType_10b558e0 &UnkType_10b558e0::CopyPair(UnkInt_10b558e0 *A, UnkInt_10b558e0 *B)
{
    unk_00 = A->unk_00;
    unk_04 = B->unk_00;
    return *this;
}
