// campaign_leaf_538360.cpp -- thiscall method at VA 0x10e38360: stores the object it is given in
// every cell of one row and one column (both chosen by the index it is given) of the 8 by 8 grid of
// reference-counted object pointers at 0x0c, taking a reference for each store and dropping the
// one held by the replaced object (count at 0x06, deleted at zero). All names are invented.

class UnkType_10e38360_Item
{
public:
    virtual ~UnkType_10e38360_Item();

    // UnkType_10e38360_Item::AddRef
    void AddRef()
    {
        unk_06++;
    }

    // UnkType_10e38360_Item::Release
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
};

class UnkType_10e38360
{
public:
    void Unk_10e38360(UnkType_10e38360_Item* Item, int Index);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e38360_Item* unk_0c[8][8];
};

// UnkType_10e38360::Unk_10e38360
void UnkType_10e38360::Unk_10e38360(UnkType_10e38360_Item* Item, int Index)
{
    for ( int Other = 0; Other < 8; Other++ )
    {
        Item->AddRef();
        unk_0c[Other][Index]->Release();
        unk_0c[Other][Index] = Item;
        Item->AddRef();
        unk_0c[Index][Other]->Release();
        unk_0c[Index][Other] = Item;
    }
}
