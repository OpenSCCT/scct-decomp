// versus_leaf_0546a0.cpp -- the function at file offset 0x546a0, VA 0x109546a0, 70 bytes. When the
// signed 16-bit count at +0x30 of the object is 1 it copies the dword at its second argument to the
// dword at its first argument; otherwise it copies that many dwords, element by element, from the
// second argument's array to the first (ret 0xc: three stack arguments). The third argument is pushed
// by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109546a0
{
public:
    void UnkFunc_109546a0(int *Dest, int *Src, int Unused);

private:
    unsigned char unk_00[0x30];     // not read by this function
    short unk_30;
};

// UnkType_109546a0::UnkFunc_109546a0
void UnkType_109546a0::UnkFunc_109546a0(int *Dest, int *Src, int Unused)
{
    int Index;
    if ( unk_30 == 1 )
    {
        *Dest = *Src;
        return;
    }
    for ( Index = 0; Index < unk_30; ++Index )
    {
        Dest[Index] = Src[Index];
    }
}
