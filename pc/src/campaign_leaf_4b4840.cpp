// campaign_leaf_4b4840.cpp -- one function at file offset 0x4b4840, preferred VA 0x10db4840.
// It copies Text into the wide string at offset 4 with the cdecl function at 0x10f331b9, or
// empties that string when Text is null. The class, function, method, member and parameter names
// are invented; the offset and the bytes are the binary's.

void Unk_10f331b9(unsigned short* Target, const unsigned short* Text);

class UnkType_10db4840
{
public:
    int unk_0;
    unsigned short unk_4[1];

    void Unk_10db4840(const unsigned short* Text);
};

// UnkType_10db4840::Unk_10db4840
void UnkType_10db4840::Unk_10db4840(const unsigned short* Text)
{
    if ( Text != 0 )
    {
        Unk_10f331b9(unk_4, Text);
    }
    else
    {
        unk_4[0] = 0;
    }
}
