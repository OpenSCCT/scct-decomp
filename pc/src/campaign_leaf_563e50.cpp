// campaign_leaf_563e50.cpp -- thiscall method at VA 0x10e63e50: removes Item from the pointer
// array at 0x58 (closing the gap), has Item fill in a record of four words through its eleventh
// virtual method, passes Item and the record to this object's fourth virtual method, sets the byte
// at 0x28, clears Item's word at 0x14 and drops one reference to Item (the word at 6), deleting it
// when none is left. All names are invented; the addresses are the binary's.

struct UnkType_10e63e50_Record
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10e63e50_Item
{
public:
    virtual ~UnkType_10e63e50_Item();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10(UnkType_10e63e50_Record* Record);

    // UnkType_10e63e50_Item::Release
    // guess: drops one reference and deletes the item when none is left.
    void Release()
    {
        unk_06--;
        if ( unk_06 == 0 )
        {
            delete this;
        }
    }

    short unk_04;
    short unk_06;
    int unk_08[3];
    int unk_14;
};

struct UnkType_10e63e50_Array
{
    UnkType_10e63e50_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e63e50_Array::Find
    // guess: returns the index of Item, or -1.
    int Find(UnkType_10e63e50_Item* Item)
    {
        for ( int Index = 0; Index < unk_04; Index++ )
        {
            if ( unk_00[Index] == Item )
            {
                return Index;
            }
        }
        return -1;
    }

    // UnkType_10e63e50_Array::Remove
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

class UnkType_10e63e50
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(UnkType_10e63e50_Item* Item, UnkType_10e63e50_Record* Record);

    void Unk_10e63e50(UnkType_10e63e50_Item* Item);

private:
    int unk_04[9];
    unsigned char unk_28;
    int unk_2c[11];
    UnkType_10e63e50_Array unk_58;
};

// UnkType_10e63e50::Unk_10e63e50
void UnkType_10e63e50::Unk_10e63e50(UnkType_10e63e50_Item* Item)
{
    UnkType_10e63e50_Record Record;

    unk_58.Remove(unk_58.Find(Item));
    Item->VirtualSlot10(&Record);
    VirtualSlot3(Item, &Record);
    unk_28 = 1;
    Item->unk_14 = 0;
    Item->Release();
}
