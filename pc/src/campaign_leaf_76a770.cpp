// campaign_leaf_76a770.cpp -- one function at file offset 0x76a770, preferred VA 0x1106a770. It
// allocates a 0x5c-byte object through the allocator at VA 0x1105ee10 and constructs it with the
// constructor at VA 0x1106a6f0; it returns -1 when that fails, and otherwise stores the object
// through its argument and returns 0. The class and function names are invented; the offset and
// the addresses are the binary's.

class UnkType_1106a770
{
public:
    static void* operator new(unsigned int Size);

    UnkType_1106a770();

    unsigned char unk_0[0x5c];
};

// Unk_1106a770
int Unk_1106a770(UnkType_1106a770** Object)
{
    UnkType_1106a770* Created;

    Created = new UnkType_1106a770;
    if ( Created == 0 )
    {
        return -1;
    }
    *Object = Created;
    return 0;
}
