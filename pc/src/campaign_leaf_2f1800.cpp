// campaign_leaf_2f1800.cpp -- method at VA 0x10bf1800 taking a value and a flag by address: makes
// two function-local static names on first use (L"Activate" and L"Deactivate", through the name
// constructor at VA 0x10cd4790 with 2), then for every set pointer of the array at 0x3fc (count at
// 0x400) calls its method at VA 0x1099a240 with this object, the value and the first name when the
// flag is set or the second otherwise. The class, member and method names are invented; the
// offsets, the strings and the addresses are the binary's.

class UnkType_10bf1800_Name
{
public:
    UnkType_10bf1800_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10bf1800;

class UnkType_10bf1800_Item
{
public:
    void Unk_1099a240(UnkType_10bf1800* Owner, int Value, UnkType_10bf1800_Name Name);
};

class UnkType_10bf1800
{
public:
    void Unk_10bf1800(int Value, const int& Flag);

private:
    unsigned char unk_00[0x3fc];
    UnkType_10bf1800_Item** unk_3fc;
    int unk_400;
};

// UnkType_10bf1800::Unk_10bf1800
void UnkType_10bf1800::Unk_10bf1800(int Value, const int& Flag)
{
    static UnkType_10bf1800_Name Activate(L"Activate", 2);
    static UnkType_10bf1800_Name Deactivate(L"Deactivate", 2);
    for ( int Index = 0; Index < unk_400; Index++ )
    {
        if ( unk_3fc[Index] )
        {
            unk_3fc[Index]->Unk_1099a240(this, Value, Flag ? Activate : Deactivate);
        }
    }
}
