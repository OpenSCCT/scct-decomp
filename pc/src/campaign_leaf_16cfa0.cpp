// campaign_leaf_16cfa0.cpp -- one function at file offset 0x16cfa0, preferred VA 0x10a6cfa0.
// The archive operator of an array of integers: it reports the array's byte counts through
// the archive's virtual slot 5; when the archive is loading (word at offset 0x18) it reads a
// compact count with the function at VA 0x10cd80b0, empties the array to it with the method at
// VA 0x10a6cc50 and reads each new element, made by the operator new at VA
// 0x10a6c9b0, through the archive's virtual slot 1; otherwise it writes the count and every
// element. It returns the archive.
// The class, function and member names are invented; the offset and the bytes are the binary's.


class UnkType_10a6cfa0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Length);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Num, int Max);

    unsigned char unk_4[0x18 - 0x4];
    int unk_18;
};

class UnkType_10a6cfa0
{
public:
    int* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6cc50(int Slack);
};

UnkType_10a6cfa0_Archive& Unk_10cd80b0(UnkType_10a6cfa0_Archive& Ar, int& Value);
void* operator new(unsigned int Size, UnkType_10a6cfa0& Array);

// operator<<
UnkType_10a6cfa0_Archive& operator<<(UnkType_10a6cfa0_Archive& Ar, UnkType_10a6cfa0& Array)
{
    Ar.VirtualSlot5(Array.ArrayNum * sizeof(int),
        Array.ArrayMax * sizeof(int));
    if ( Ar.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Ar, NewNum);
        Array.Unk_10a6cc50(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Ar.VirtualSlot1(new(Array) int, sizeof(int));
        }
    }
    else
    {
        Unk_10cd80b0(Ar, Array.ArrayNum);
        for ( int i = 0; i < Array.ArrayNum; i++ )
        {
            Ar.VirtualSlot1(&Array.Data[i], sizeof(int));
        }
    }
    return Ar;
}
