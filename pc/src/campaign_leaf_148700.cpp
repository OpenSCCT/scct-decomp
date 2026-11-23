// campaign_leaf_148700.cpp -- one function at file offset 0x148700, preferred VA 0x10a48700.
// The archive operator of an array of object pointers: it reports the array's byte counts through
// the archive's virtual slot 5; when the archive is loading (word at offset 0x18) it reads a
// compact count with the function at VA 0x10cd80b0, empties the array to it with the method at VA
// 0x10a486d0 and reads each new element, made by the operator new at VA 0x10a48680, through the
// archive's virtual slot 6; otherwise it writes the count and every element. It returns the
// archive.
// The class, function and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a48700_Object;

class UnkType_10a48700_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Num, int Max);
    virtual UnkType_10a48700_Archive& VirtualSlot6(UnkType_10a48700_Object*& Object);

    unsigned char unk_4[0x18 - 0x4];
    int unk_18;
};

class UnkType_10a48700
{
public:
    UnkType_10a48700_Object** Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a486d0(int Slack);
};

UnkType_10a48700_Archive& Unk_10cd80b0(UnkType_10a48700_Archive& Ar, int& Value);
void* operator new(unsigned int Size, UnkType_10a48700& Array);

// operator<<
UnkType_10a48700_Archive& operator<<(UnkType_10a48700_Archive& Ar, UnkType_10a48700& Array)
{
    Ar.VirtualSlot5(Array.ArrayNum * sizeof(UnkType_10a48700_Object*),
        Array.ArrayMax * sizeof(UnkType_10a48700_Object*));
    if ( Ar.unk_18 )
    {
        int NewNum;
        Unk_10cd80b0(Ar, NewNum);
        Array.Unk_10a486d0(NewNum);
        for ( int i = 0; i < NewNum; i++ )
        {
            Ar.VirtualSlot6(*new(Array) UnkType_10a48700_Object*);
        }
    }
    else
    {
        Unk_10cd80b0(Ar, Array.ArrayNum);
        for ( int i = 0; i < Array.ArrayNum; i++ )
        {
            Ar.VirtualSlot6(Array.Data[i]);
        }
    }
    return Ar;
}
