// campaign_leaf_16d2a0.cpp -- one function at file offset 0x16d2a0, preferred VA 0x10a6d2a0.
// The archive operator of an array of 8-byte elements: it reports the array's byte counts through
// the archive's virtual slot 5; when the archive is loading (word at offset 0x18) it reads a
// compact count with the function at VA 0x10cd80b0, empties the array to it with the method at
// VA 0x10a6ce70 and reads both words of each new element, made by the operator new at VA
// 0x10a6caf0, through the archive's virtual slot 1; otherwise it writes the count and both
// words of every element. It returns the archive.
// The class, function and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10a6d2a0_Element
{
    int unk_0;
    int unk_4;
};

class UnkType_10a6d2a0_Archive
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

class UnkType_10a6d2a0
{
public:
    UnkType_10a6d2a0_Element* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a6ce70(int Slack);
};

UnkType_10a6d2a0_Archive& Unk_10cd80b0(UnkType_10a6d2a0_Archive& Ar, int& Value);
void* operator new(unsigned int Size, UnkType_10a6d2a0& Array);

// operator<<
UnkType_10a6d2a0_Archive& operator<<(UnkType_10a6d2a0_Archive& Ar, UnkType_10a6d2a0& Array)
{
    Ar.VirtualSlot5(Array.ArrayNum * sizeof(UnkType_10a6d2a0_Element),
        Array.ArrayMax * sizeof(UnkType_10a6d2a0_Element));
    if ( Ar.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Ar, NewNum);
        Array.Unk_10a6ce70(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            UnkType_10a6d2a0_Element* Element = new(Array) UnkType_10a6d2a0_Element;
            Ar.VirtualSlot1(&Element->unk_0, 4);
            Ar.VirtualSlot1(&Element->unk_4, 4);
        }
    }
    else
    {
        Unk_10cd80b0(Ar, Array.ArrayNum);
        for ( int i = 0; i < Array.ArrayNum; i++ )
        {
            UnkType_10a6d2a0_Element& Element = Array.Data[i];
            Ar.VirtualSlot1(&Element.unk_0, 4);
            Ar.VirtualSlot1(&Element.unk_4, 4);
        }
    }
    return Ar;
}
