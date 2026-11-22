// versus_leaf_25a180.cpp -- copies the int at 0 of one argument record and the byte at 0 of another into the object and returns it, at file offset 0x25a180 (VA 0x10b5a180).
// The class, member, argument and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

struct UnkInt_10b5a180
{
    int unk_00;                         // read by CopyPair
};

struct UnkByte_10b5a180
{
    unsigned char unk_00;               // read by CopyPair
};

class UnkType_10b5a180
{
public:
    UnkType_10b5a180 &CopyPair(UnkInt_10b5a180 *A, UnkByte_10b5a180 *B);

private:
    int unk_00;                         // written by CopyPair
    unsigned char unk_04;               // written by CopyPair
};

// UnkType_10b5a180::CopyPair
// The function pops both arguments (ret 8) and returns *this.
UnkType_10b5a180 &UnkType_10b5a180::CopyPair(UnkInt_10b5a180 *A, UnkByte_10b5a180 *B)
{
    unk_00 = A->unk_00;
    unk_04 = B->unk_00;
    return *this;
}
