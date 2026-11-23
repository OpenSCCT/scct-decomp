// campaign_leaf_753c40.cpp -- one function at file offset 0x753c40, preferred VA 0x11053c40. It
// returns 0xffff unless both of its first two arguments are set. It allocates a 0x64-byte object
// through the allocator at VA 0x10901480 and constructs it with the constructor at VA
// 0x1105f360, and passes all three arguments to the object's method at VA 0x11060ad0; it returns
// 0xffff when either fails, and otherwise adds the object to the global object at VA 0x1132e9e0
// and returns that method's result. The class and function names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_1132e9e0.h"

class UnkType_11053c40
{
public:
    static void* operator new(unsigned int Size);

    UnkType_11053c40();

    int Unk_11060ad0(int First, int Second, int Third);

    unsigned char unk_0[0x64];
};

// Unk_11053c40
int Unk_11053c40(int First, int Second, int Third)
{
    UnkType_11053c40* Created;
    int Result;

    if ( First == 0 || Second == 0 )
    {
        return 0xffff;
    }
    Created = new UnkType_11053c40;
    if ( Created == 0 )
    {
        return 0xffff;
    }
    Result = Created->Unk_11060ad0(First, Second, Third);
    if ( Result == 0xffff )
    {
        return 0xffff;
    }
    GUnk_1132e9e0.Unk_110533e0(Created);
    return Result;
}
