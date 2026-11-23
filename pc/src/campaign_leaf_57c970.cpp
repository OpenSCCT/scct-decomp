// campaign_leaf_57c970.cpp -- thiscall method at VA 0x10e7c970: walks the array of object pointers
// at 0xec and returns the first object whose name (member at 0x08) the cdecl function at VA
// 0x10dffc00 reports equal to the name it is given (result 0), or null. guess: a lookup by name
// with a string comparison. The class and method names are invented.

int Unk_10dffc00(const unsigned short* First, const unsigned short* Second);

struct UnkType_10e7c970_Item
{
    int unk_00;
    int unk_04;
    const unsigned short* unk_08;
};

struct UnkType_10e7c970_Array
{
    UnkType_10e7c970_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7c970_Array::Begin
    UnkType_10e7c970_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e7c970_Array::End
    UnkType_10e7c970_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e7c970
{
public:
    UnkType_10e7c970_Item* Unk_10e7c970(const unsigned short* Name);

private:
    int unk_00[59];
    UnkType_10e7c970_Array unk_ec;
};

// UnkType_10e7c970::Unk_10e7c970
UnkType_10e7c970_Item* UnkType_10e7c970::Unk_10e7c970(const unsigned short* Name)
{
    for ( UnkType_10e7c970_Item** Item = unk_ec.Begin(); Item < unk_ec.End(); Item++ )
    {
        const unsigned short* ItemName = (*Item)->unk_08;
        if ( Unk_10dffc00(ItemName, Name) == 0 )
        {
            return *Item;
        }
    }
    return 0;
}
