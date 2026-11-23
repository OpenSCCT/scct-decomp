// campaign_leaf_58ae80.cpp -- destructor at VA 0x10e8ae80: installs this class's vtable (VA
// 0x11150320), drops the references held at 0xf4 and 0xf8 (count at 0x06 of each object, deleted
// at zero) and clears them, then runs the base class destructor at VA 0x10e8f020. The class names
// are invented; the addresses are the binary's.

class UnkType_10e8ae80_Item
{
public:
    virtual ~UnkType_10e8ae80_Item();

    // UnkType_10e8ae80_Item::Release
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

class UnkType_10e8ae80_10e8f020
{
public:
    virtual ~UnkType_10e8ae80_10e8f020();

private:
    int unk_04[0xf0 / 4];
};

class UnkType_10e8ae80 : public UnkType_10e8ae80_10e8f020
{
public:
    ~UnkType_10e8ae80();

private:
    UnkType_10e8ae80_Item* unk_f4;
    UnkType_10e8ae80_Item* unk_f8;
};

// UnkType_10e8ae80::~UnkType_10e8ae80
UnkType_10e8ae80::~UnkType_10e8ae80()
{
    if ( unk_f4 )
    {
        unk_f4->Release();
        unk_f4 = 0;
    }
    if ( unk_f8 )
    {
        unk_f8->Release();
        unk_f8 = 0;
    }
}
