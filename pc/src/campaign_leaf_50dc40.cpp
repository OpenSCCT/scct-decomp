// campaign_leaf_50dc40.cpp -- method at VA 0x10e0dc40: passes its argument to the method at VA
// 0x10e0f570, then sizes the argument's two word arrays at 0x04 and 0x10 to the count at 0x10
// (growing them through the function at VA 0x10dfc3c0) and fills them with the first and second
// words of this object's pairs at 0x0c. The class, method and member names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10e0dc40_Words;

void Unk_10dfc3c0(UnkType_10e0dc40_Words* Array, int NewMax, int ElementSize);

class UnkType_10e0dc40_Words
{
public:
    void Reserve(int Count)
    {
        int Capacity = Max & 0x7fffffff;
        if ( Capacity < Count )
        {
            Capacity *= 2;
            Unk_10dfc3c0(this, Count < Capacity ? Capacity : Count, sizeof(int));
        }
    }

    int* Data;
    int Num;
    int Max;
};

class UnkType_10e0dc40_Out
{
public:
    int unk_00;
    UnkType_10e0dc40_Words unk_04;
    UnkType_10e0dc40_Words unk_10;
};

class UnkType_10e0dc40_Pair
{
public:
    int First;
    int Second;
};

class UnkType_10e0dc40
{
public:
    void Unk_10e0dc40(UnkType_10e0dc40_Out* Out);
    void Unk_10e0f570(UnkType_10e0dc40_Out* Out);

    unsigned char unk_00[0x0c];
    UnkType_10e0dc40_Pair* unk_0c;
    int unk_10;
};

// UnkType_10e0dc40::Unk_10e0dc40
void UnkType_10e0dc40::Unk_10e0dc40(UnkType_10e0dc40_Out* Out)
{
    Unk_10e0f570(Out);
    Out->unk_04.Num = 0;
    int Count = unk_10;
    UnkType_10e0dc40_Words& Firsts = Out->unk_04;
    Firsts.Reserve(Count);
    Firsts.Num = Count;
    UnkType_10e0dc40_Words& Seconds = Out->unk_10;
    Seconds.Reserve(Count);
    Seconds.Num = Count;
    for ( int i = 0; i < Count; i++ )
    {
        Firsts.Data[i] = unk_0c[i].First;
        Seconds.Data[i] = unk_0c[i].Second;
    }
}
