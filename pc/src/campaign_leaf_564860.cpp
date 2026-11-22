// campaign_leaf_564860.cpp -- one function at file offset 0x564860, preferred VA 0x10e64860.
// It finds Item in the pointer array at offset 0x4c (count at offset 0x50), removes it by
// shifting the later entries down, clears the item's int at offset 0x10 and sets the byte at
// offset 0x28. An absent item gives index -1. The class, structure, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_10e64860_Item
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

struct UnkType_10e64860_Array
{
    UnkType_10e64860_Item** Data;
    int Num;

    int FindIndex(UnkType_10e64860_Item* Item) const
    {
        int i;

        for ( i = 0; i < Num; i++ )
        {
            if ( Data[i] == Item )
            {
                return i;
            }
        }
        return -1;
    }

    void RemoveAt(int Index)
    {
        int i;

        Num--;
        for ( i = Index; i < Num; i++ )
        {
            Data[i] = Data[i + 1];
        }
    }
};

class UnkType_10e64860
{
public:
    unsigned char unk_0[0x28];
    bool unk_28;
    unsigned char unk_29[0x23];
    UnkType_10e64860_Array unk_4c;

    void Unk_10e64860(UnkType_10e64860_Item* Item);
};

// UnkType_10e64860::Unk_10e64860
void UnkType_10e64860::Unk_10e64860(UnkType_10e64860_Item* Item)
{
    unk_4c.RemoveAt(unk_4c.FindIndex(Item));
    Item->unk_10 = 0;
    unk_28 = true;
}
