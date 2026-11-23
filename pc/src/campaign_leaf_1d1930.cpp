// campaign_leaf_1d1930.cpp -- thiscall method at VA 0x10ad1930. Given a string, it compares it
// with every string in the array of 12-byte strings at 0x28 (an empty string standing in for one
// with no characters) through the function at VA 0x10ccae30, and returns 1 when one compares equal,
// 0 otherwise. The class, method and member names are invented.

int Unk_10ccae30(const unsigned short* First, const unsigned short* Second);

class UnkType_10ad1930_String
{
public:
    // UnkType_10ad1930_String::operator*
    const unsigned short* operator*() const
    {
        return unk_4 ? unk_0 : L"";
    }

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad1930
{
public:
    int Unk_10ad1930(const unsigned short* Name);

private:
    char unk_00[0x28];
    UnkType_10ad1930_String* unk_28;
    int unk_2c;
};

// UnkType_10ad1930::Unk_10ad1930
int UnkType_10ad1930::Unk_10ad1930(const unsigned short* Name)
{
    for ( int i = 0; i < unk_2c; i++ )
    {
        if ( Unk_10ccae30(*unk_28[i], Name) == 0 )
        {
            return 1;
        }
    }
    return 0;
}
