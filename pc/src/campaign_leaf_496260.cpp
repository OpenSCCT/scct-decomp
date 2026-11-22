// campaign_leaf_496260.cpp -- free function at VA 0x10d96260: passes its argument to the second
// virtual method of the object the global at VA 0x1131a6b8 points to, and returns the argument.
// All names are invented.

class UnkType_1131a6b8
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Value);
};

extern UnkType_1131a6b8* GUnk_1131a6b8;

// Unk_10d96260
void* Unk_10d96260(void* Value)
{
    GUnk_1131a6b8->VirtualSlot1(Value);
    return Value;
}
