// versus_leaf_1bfab0.cpp -- returns whether the object or a node linked after it through 0x104 is the
// target, at file offset 0x1bfab0 (VA 0x10abfab0). The class, member and method names are invented; the
// offsets, the argument sizes (ret 0xc) and the return values are the binary's.

class UnkType_10abfab0
{
public:
    int ContainsFrom(UnkType_10abfab0 *Target, int Unused1, int Unused2);

private:
    unsigned char unk_00[0x104];        // not read by this function
    UnkType_10abfab0 *unk_104;          // the next link
};

// UnkType_10abfab0::ContainsFrom
// The two unused arguments are popped with the target (ret 0xc).
int UnkType_10abfab0::ContainsFrom(UnkType_10abfab0 *Target, int Unused1, int Unused2)
{
    UnkType_10abfab0 *node = this;
    if ( node == 0 )
    {
        return 0;
    }
    do
    {
        if ( node == Target )
        {
            return 1;
        }
        node = node->unk_104;
    } while ( node != 0 );
    return 0;
}
