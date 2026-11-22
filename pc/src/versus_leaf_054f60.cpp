// versus_leaf_054f60.cpp -- the function at file offset 0x54f60, VA 0x10954f60, 32 bytes. It merges
// two dwords under the mask at +0x58 of the object: the bits of the mask come from the second
// argument, the other bits keep the value of the first (ret 0xc: three stack arguments). The third
// argument is pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_10954f60
{
public:
    void UnkFunc_10954f60(unsigned int *Dest, unsigned int *Src, int Unused);

private:
    unsigned char unk_00[0x58];     // not read by this function
    unsigned int unk_58;            // mask
};

// UnkType_10954f60::UnkFunc_10954f60
void UnkType_10954f60::UnkFunc_10954f60(unsigned int *Dest, unsigned int *Src, int Unused)
{
    *Dest = ( *Dest & ~unk_58 ) | ( *Src & unk_58 );
}
