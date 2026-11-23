// campaign_leaf_501ef0.cpp -- method at VA 0x10e01ef0: copies a count of bytes from its argument into
// the character array at 0x08 at the position at 0x0c (copy function at VA 0x10dffe80), first
// lengthening the array to fit (growing it through the function at VA 0x10dfc3c0) and keeping a zero
// byte after its last character, then advances the position and returns the count. The class,
// method and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10e01ef0_Text;

void Unk_10dfc3c0(UnkType_10e01ef0_Text* Array, int NewMax, int ElementSize);
void* Unk_10dffe80(void* Destination, const void* Source, int Count);

class UnkType_10e01ef0_Text
{
public:
    void Reserve(int Count)
    {
        int Capacity = Max & 0x7fffffff;
        if ( Capacity < Count )
        {
            Capacity *= 2;
            Unk_10dfc3c0(this, Count < Capacity ? Capacity : Count, 1);
        }
    }

    char* Data;
    int Num;
    int Max;
};

class UnkType_10e01ef0
{
public:
    int Unk_10e01ef0(const char* Source, int Count);

    unsigned char unk_00[0x08];
    UnkType_10e01ef0_Text* unk_08;
    int unk_0c;
};

// UnkType_10e01ef0::Unk_10e01ef0
int UnkType_10e01ef0::Unk_10e01ef0(const char* Source, int Count)
{
    int Available = unk_08->Num - unk_0c;
    if ( Count > Available )
    {
        int NewNum = unk_08->Num - Available + Count;
        unk_08->Reserve(NewNum + 1);
        unk_08->Num = NewNum;
        unk_08->Data[NewNum] = 0;
    }
    else if ( ( unk_08->Max & 0x7fffffff ) > unk_08->Num )
    {
        unk_08->Data[unk_08->Num] = 0;
    }
    Unk_10dffe80(unk_08->Data + unk_0c, Source, Count);
    unk_0c += Count;
    return Count;
}
