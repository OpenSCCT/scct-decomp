// campaign_leaf_4fe480.cpp -- method at VA 0x10dfe480: returns the address of the value paired with
// the key its argument points to in this array of key/value pairs, appending a new pair for the key
// (growing through the function at VA 0x10dfc3c0) when none matches. The class, method and member
// names are invented; the address is the binary's.

class UnkType_10dfe480_ArrayBase;

void Unk_10dfc3c0(UnkType_10dfe480_ArrayBase* Array, int NewMax, int ElementSize);

class UnkType_10dfe480_ArrayBase
{
public:
    void* Data;
    int Num;
    int Max;
};

template<class T> class UnkType_10dfe480_Array : public UnkType_10dfe480_ArrayBase
{
public:
    void Reserve(int Count)
    {
        int Capacity = Max & 0x7fffffff;
        if ( Capacity < Count )
        {
            Capacity *= 2;
            Unk_10dfc3c0(this, Count < Capacity ? Capacity : Count, sizeof(T));
        }
    }

    T& operator()(int Index)
    {
        return ( (T*)Data )[Index];
    }
};

class UnkType_10dfe480_Pair
{
public:
    int Key;
    int Value;
};

class UnkType_10dfe480 : public UnkType_10dfe480_Array<UnkType_10dfe480_Pair>
{
public:
    int* Unk_10dfe480(const int& Key);
};

// UnkType_10dfe480::Unk_10dfe480
int* UnkType_10dfe480::Unk_10dfe480(const int& Key)
{
    int Count = Num;
    for ( int i = 0; i < Num; i++ )
    {
        if ( ( *this )(i).Key == Key )
        {
            return &( *this )(i).Value;
        }
    }
    Reserve(Count + 1);
    Num = Count + 1;
    UnkType_10dfe480_Pair& Pair = ( *this )(Count);
    Pair.Key = Key;
    return &Pair.Value;
}
