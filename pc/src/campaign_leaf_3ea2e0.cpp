// campaign_leaf_3ea2e0.cpp -- a member function at VA 0x10cea2e0 taking three arguments: it calls
// virtual slot 1 of its first argument with the second argument and the length 1. It does not read
// this or its third argument. guess: a property class serializing a 1-byte value through an
// archive. The class, method and parameter names are invented; the addresses, the slot and the
// length are the binary's.

class UnkType_10cea2e0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void Unk_Slot1(void* Data, int Length);
};

class UnkType_10cea2e0
{
public:
    void Unk_10cea2e0(UnkType_10cea2e0_Archive& Ar, void* Value, int MaxBytes);
};

// UnkType_10cea2e0::Unk_10cea2e0
void UnkType_10cea2e0::Unk_10cea2e0(UnkType_10cea2e0_Archive& Ar, void* Value, int MaxBytes)
{
    Ar.Unk_Slot1(Value, 1);
}
