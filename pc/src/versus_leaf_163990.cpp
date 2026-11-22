// versus_leaf_163990.cpp -- whether a node in the chain that starts at the owner's first node has the int value at 0x20, at file offset 0x163990 (VA 0x10a63990).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkNode_10a63990
{
    unsigned char unk_00[0x20];
    int unk_20;                         // compared with the argument by FindUnk20
    unsigned char unk_24[0x28 - 0x24];
    UnkNode_10a63990 *unk_28;                // the next node
};

struct UnkOwner_10a63990
{
    unsigned char unk_00[0x18];
    UnkNode_10a63990 *unk_18;                // the first node
};

class UnkType_10a63990
{
public:
    int FindUnk20(int Value);

private:
    unsigned char unk_00[0xc];          // not read by this function except through the owner
    UnkOwner_10a63990 *unk_0c;
};

// UnkType_10a63990::FindUnk20
int UnkType_10a63990::FindUnk20(int Value)
{
    if ( unk_0c == 0 )
        return 0;
    UnkNode_10a63990 *node = unk_0c->unk_18;
    if ( node == 0 )
        return 0;
    do
    {
        if ( node->unk_20 == Value )
            return 1;
        node = node->unk_28;
    } while ( node != 0 );
    return 0;
}
