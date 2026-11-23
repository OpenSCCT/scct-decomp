// campaign_leaf_4fe760.cpp -- method at VA 0x10dfe760: searches its array of twelve-byte pairs from
// the end for a key whose second word equals the argument's and whose first word compares equal
// through the function at VA 0x10dffc60; moves the last pair into its place, shortens the array and
// returns 0, or returns 1 when none matches. The class, method and member names are invented; the
// offsets and the address are the binary's.

class UnkType_10dfe760_Key
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10dfe760_Pair
{
public:
    UnkType_10dfe760_Key Key;
    int Value;
};

int Unk_10dffc60(int Left, int Right);

class UnkType_10dfe760
{
public:
    int Unk_10dfe760(const UnkType_10dfe760_Key& Key);

    UnkType_10dfe760_Pair* Data;
    int Num;
};

// UnkType_10dfe760::Unk_10dfe760
int UnkType_10dfe760::Unk_10dfe760(const UnkType_10dfe760_Key& Key)
{
    for ( int i = Num - 1; i >= 0; i-- )
    {
        if ( Data[i].Key.unk_04 == Key.unk_04 && Unk_10dffc60(Data[i].Key.unk_00, Key.unk_00) == 0 )
        {
            Num--;
            Data[i] = Data[Num];
            return 0;
        }
    }
    return 1;
}
