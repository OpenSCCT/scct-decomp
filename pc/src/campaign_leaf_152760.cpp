// campaign_leaf_152760.cpp -- one function at file offset 0x152760, preferred VA 0x10a52760.
// The archive operator of an array of 16-byte elements: it reports the array's byte counts
// through the archive's virtual slot 5; when the archive is loading (word at offset 0x18) it reads
// a compact count with the function at VA 0x10cd80b0, empties the array to it with the method
// at VA 0x10a50f70 and reads each new element, made by the operator new at VA 0x10a508d0,
// with the element operator at VA 0x10a4c0a0; otherwise it writes the count and every
// element. It returns the archive.
// The class, function and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10a52760_Element
{
    unsigned char unk_0[0x10];
};

class UnkType_10a52760_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Num, int Max);

    unsigned char unk_4[0x18 - 0x4];
    int unk_18;
};

class UnkType_10a52760
{
public:
    UnkType_10a52760_Element* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a50f70(int Slack);
};

UnkType_10a52760_Archive& Unk_10cd80b0(UnkType_10a52760_Archive& Ar, int& Value);
void* operator new(unsigned int Size, UnkType_10a52760& Array);
UnkType_10a52760_Archive& operator<<(UnkType_10a52760_Archive& Ar,
    UnkType_10a52760_Element& Element);

// operator<<
UnkType_10a52760_Archive& operator<<(UnkType_10a52760_Archive& Ar, UnkType_10a52760& Array)
{
    Ar.VirtualSlot5(Array.ArrayNum * sizeof(UnkType_10a52760_Element),
        Array.ArrayMax * sizeof(UnkType_10a52760_Element));
    if ( Ar.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Ar, NewNum);
        Array.Unk_10a50f70(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Ar << *new(Array) UnkType_10a52760_Element;
        }
    }
    else
    {
        Unk_10cd80b0(Ar, Array.ArrayNum);
        for ( int i = 0; i < Array.ArrayNum; i++ )
        {
            Ar << Array.Data[i];
        }
    }
    return Ar;
}
