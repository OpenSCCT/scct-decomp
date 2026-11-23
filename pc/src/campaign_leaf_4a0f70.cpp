// campaign_leaf_4a0f70.cpp -- one function at file offset 0x4a0f70, preferred VA 0x10da0f70.
// It deletes the object at offset 0x20 through its virtual destructor and stores Item there. The
// class, method, member and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10da0f70_Item
{
public:
    virtual ~UnkType_10da0f70_Item();
};

class UnkType_10da0f70
{
public:
    unsigned char unk_0[0x20];
    UnkType_10da0f70_Item* unk_20;

    void Unk_10da0f70(UnkType_10da0f70_Item* Item);
};

// UnkType_10da0f70::Unk_10da0f70
void UnkType_10da0f70::Unk_10da0f70(UnkType_10da0f70_Item* Item)
{
    delete unk_20;
    unk_20 = Item;
}
