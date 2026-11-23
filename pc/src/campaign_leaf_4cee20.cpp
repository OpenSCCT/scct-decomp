// campaign_leaf_4cee20.cpp -- one function at file offset 0x4cee20, preferred VA 0x10dcee20.
// It deletes Item, if any, through its destructor at 0x10d91520 and the operator delete at
// 0x10d87b90. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10dcee20_Item
{
public:
    int unk_0;

    ~UnkType_10dcee20_Item();
};

class UnkType_10dcee20
{
public:
    void Unk_10dcee20(UnkType_10dcee20_Item* Item);
};

// UnkType_10dcee20::Unk_10dcee20
void UnkType_10dcee20::Unk_10dcee20(UnkType_10dcee20_Item* Item)
{
    if ( Item != 0 )
    {
        delete Item;
    }
}
