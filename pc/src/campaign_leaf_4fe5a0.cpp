// campaign_leaf_4fe5a0.cpp -- method at VA 0x10dfe5a0: returns the address of the value paired with
// its key in this array of twelve-byte pairs (a key matches when its second word is equal and its
// first word compares equal through the function at VA 0x10dffc60), appending a new pair for the
// key (growing through the function at VA 0x10dfc3c0) when none matches. The class, method and
// member names are invented; the address is the binary's.

class UnkType_10dfe5a0;

void Unk_10dfc3c0(UnkType_10dfe5a0* Array, int NewMax, int ElementSize);
int Unk_10dffc60(int Left, int Right);

class UnkType_10dfe5a0_Key
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10dfe5a0_Pair
{
public:
    UnkType_10dfe5a0_Key Key;
    int Value;
};

class UnkType_10dfe5a0
{
public:
    void Reserve(int Count)
    {
        int Capacity = Max & 0x7fffffff;
        if ( Capacity < Count )
        {
            Capacity *= 2;
            Unk_10dfc3c0(this, Count < Capacity ? Capacity : Count, sizeof(UnkType_10dfe5a0_Pair));
        }
    }

    int* Unk_10dfe5a0(const UnkType_10dfe5a0_Key& Key);

    UnkType_10dfe5a0_Pair* Data;
    int Num;
    int Max;
};

// UnkType_10dfe5a0::Unk_10dfe5a0
int* UnkType_10dfe5a0::Unk_10dfe5a0(const UnkType_10dfe5a0_Key& Key)
{
    for ( int i = 0; i < Num; i++ )
    {
        if ( Data[i].Key.unk_04 == Key.unk_04 && Unk_10dffc60(Data[i].Key.unk_00, Key.unk_00) == 0 )
        {
            return &Data[i].Value;
        }
    }
    int Count = Num;
    Reserve(Count + 1);
    Num = Count + 1;
    UnkType_10dfe5a0_Pair& Pair = Data[Count];
    Pair.Key = Key;
    return &Pair.Value;
}
