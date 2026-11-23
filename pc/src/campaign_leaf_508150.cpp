// campaign_leaf_508150.cpp -- method at VA 0x10e08150: grows the array of sixteen-byte items at
// 0x10 to hold its first argument and the array of twelve-byte items at 0x1c to hold its second,
// through the function at VA 0x10dfc3c0, doubling the capacity when that is enough. The class,
// method and member names are invented; the offsets and the address are the binary's.

class UnkType_10e08150_ArrayBase;

void Unk_10dfc3c0(UnkType_10e08150_ArrayBase* Array, int NewMax, int ElementSize);

class UnkType_10e08150_ArrayBase
{
public:
    void* Data;
    int Num;
    int Max;
};

template<class T> class UnkType_10e08150_Array : public UnkType_10e08150_ArrayBase
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

class UnkType_10e08150_Item16
{
public:
    int unk_00[4];
};

class UnkType_10e08150_Item12
{
public:
    int unk_00[3];
};

class UnkType_10e08150
{
public:
    void Unk_10e08150(int Count16, int Count12);

    unsigned char unk_00[0x10];
    UnkType_10e08150_Array<UnkType_10e08150_Item16> unk_10;
    UnkType_10e08150_Array<UnkType_10e08150_Item12> unk_1c;
};

// UnkType_10e08150::Unk_10e08150
void UnkType_10e08150::Unk_10e08150(int Count16, int Count12)
{
    if ( Count16 > ( unk_10.Max & 0x7fffffff ) )
    {
        unk_10.Reserve(Count16);
    }
    if ( Count12 > ( unk_1c.Max & 0x7fffffff ) )
    {
        unk_1c.Reserve(Count12);
    }
}
