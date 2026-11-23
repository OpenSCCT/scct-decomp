// campaign_leaf_504840.cpp -- method at VA 0x10e04840: stores a word at an index of this array of
// words, first growing the array to cover the index (through the function at VA 0x10dfc3c0) and
// zeroing the new entries. The class, method and member names are invented; the address is the
// binary's.

class UnkType_10e04840_ArrayBase;

void Unk_10dfc3c0(UnkType_10e04840_ArrayBase* Array, int NewMax, int ElementSize);

class UnkType_10e04840_ArrayBase
{
public:
    void* Data;
    int Num;
    int Max;
};

template<class T> class UnkType_10e04840_Array : public UnkType_10e04840_ArrayBase
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

class UnkType_10e04840 : public UnkType_10e04840_Array<int>
{
public:
    void Unk_10e04840(int Index, int Value);
};

// UnkType_10e04840::Unk_10e04840
void UnkType_10e04840::Unk_10e04840(int Index, int Value)
{
    int Count = Num;
    if ( Count <= Index )
    {
        int NewNum = Index + 1;
        if ( NewNum > Count )
        {
            Reserve(NewNum);
            for ( int i = Count; i < NewNum; i++ )
            {
                ( *this )(i) = 0;
            }
        }
        Num = NewNum;
    }
    ( *this )(Index) = Value;
}
