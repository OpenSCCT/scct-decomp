// campaign_leaf_212f30.cpp -- a member function at VA 0x10b12f30 that deletes the object the
// pointer at 0x04 refers to, through its virtual destructor, and clears the pointer. The class,
// method and member names are invented; the offsets are the binary's.

class UnkType_10b12f30_Item
{
public:
    virtual ~UnkType_10b12f30_Item();
};

class UnkType_10b12f30
{
public:
    void Unk_10b12f30();

private:
    int unk_00;
    UnkType_10b12f30_Item* unk_04;
};

// UnkType_10b12f30::Unk_10b12f30
void UnkType_10b12f30::Unk_10b12f30()
{
    delete unk_04;
    unk_04 = 0;
}
