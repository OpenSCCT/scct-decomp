// campaign_leaf_323d60.cpp -- a member function at VA 0x10c23d60: when the int at 0x2c of the
// object the pointer at 0x28 refers to is zero, it passes that pointer to the member at VA
// 0x10aa8370 of the object the pointer at 0x34 refers to and clears the pointer at 0x28. The class,
// method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10c23d60_Item
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
};

class UnkType_10aa8370
{
public:
    void Unk_10aa8370(UnkType_10c23d60_Item* Item);
};

class UnkType_10c23d60
{
public:
    void Unk_10c23d60();

private:
    unsigned char unk_00[0x28];
    UnkType_10c23d60_Item* unk_28;
    int unk_2c;
    int unk_30;
    UnkType_10aa8370* unk_34;
};

// UnkType_10c23d60::Unk_10c23d60
void UnkType_10c23d60::Unk_10c23d60()
{
    if ( !unk_28->unk_2c )
    {
        unk_34->Unk_10aa8370(unk_28);
        unk_28 = 0;
    }
}
