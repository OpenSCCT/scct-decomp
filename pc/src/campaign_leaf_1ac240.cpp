// campaign_leaf_1ac240.cpp -- thiscall method at VA 0x10aac240. Given a string, it compares it with
// the string leading each 0x38-byte entry of the array at 0x04 (an empty string standing in for one
// with no characters) through the function at VA 0x10ccae30, and returns the first entry that
// compares equal, or null. The class, method and member names are invented.

int Unk_10ccae30(const unsigned short* First, const unsigned short* Second);

class UnkType_10aac240_String
{
public:
    // UnkType_10aac240_String::operator*
    const unsigned short* operator*() const
    {
        return unk_4 ? unk_0 : L"";
    }

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10aac240_Entry
{
    UnkType_10aac240_String unk_00;
    char unk_0c[0x38 - 0x0c];
};

class UnkType_10aac240
{
public:
    UnkType_10aac240_Entry* Unk_10aac240(const unsigned short* Name);

private:
    int unk_00;
    UnkType_10aac240_Entry* unk_04;
    int unk_08;
};

// UnkType_10aac240::Unk_10aac240
UnkType_10aac240_Entry* UnkType_10aac240::Unk_10aac240(const unsigned short* Name)
{
    for ( int i = 0; i < unk_08; i++ )
    {
        if ( Unk_10ccae30(*unk_04[i].unk_00, Name) == 0 )
        {
            return &unk_04[i];
        }
    }
    return 0;
}
