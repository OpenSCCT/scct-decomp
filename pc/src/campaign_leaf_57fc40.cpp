// campaign_leaf_57fc40.cpp -- thiscall method at VA 0x10e7fc40: walks the array of object pointers
// at 0x110 and returns the first object whose name (member at 0x08) the cdecl function at VA
// 0x10dffc00 reports equal to the name it is given (result 0), or null. guess: a lookup by name
// with a string comparison. The class and method names are invented.

int Unk_10dffc00(const unsigned short* First, const unsigned short* Second);

struct UnkType_10e7fc40_Item
{
    int unk_00;
    int unk_04;
    const unsigned short* unk_08;
};

struct UnkType_10e7fc40_Array
{
    UnkType_10e7fc40_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7fc40_Array::Begin
    UnkType_10e7fc40_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e7fc40_Array::End
    UnkType_10e7fc40_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e7fc40
{
public:
    UnkType_10e7fc40_Item* Unk_10e7fc40(const unsigned short* Name);

private:
    int unk_00[68];
    UnkType_10e7fc40_Array unk_110;
};

// UnkType_10e7fc40::Unk_10e7fc40
UnkType_10e7fc40_Item* UnkType_10e7fc40::Unk_10e7fc40(const unsigned short* Name)
{
    for ( UnkType_10e7fc40_Item** Item = unk_110.Begin(); Item < unk_110.End(); Item++ )
    {
        const unsigned short* ItemName = (*Item)->unk_08;
        if ( Unk_10dffc00(ItemName, Name) == 0 )
        {
            return *Item;
        }
    }
    return 0;
}
