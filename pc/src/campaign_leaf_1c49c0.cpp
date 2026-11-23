// campaign_leaf_1c49c0.cpp -- method at VA 0x10ac49c0: inserts Value with Key into the table of up
// to 32 values at 0x0 kept in ascending order of their keys at 0x80 (count at 0x100), starting the
// search from a half or quarter of the count, and shifts the later entries up. The class, member,
// method, parameter and local names are invented; the offsets and the constants are the binary's.

class UnkType_10ac49c0
{
public:
    void Unk_10ac49c0(int Value, int Key);

private:
    int unk_0[32];
    int unk_80[32];
    int unk_100;
};

// UnkType_10ac49c0::Unk_10ac49c0
void UnkType_10ac49c0::Unk_10ac49c0(int Value, int Key)
{
    int i = 0;

    if ( unk_100 > 8 )
    {
        if ( Key > unk_80[unk_100 / 2] )
        {
            i = unk_100 / 2;
            if ( unk_100 > 16 && Key > unk_80[i + unk_100 / 4] )
            {
                i += unk_100 / 4;
            }
        }
        else if ( unk_100 > 16 && Key > unk_80[unk_100 / 4] )
        {
            i = unk_100 / 4;
        }
    }
    while ( i < unk_100 && Key > unk_80[i] )
    {
        i++;
    }
    if ( i < 32 )
    {
        int MovedValue = unk_0[i];
        float MovedKey = unk_80[i];

        unk_0[i] = Value;
        unk_80[i] = Key;
        if ( unk_100 < 32 )
        {
            unk_100++;
        }
        for ( i++; i < unk_100; i++ )
        {
            int NextValue = unk_0[i];
            float NextKey = unk_80[i];

            unk_0[i] = MovedValue;
            unk_80[i] = (int)MovedKey;
            MovedValue = NextValue;
            MovedKey = NextKey;
        }
    }
}
