// campaign_leaf_1e74b0.cpp -- thiscall method at VA 0x10ae74b0. It allocates a 12-byte node through
// slot 0 of the allocator at VA 0x111c88a0 (tag "new"), stores its argument in the node, appends
// the node to the doubly linked list whose first and last nodes are at 0x04 and 0x08, and calls its
// own virtual slot 1. The class, method and member names are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"

struct UnkType_10ae74b0_Node
{
    UnkType_10ae74b0_Node* Prev;
    UnkType_10ae74b0_Node* Next;
    int Value;
};

class UnkType_10ae74b0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();

    void Unk_10ae74b0(int Value);

private:
    UnkType_10ae74b0_Node* unk_04;
    UnkType_10ae74b0_Node* unk_08;
};

// UnkType_10ae74b0::Unk_10ae74b0
void UnkType_10ae74b0::Unk_10ae74b0(int Value)
{
    UnkType_10ae74b0_Node* Node =
        (UnkType_10ae74b0_Node*)GUnk_111c88a0->Malloc(sizeof(UnkType_10ae74b0_Node), L"new");
    Node->Prev = 0;
    Node->Next = 0;
    Node->Value = Value;
    if ( unk_08 == 0 )
    {
        unk_04 = Node;
        unk_08 = Node;
    }
    else
    {
        unk_08->Next = Node;
        Node->Prev = unk_08;
        unk_08 = Node;
    }
    VirtualSlot1();
}
