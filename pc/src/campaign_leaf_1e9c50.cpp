// campaign_leaf_1e9c50.cpp -- thiscall method at VA 0x10ae9c50. Given a string and a pointer to an
// index, it walks the index over the array of 12-byte entries, each beginning with a string, and
// returns 1 with the index left on the first entry whose string compares equal to the given one
// through the function at VA 0x10ccae30 (an empty string standing in for one with no characters),
// 0 when none does. The class, method and member names are invented.

int Unk_10ccae30(const unsigned short* First, const unsigned short* Second);

class UnkType_10ae9c50_String
{
public:
    // UnkType_10ae9c50_String::operator*
    const unsigned short* operator*() const
    {
        return unk_4 ? unk_0 : L"";
    }

    // UnkType_10ae9c50_String::operator==
    bool operator==(const UnkType_10ae9c50_String& Other) const
    {
        return Unk_10ccae30(**this, *Other) == 0;
    }

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ae9c50
{
public:
    int Unk_10ae9c50(const UnkType_10ae9c50_String& Name, int* Index);

private:
    UnkType_10ae9c50_String* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10ae9c50::Unk_10ae9c50
int UnkType_10ae9c50::Unk_10ae9c50(const UnkType_10ae9c50_String& Name, int* Index)
{
    for ( *Index = 0; *Index < unk_4; (*Index)++ )
    {
        if ( unk_0[*Index] == Name )
        {
            return 1;
        }
    }
    return 0;
}
