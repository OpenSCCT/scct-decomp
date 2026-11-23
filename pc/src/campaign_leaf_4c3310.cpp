// campaign_leaf_4c3310.cpp -- one function at file offset 0x4c3310, preferred VA 0x10dc3310.
// It deletes the object at offset 0, if any, through its destructor at 0x10d963c0 and the
// operator delete at 0x10d87b90. The class, method and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10dc3310_Item
{
public:
    int unk_0;

    ~UnkType_10dc3310_Item();
};

class UnkType_10dc3310
{
public:
    UnkType_10dc3310_Item* unk_0;

    void Unk_10dc3310();
};

// UnkType_10dc3310::Unk_10dc3310
void UnkType_10dc3310::Unk_10dc3310()
{
    if ( unk_0 != 0 )
    {
        delete unk_0;
    }
}
