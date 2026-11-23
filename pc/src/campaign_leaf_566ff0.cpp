// campaign_leaf_566ff0.cpp -- function at VA 0x10e66ff0: passes First and Second to the second
// virtual method of every listener in Owner's pointer array at 0xa8 (last first, skipping null
// entries), then removes the null entries from the array, closing each gap. All names are
// invented; the addresses are the binary's.

class UnkType_10e66ff0_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int First, int Second);
};

struct UnkType_10e66ff0_Array
{
    UnkType_10e66ff0_Listener** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e66ff0_Array::Remove
    // guess: removes the entry at Index, moving the later entries down.
    void Remove(int Index)
    {
        unk_04--;
        for ( int Later = Index; Later < unk_04; Later++ )
        {
            unk_00[Later] = unk_00[Later + 1];
        }
    }
};

class UnkType_10e66ff0
{
public:
    int unk_00[0xa8 / 4];
    UnkType_10e66ff0_Array unk_a8;
};

// Unk_10e66ff0
void Unk_10e66ff0(UnkType_10e66ff0* Owner, int First, int Second)
{
    int Index;

    for ( Index = Owner->unk_a8.unk_04 - 1; Index >= 0; Index-- )
    {
        UnkType_10e66ff0_Listener* Listener = Owner->unk_a8.unk_00[Index];

        if ( Listener )
        {
            Listener->VirtualSlot1(First, Second);
        }
    }
    for ( Index = Owner->unk_a8.unk_04 - 1; Index >= 0; Index-- )
    {
        if ( Owner->unk_a8.unk_00[Index] == 0 )
        {
            Owner->unk_a8.Remove(Index);
        }
    }
}
