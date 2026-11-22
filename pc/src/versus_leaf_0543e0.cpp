// versus_leaf_0543e0.cpp -- the function at file offset 0x543e0, VA 0x109543e0, 15 bytes. It copies
// the byte at its second argument to the byte at its first argument (ret 0xc: three stack arguments).
// The third argument is pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109543e0
{
public:
    void UnkFunc_109543e0(unsigned char *Dest, unsigned char *Src, int Unused);
};

// UnkType_109543e0::UnkFunc_109543e0
void UnkType_109543e0::UnkFunc_109543e0(unsigned char *Dest, unsigned char *Src, int Unused)
{
    *Dest = *Src;
}
