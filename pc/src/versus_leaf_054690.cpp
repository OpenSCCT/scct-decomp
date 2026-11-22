// versus_leaf_054690.cpp -- the function at file offset 0x54690, VA 0x10954690, 15 bytes. It copies
// the dword at its second argument to the dword at its first argument (ret 0xc: three stack
// arguments). The third argument is pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_10954690
{
public:
    void UnkFunc_10954690(int *Dest, int *Src, int Unused);
};

// UnkType_10954690::UnkFunc_10954690
void UnkType_10954690::UnkFunc_10954690(int *Dest, int *Src, int Unused)
{
    *Dest = *Src;
}
