// campaign_leaf_072360.cpp -- free function at VA 0x10972360: calls virtual slot 1 (vtable offset
// 0x04) of the object its first argument refers to with the address of its second argument and the
// size 1, and returns the first argument. The class and function names are invented; the slot and
// the size are the binary's.

class UnkType_10972360
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

// Unk_10972360
UnkType_10972360& Unk_10972360(UnkType_10972360& Target, unsigned char& Value)
{
    Target.VirtualSlot1(&Value, 1);
    return Target;
}
