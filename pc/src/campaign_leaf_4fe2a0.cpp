// campaign_leaf_4fe2a0.cpp -- method at VA 0x10dfe2a0: searches its array of twelve-byte pairs for
// a key whose second word equals the argument's and whose first word compares equal through the
// function at VA 0x10dffc60, and returns the address of that pair's value, or null. The class,
// method and member names are invented; the offsets and the address are the binary's.

class UnkType_10dfe2a0_Key
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10dfe2a0_Pair
{
public:
    UnkType_10dfe2a0_Key Key;
    int Value;
};

int Unk_10dffc60(int Left, int Right);

class UnkType_10dfe2a0
{
public:
    int* Unk_10dfe2a0(const UnkType_10dfe2a0_Key& Key);

    UnkType_10dfe2a0_Pair* Data;
    int Num;
};

// UnkType_10dfe2a0::Unk_10dfe2a0
int* UnkType_10dfe2a0::Unk_10dfe2a0(const UnkType_10dfe2a0_Key& Key)
{
    for ( int i = 0; i < Num; i++ )
    {
        if ( Data[i].Key.unk_04 == Key.unk_04 && Unk_10dffc60(Data[i].Key.unk_00, Key.unk_00) == 0 )
        {
            return &Data[i].Value;
        }
    }
    return 0;
}
