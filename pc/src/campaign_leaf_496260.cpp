// campaign_leaf_496260.cpp -- free function at VA 0x10d96260: passes its argument to the second
// virtual method of the object the global at VA 0x1131a6b8 points to, and returns the argument.
// All names are invented.

#include "campaign_global_1131a6b8.h"

// Unk_10d96260
void* Unk_10d96260(void* Value)
{
    GUnk_1131a6b8->VirtualSlot1(Value);
    return Value;
}
