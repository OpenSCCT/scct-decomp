// versus_leaf_29ffc0.cpp -- adds the first word argument to the words at 0 and 2 and the second to the words at 4 and
// 6, at file offset 0x29ffc0 (VA 0x10b9ffc0). The class and method names are invented; the offsets, the argument
// sizes and the calling convention are the binary's.

class UnkType_10b9ffc0
{
public:
    void AddUnk00Unk04(unsigned int A, unsigned int B);

private:
    unsigned short unk_00;              // updated by AddUnk00Unk04
    unsigned short unk_02;              // updated by AddUnk00Unk04
    unsigned short unk_04;              // updated by AddUnk00Unk04
    unsigned short unk_06;              // updated by AddUnk00Unk04
};

// UnkType_10b9ffc0::AddUnk00Unk04
// The function pops its two arguments (ret 8).
void UnkType_10b9ffc0::AddUnk00Unk04(unsigned int A, unsigned int B)
{
    unk_00 += A;
    unk_02 += A;
    unk_04 += B;
    unk_06 += B;
}
