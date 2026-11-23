// campaign_leaf_7607d0.cpp -- one function at file offset 0x7607d0, preferred VA 0x110607d0. A
// constructor: it clears the word at 0x0, stores its arguments at 0xc, 0x8 and 0x10, allocates a
// 0x60-byte object through the allocator at VA 0x10901480 and constructs it with the first two
// arguments through the constructor at VA 0x110658c0, storing it at 0x4, and stores 0 at 0x14 when
// that succeeded and 2 otherwise. The class names are invented; the offsets and the addresses are
// the binary's.

class UnkType_110607d0_Child
{
public:
    static void* operator new(unsigned int Size);

    UnkType_110607d0_Child(int First, int Second);

    unsigned char unk_0[0x60];
};

class UnkType_110607d0
{
public:
    UnkType_110607d0(int First, int Second, int Third);

    int unk_0;
    UnkType_110607d0_Child* unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

// UnkType_110607d0::UnkType_110607d0
UnkType_110607d0::UnkType_110607d0(int First, int Second, int Third)
{
    unk_0 = 0;
    unk_c = First;
    unk_8 = Second;
    unk_10 = Third;
    unk_4 = new UnkType_110607d0_Child(First, Second);
    unk_14 = unk_4 != 0 ? 0 : 2;
}
