// versus_leaf_25bd00.cpp -- clears the byte and the int at 4 of the node at 0 and points its two links at it, at file offset 0x25bd00 (VA 0x10b5bd00).
// The class, member, argument and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

struct UnkNode_10b5bd00
{
    unsigned char unk_00;               // cleared by InitNode
    unsigned char unk_01[0x4 - 0x1];
    int unk_04;                         // cleared by InitNode
    UnkNode_10b5bd00 *unk_08;                // set to the node by InitNode
    UnkNode_10b5bd00 *unk_0c;                // set to the node by InitNode
};

class UnkType_10b5bd00
{
public:
    void InitNode();

private:
    UnkNode_10b5bd00 *unk_00;                // the node
};

// UnkType_10b5bd00::InitNode
void UnkType_10b5bd00::InitNode()
{
    unk_00->unk_00 = 0;
    unk_00->unk_04 = 0;
    unk_00->unk_08 = unk_00;
    unk_00->unk_0c = unk_00;
}
