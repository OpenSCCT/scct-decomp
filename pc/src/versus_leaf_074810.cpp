// versus_leaf_074810.cpp -- one function at file offset 0x74810, preferred VA 0x10974810.
// It walks the class chain of its object: the first node is at +0x24 and each node links to
// the next at +0x28. It returns the object when the chain reaches the class object at VA
// 0x10cbd8c8, and 0 otherwise. It takes the object in EAX and returns it in EAX, which the
// link chooses from the callers. The class, member and function names are invented; the offsets
// and the bytes are the binary's.

#include "versus_leaf_074810.h"

/*
================
Unk_74810

Returns the object if its class chain at +0x24 reaches Unk_10cbd8c8, else 0.
================
*/
__declspec(noinline) UnkType_74810_Object *Unk_74810(UnkType_74810_Object *Object)
{
    UnkType_74810_Class *Node;

    if (Object == 0)
        return 0;
    Node = Object->unk_24;
    while (Node != 0)
    {
        if (Node == &Unk_10cbd8c8)
            return Object;
        Node = Node->unk_28;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
UnkType_74810_Object *Driver_74810(UnkType_74810_Object *Object)
{
    return Unk_74810(Object);
}
