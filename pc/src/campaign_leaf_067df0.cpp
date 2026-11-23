// campaign_leaf_067df0.cpp -- method at VA 0x10967df0: calls virtual slot 1 (vtable offset 0x04) on
// the same object with its two arguments and returns the object. The class and method names are
// invented; the slot is the binary's.

class UnkType_10967df0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);

    UnkType_10967df0& Unk_10967df0(void* Data, int Size);
};

// UnkType_10967df0::Unk_10967df0
UnkType_10967df0& UnkType_10967df0::Unk_10967df0(void* Data, int Size)
{
    VirtualSlot1(Data, Size);
    return *this;
}
