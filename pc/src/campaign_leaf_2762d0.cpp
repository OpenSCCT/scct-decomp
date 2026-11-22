// campaign_leaf_2762d0.cpp -- a member function at VA 0x10b762d0 that stores this in the pointer at
// 0x08 of the object its argument points to and passes a reference to the argument to the member at
// VA 0x10b761c0 of the object at 0x04. The class, method and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10b762d0;

class UnkType_10b762d0_Item
{
public:
    int unk_00;
    int unk_04;
    UnkType_10b762d0* unk_08;
};

class UnkType_10b761c0
{
public:
    void Unk_10b761c0(UnkType_10b762d0_Item* const& Item);
};

class UnkType_10b762d0
{
public:
    void Unk_10b762d0(UnkType_10b762d0_Item* Item);

private:
    int unk_00;
    UnkType_10b761c0 unk_04;
};

// UnkType_10b762d0::Unk_10b762d0
void UnkType_10b762d0::Unk_10b762d0(UnkType_10b762d0_Item* Item)
{
    Item->unk_08 = this;
    unk_04.Unk_10b761c0(Item);
}
