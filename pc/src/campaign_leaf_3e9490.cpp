// campaign_leaf_3e9490.cpp -- a member function at VA 0x10ce9490 taking three arguments: it calls
// virtual slot 1 of its first argument with the second argument and the length 4. It does not read
// this or its third argument. guess: a property class serializing a 4-byte value through an
// archive. The class, method and parameter names are invented; the addresses, the slot and the
// length are the binary's.

class UnkType_10ce9490_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void Unk_Slot1(void* Data, int Length);
};

class UnkType_10ce9490
{
public:
    void Unk_10ce9490(UnkType_10ce9490_Archive& Ar, void* Value, int MaxBytes);
};

// UnkType_10ce9490::Unk_10ce9490
void UnkType_10ce9490::Unk_10ce9490(UnkType_10ce9490_Archive& Ar, void* Value, int MaxBytes)
{
    Ar.Unk_Slot1(Value, 4);
}
