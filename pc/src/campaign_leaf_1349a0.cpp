// campaign_leaf_1349a0.cpp -- returns 1 when its argument is in the range 0xc4 to 0xd7 or in the
// range 0x97 to 0x9a, otherwise 0. File offset 0x1349a0, VA 0x10a349a0. The class and method names
// are invented.

class UnkType_10a349a0
{
public:
    static int UnkStatic_10a349a0(int Value);
};

// UnkType_10a349a0::UnkStatic_10a349a0
int UnkType_10a349a0::UnkStatic_10a349a0(int Value)
{
    if ( Value >= 0xc4 && Value <= 0xd7 )
    {
        return 1;
    }
    if ( Value >= 0x97 && Value <= 0x9a )
    {
        return 1;
    }
    return 0;
}
