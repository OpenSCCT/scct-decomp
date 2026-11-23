// campaign_leaf_1e9b90.cpp -- stdcall function at VA 0x10ae9b90. Given an object and a string, it
// returns the index of the first 16-byte entry of the object's array at 0xac whose leading string
// compares equal to the given one through the function at VA 0x10ccae30 (an empty string standing
// in for one with no characters), or -1. The type and function names are invented.

int Unk_10ccae30(const unsigned short* First, const unsigned short* Second);

class UnkType_10ae9b90_String
{
public:
    // UnkType_10ae9b90_String::operator*
    const unsigned short* operator*() const
    {
        return unk_4 ? unk_0 : L"";
    }

    // UnkType_10ae9b90_String::operator==
    bool operator==(const UnkType_10ae9b90_String& Other) const
    {
        return Unk_10ccae30(**this, *Other) == 0;
    }

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10ae9b90_Entry
{
    UnkType_10ae9b90_String unk_0;
    int unk_c;
};

struct UnkType_10ae9b90_Owner
{
    char unk_00[0xac];
    UnkType_10ae9b90_Entry* unk_ac;
    int unk_b0;
};

// Unk_10ae9b90
int __stdcall Unk_10ae9b90(UnkType_10ae9b90_Owner* Owner, const UnkType_10ae9b90_String& Name)
{
    for ( int i = 0; i < Owner->unk_b0; i++ )
    {
        if ( Owner->unk_ac[i].unk_0 == Name )
        {
            return i;
        }
    }
    return -1;
}
