// campaign_leaf_1f1140.cpp -- function at VA 0x10af1140 with no this pointer. Given a singly linked
// list of key nodes and a key, it returns the list unchanged when a node already holds the key;
// otherwise it pushes a new 8-byte node holding the key in front of the list, allocated from the
// stack allocator at VA 0x1120a99c, and returns it (or null when the allocation fails). The type and
// function names are invented.

#include "campaign_global_1120a99c.h"

struct UnkType_10af1140_Node
{
    int Key;
    UnkType_10af1140_Node* Next;
};

// Unk_10af1140
UnkType_10af1140_Node* Unk_10af1140(UnkType_10af1140_Node* List, int Key)
{
    for ( UnkType_10af1140_Node* Node = List; Node != 0; Node = Node->Next )
    {
        if ( Node->Key == Key )
        {
            return List;
        }
    }
    UnkType_10af1140_Node* Result = new(GUnk_1120a99c) UnkType_10af1140_Node;
    if ( Result != 0 )
    {
        Result->Key = Key;
        Result->Next = List;
        return Result;
    }
    return 0;
}
