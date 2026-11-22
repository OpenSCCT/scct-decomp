// campaign_leaf_194930.cpp -- returns 1 when the argument is this or one of the objects reached
// from this through the pointers at offset 0x28, otherwise 0. File offset 0x194930, VA 0x10a94930.
// The class and method names are invented; the offset is the binary's, and the pointee type is a
// guess.

class UnkNode_10a94930
{
public:
    int UnkMethod_10a94930(UnkNode_10a94930 *Target);

private:
    unsigned char unk_00[0x28];     // not read by this function
    UnkNode_10a94930 *unk_28;       // guess: next object in a chain
};

// UnkNode_10a94930::UnkMethod_10a94930
int UnkNode_10a94930::UnkMethod_10a94930(UnkNode_10a94930 *Target)
{
    UnkNode_10a94930 *node;

    node = this;
    while ( node != 0 )
    {
        if ( node == Target )
        {
            return 1;
        }
        node = node->unk_28;
    }
    return 0;
}
