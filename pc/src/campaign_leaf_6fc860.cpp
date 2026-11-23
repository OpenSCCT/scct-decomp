// campaign_leaf_6fc860.cpp -- function at VA 0x10ffc860: takes the base-2 logarithm of its third
// argument (rounded down; zero counts as one), then creates a 0x80-byte object with the
// constructor at VA 0x10ff8ad0, passing its first two arguments and the logarithm, and returns it.
// The object's operator new allocates with tag 0x1c from the allocator at VA 0x1131b3d8 and keeps
// the size at 0x04. It has no this pointer. The class, function and parameter names are
// invented; the addresses and sizes are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10ffc860
{
public:
    UnkType_10ffc860(int First, int Second, int Shift);

    // guess: allocates the object and keeps its size at 0x04 for operator delete.
    void* operator new(unsigned int Size)
    {
        UnkType_10ffc860* Object;

        Object = (UnkType_10ffc860*)GUnk_1131b3d8->VirtualSlot4(Size, 0x1c);
        Object->unk_4 = (unsigned short)Size;
        return Object;
    }

private:
    int unk_0;
    unsigned short unk_4;
    unsigned char unk_6[0x7a];
};

// Unk_10ffc860
UnkType_10ffc860* Unk_10ffc860(int First, int Second, int Count)
{
    int Shift;

    if ( Count == 0 )
    {
        Count = 1;
    }
    Shift = -1;
    while ( Count > 0 )
    {
        Count >>= 1;
        Shift++;
    }
    return new UnkType_10ffc860(First, Second, Shift);
}
