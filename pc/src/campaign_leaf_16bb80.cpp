// campaign_leaf_16bb80.cpp -- one function at file offset 0x16bb80, preferred VA 0x10a6bb80.
// The archive operator of a four-field record: it serializes the first field's four bytes
// through the archive's virtual slot 1 and the next two fields through slot 7. The last field
// goes through slot 6 when the archive's version (offset 0xc) is above 77; older archives set it
// to zero instead.
// The class, function and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a6bb80_Name;
class UnkType_10a6bb80_Object;

class UnkType_10a6bb80_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Value, int Length);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual UnkType_10a6bb80_Archive& VirtualSlot6(UnkType_10a6bb80_Object*& Object);
    virtual UnkType_10a6bb80_Archive& VirtualSlot7(UnkType_10a6bb80_Name& Name);

    unsigned char unk_4[0xc - 0x4];
    int unk_c;
};

class UnkType_10a6bb80_Name
{
public:
    int unk_0;
};

class UnkType_10a6bb80
{
public:
    int unk_0;
    UnkType_10a6bb80_Name unk_4;
    UnkType_10a6bb80_Name unk_8;
    UnkType_10a6bb80_Object* unk_c;
};

// operator<<
void operator<<(UnkType_10a6bb80_Archive& Ar, UnkType_10a6bb80& Record)
{
    if ( Ar.unk_c > 77 )
    {
        Ar.VirtualSlot1(&Record.unk_0, 4);
        Ar.VirtualSlot7(Record.unk_4).VirtualSlot7(Record.unk_8).VirtualSlot6(Record.unk_c);
    }
    else
    {
        Record.unk_c = 0;
        Ar.VirtualSlot1(&Record.unk_0, 4);
        Ar.VirtualSlot7(Record.unk_4).VirtualSlot7(Record.unk_8);
    }
}
