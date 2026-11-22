// versus_leaf_0746e0.cpp -- one function at file offset 0x746e0, preferred VA 0x109746e0.
// It walks the class chain of its object: the first node is at +0x24 and each node links to
// the next at +0x28. It returns the object when the chain reaches the class object at VA
// 0x10cc3638, and 0 otherwise. It takes the object in EAX and returns it in EAX, which the
// link chooses from the callers. The class, member and function names are invented; the offsets
// and the bytes are the binary's.

#include "versus_leaf_0746e0.h"

/*
================
Unk_746e0

Returns the object if its class chain at +0x24 reaches Unk_10cc3638, else 0.
================
*/
__declspec(noinline) UnkType_746e0_Object *Unk_746e0(UnkType_746e0_Object *Object)
{
    UnkType_746e0_Class *Node;

    if (Object == 0)
        return 0;
    Node = Object->unk_24;
    while (Node != 0)
    {
        if (Node == &Unk_10cc3638)
            return Object;
        Node = Node->unk_28;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
UnkType_746e0_Object *Driver_746e0(UnkType_746e0_Object *Object)
{
    return Unk_746e0(Object);
}
