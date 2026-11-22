// versus_leaf_2647f0.cpp -- zeroes the 0x412 words after the member at 8, at file offset 0x2647f0 (VA 0x10b647f0).
// The class and method names are invented; the offsets, the element count and the memset intrinsic are the
// binary's.

extern "C" void *memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)

class UnkType_10b647f0
{
public:
    void ZeroBlock();

private:
    unsigned char unk_00[0x8];
    unsigned int unk_08[0x412];
};

// UnkType_10b647f0::ZeroBlock
// Every byte of unk_08 is set to zero by the memset intrinsic; the function returns nothing and pops nothing.
void UnkType_10b647f0::ZeroBlock()
{
    memset(unk_08, 0, sizeof(unk_08));
}
