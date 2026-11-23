// campaign_leaf_57fca0.cpp -- thiscall method at VA 0x10e7fca0: walks the array of object pointers
// at 0x104 and returns the first object whose name (member at 0x08) the cdecl function at VA
// 0x10dffc00 reports equal to the name it is given (result 0), or null. guess: a lookup by name
// with a string comparison. The class and method names are invented.

int Unk_10dffc00(const unsigned short* First, const unsigned short* Second);

struct UnkType_10e7fca0_Item
{
    int unk_00;
    int unk_04;
    const unsigned short* unk_08;
};

struct UnkType_10e7fca0_Array
{
    UnkType_10e7fca0_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7fca0_Array::Begin
    UnkType_10e7fca0_Item** Begin()
    {
        return unk_00;
    }

    // UnkType_10e7fca0_Array::End
    UnkType_10e7fca0_Item** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e7fca0
{
public:
    UnkType_10e7fca0_Item* Unk_10e7fca0(const unsigned short* Name);

private:
    int unk_00[65];
    UnkType_10e7fca0_Array unk_104;
};

// UnkType_10e7fca0::Unk_10e7fca0
UnkType_10e7fca0_Item* UnkType_10e7fca0::Unk_10e7fca0(const unsigned short* Name)
{
    for ( UnkType_10e7fca0_Item** Item = unk_104.Begin(); Item < unk_104.End(); Item++ )
    {
        const unsigned short* ItemName = (*Item)->unk_08;
        if ( Unk_10dffc00(ItemName, Name) == 0 )
        {
            return *Item;
        }
    }
    return 0;
}
