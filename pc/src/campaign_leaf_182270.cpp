// campaign_leaf_182270.cpp -- returns 1 when the argument is this or one of the objects reached
// from this through the pointers at offset 0xa8, otherwise 0. File offset 0x182270, VA 0x10a82270.
// The class and method names are invented; the offset is the binary's, and the pointee type is a
// guess.

class UnkNode_10a82270
{
public:
    int UnkMethod_10a82270(UnkNode_10a82270 *Target);

private:
    unsigned char unk_00[0xa8];     // not read by this function
    UnkNode_10a82270 *unk_a8;       // guess: next object in a chain
};

// UnkNode_10a82270::UnkMethod_10a82270
int UnkNode_10a82270::UnkMethod_10a82270(UnkNode_10a82270 *Target)
{
    UnkNode_10a82270 *node;

    node = this;
    while ( node != 0 )
    {
        if ( node == Target )
        {
            return 1;
        }
        node = node->unk_a8;
    }
    return 0;
}
