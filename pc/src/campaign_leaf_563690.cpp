// campaign_leaf_563690.cpp -- function at VA 0x10e63690: passes Owner to the third virtual method
// of every listener in Owner's pointer array at 0x7c (last first), and of the listener object at
// 0x08 of every entry in the pointer arrays at 0x88 and 0x94 (first first), skipping null entries.
// All names are invented; the addresses are the binary's.

class UnkType_10e63690;

class UnkType_10e63690_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10e63690* Owner);
};

struct UnkType_10e63690_Entry
{
    int unk_00;
    int unk_04;
    UnkType_10e63690_Listener unk_08;
};

class UnkType_10e63690
{
public:
    int unk_00[0x7c / 4];
    UnkType_10e63690_Listener** unk_7c;
    int unk_80;
    int unk_84;
    UnkType_10e63690_Entry** unk_88;
    int unk_8c;
    int unk_90;
    UnkType_10e63690_Entry** unk_94;
    int unk_98;
};

// Unk_10e63690
void Unk_10e63690(UnkType_10e63690* Owner)
{
    int Index;

    for ( Index = Owner->unk_80 - 1; Index >= 0; Index-- )
    {
        UnkType_10e63690_Listener* Listener = Owner->unk_7c[Index];

        if ( Listener )
        {
            Listener->VirtualSlot2(Owner);
        }
    }
    for ( Index = 0; Index < Owner->unk_8c; Index++ )
    {
        UnkType_10e63690_Entry* Entry = Owner->unk_88[Index];

        if ( Entry )
        {
            Entry->unk_08.VirtualSlot2(Owner);
        }
    }
    for ( Index = 0; Index < Owner->unk_98; Index++ )
    {
        UnkType_10e63690_Entry* Entry = Owner->unk_94[Index];

        if ( Entry )
        {
            Entry->unk_08.VirtualSlot2(Owner);
        }
    }
}
