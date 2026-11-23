// campaign_leaf_2c4670.cpp -- method at VA 0x10bc4670 of an array (data pointer, count) of 12-byte
// strings, taking a string: returns the index of the first element the function at VA 0x10ccae30
// reports equal to it (each string read as its characters, or L"" when its count is zero), or -1.
// The class, member and method names are invented; the offsets and the address are the binary's.

int Unk_10ccae30(const unsigned short* First, const unsigned short* Second);

class UnkType_10bc4670_String
{
public:
    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bc4670
{
public:
    int Unk_10bc4670(const UnkType_10bc4670_String& Text);

private:
    UnkType_10bc4670_String* unk_00;
    int unk_04;
};

// UnkType_10bc4670::Unk_10bc4670
int UnkType_10bc4670::Unk_10bc4670(const UnkType_10bc4670_String& Text)
{
    for ( int Index = 0; Index < unk_04; Index++ )
    {
        const UnkType_10bc4670_String& Entry = unk_00[Index];
        if ( !Unk_10ccae30(*Entry, *Text) )
        {
            return Index;
        }
    }
    return -1;
}
