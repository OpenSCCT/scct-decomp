// campaign_leaf_067e20.cpp -- free function at VA 0x10967e20: calls virtual slot 1 (vtable offset
// 0x04) of the object its first argument refers to with the address of its second argument and the
// size 2, and returns the first argument. The class and function names are invented; the slot and
// the size are the binary's.

class UnkType_10967e20
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

// Unk_10967e20
UnkType_10967e20& Unk_10967e20(UnkType_10967e20& Target, unsigned short& Value)
{
    Target.VirtualSlot1(&Value, 2);
    return Target;
}
