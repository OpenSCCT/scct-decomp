// campaign_leaf_067e40.cpp -- free function at VA 0x10967e40: calls virtual slot 1 (vtable offset
// 0x04) of the object its first argument refers to with the address of its second argument and the
// size 4, and returns the first argument. The class and function names are invented; the slot and
// the size are the binary's.

class UnkType_10967e40
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

// Unk_10967e40
UnkType_10967e40& Unk_10967e40(UnkType_10967e40& Target, int& Value)
{
    Target.VirtualSlot1(&Value, 4);
    return Target;
}
