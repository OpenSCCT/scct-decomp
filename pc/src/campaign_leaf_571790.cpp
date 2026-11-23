// campaign_leaf_571790.cpp -- thiscall method at VA 0x10e71790: splits the array of pairs at 0x1c
// into Out's two arrays of words at 0x00 and 0x0c, the first word of each pair into the first array
// and the second into the second. Each destination is sized to the pair count first, reserving room
// through VA 0x10dfc3c0 (at least doubling it). All names are invented; the addresses are the
// binary's.

struct UnkType_10e71790_Array;

void Unk_10dfc3c0(UnkType_10e71790_Array* Array, int NewMax, int ElementSize);

struct UnkType_10e71790_Array
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e71790_Array::Reserve
    // guess: grows the storage to at least Count words, at least doubling it.
    void Reserve(int Count)
    {
        int Capacity = unk_08 & 0x7fffffff;
        if ( Capacity < Count )
        {
            Capacity *= 2;
            Unk_10dfc3c0(this, Count < Capacity ? Capacity : Count, sizeof(int));
        }
    }

    // UnkType_10e71790_Array::SetNum
    // guess: sets the count to Count, reserving room first; new entries are left as they are.
    void SetNum(int Count)
    {
        Reserve(Count);
        unk_04 = Count;
    }
};

struct UnkType_10e71790_Pair
{
    int unk_00;
    int unk_04;
};

struct UnkType_10e71790_Split
{
    UnkType_10e71790_Array unk_00;
    UnkType_10e71790_Array unk_0c;
};

class UnkType_10e71790
{
public:
    void Unk_10e71790(UnkType_10e71790_Split* Out);

private:
    int unk_00[7];
    UnkType_10e71790_Pair* unk_1c;
    int unk_20;
};

// UnkType_10e71790::Unk_10e71790
void UnkType_10e71790::Unk_10e71790(UnkType_10e71790_Split* Out)
{
    int Count = unk_20;

    Out->unk_00.SetNum(Count);
    Out->unk_0c.SetNum(Count);
    for ( int Index = 0; Index < Count; Index++ )
    {
        Out->unk_00.unk_00[Index] = unk_1c[Index].unk_00;
        Out->unk_0c.unk_00[Index] = unk_1c[Index].unk_04;
    }
}
