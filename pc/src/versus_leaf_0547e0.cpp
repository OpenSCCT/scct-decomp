// versus_leaf_0547e0.cpp -- the function at file offset 0x547e0, VA 0x109547e0, 21 bytes. It copies
// the two dwords of the pair at its second argument to the pair at its first argument (ret 0xc: three
// stack arguments). The third argument is pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkPair_109547e0
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_109547e0
{
public:
    void UnkFunc_109547e0(UnkPair_109547e0 *Dest, UnkPair_109547e0 *Src, int Unused);
};

// UnkType_109547e0::UnkFunc_109547e0
void UnkType_109547e0::UnkFunc_109547e0(UnkPair_109547e0 *Dest, UnkPair_109547e0 *Src, int Unused)
{
    Dest->unk_00 = Src->unk_00;
    Dest->unk_04 = Src->unk_04;
}
