// campaign_leaf_61ce20.cpp -- thiscall method at VA 0x10f1ce20 taking a character and a second
// argument it does not read: for '&' it sets the member at 0x74 to 3, otherwise it calls the method
// at VA 0x10f1ce40. The class and method names are invented.

class UnkType_10f1ce20
{
public:
    void Unk_10f1ce40();
    void Unk_10f1ce20(char Character, int Unused);

private:
    int unk_00[29];
    int unk_74;
};

// UnkType_10f1ce20::Unk_10f1ce20
void UnkType_10f1ce20::Unk_10f1ce20(char Character, int Unused)
{
    if ( Character == '&' )
    {
        unk_74 = 3;
    }
    else
    {
        Unk_10f1ce40();
    }
}
