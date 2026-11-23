// campaign_leaf_554280.cpp -- thiscall method at VA 0x10e54280: for every object in the pointer
// array at 0x108 (count at 0x10c), passes its member at 0x44 to the method at VA 0x10e540d0 when
// that member is set and its byte at 0x29 is nonzero, then drops one reference to the object
// (count at 0x06, deleted at zero); finally empties the array. All names are invented.

struct UnkType_10e54280_Owner
{
    int unk_00[10];
    char unk_28;
    char unk_29;
};

class UnkType_10e54280_Item
{
public:
    virtual ~UnkType_10e54280_Item();

    // UnkType_10e54280_Item::Release
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
    int unk_08[15];
    UnkType_10e54280_Owner* unk_44;
};

class UnkType_10e54280
{
public:
    void Unk_10e540d0(UnkType_10e54280_Owner* Owner);
    void Unk_10e54280();

private:
    int unk_00[0x108 / 4];
    UnkType_10e54280_Item** unk_108;
    int unk_10c;
};

// UnkType_10e54280::Unk_10e54280
void UnkType_10e54280::Unk_10e54280()
{
    for ( int Index = 0; Index < unk_10c; Index++ )
    {
        UnkType_10e54280_Owner* Owner = unk_108[Index]->unk_44;
        if ( Owner && Owner->unk_29 )
        {
            Unk_10e540d0(Owner);
        }
        unk_108[Index]->Release();
    }
    unk_10c = 0;
}
