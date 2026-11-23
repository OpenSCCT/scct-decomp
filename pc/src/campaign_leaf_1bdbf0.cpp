// campaign_leaf_1bdbf0.cpp -- method at VA 0x10abdbf0: in the table of up to 16 key and float
// pairs at 0x0, with its count at 0x80, lowers the float of Key to Value when Key is present and
// otherwise appends the pair while there is room. The class, member, method and parameter names
// are invented; the offsets and the constant are the binary's.

class UnkType_10abdbf0_Entry
{
public:
    int unk_0;
    float unk_4;
};

class UnkType_10abdbf0
{
public:
    void Unk_10abdbf0(int Key, float Value);

private:
    UnkType_10abdbf0_Entry unk_0[16];
    int unk_80;
};

// UnkType_10abdbf0::Unk_10abdbf0
void UnkType_10abdbf0::Unk_10abdbf0(int Key, float Value)
{
    int i;

    for ( i = 0; i < unk_80; i++ )
    {
        if ( unk_0[i].unk_0 == Key )
        {
            float Old = unk_0[i].unk_4;

            unk_0[i].unk_4 = Old <= Value ? Old : Value;
            return;
        }
    }
    if ( unk_80 != 16 )
    {
        unk_0[unk_80].unk_0 = Key;
        unk_0[unk_80].unk_4 = Value;
        unk_80++;
    }
}
