// campaign_leaf_3e95f0.cpp -- a member function at VA 0x10ce95f0 taking three arguments: it calls
// virtual slot 6 of its first argument with the second argument. It does not read this or its third
// argument. The class, method and parameter names are invented; the addresses and the slot are the
// binary's.

class UnkType_10ce95f0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(void* Value);
};

class UnkType_10ce95f0
{
public:
    void Unk_10ce95f0(UnkType_10ce95f0_Archive& Ar, void* Value, int MaxBytes);
};

// UnkType_10ce95f0::Unk_10ce95f0
void UnkType_10ce95f0::Unk_10ce95f0(UnkType_10ce95f0_Archive& Ar, void* Value, int MaxBytes)
{
    Ar.VirtualSlot6(Value);
}
