// campaign_leaf_08a050.cpp -- method at VA 0x1098a050: passes its two arguments to virtual slot 1
// of the archive at 0x08, adds to the value at 0x0c how far that moved the position its virtual
// slot 10 (vtable offset 0x28) returns, and returns that distance. The class, member and method
// names are invented; the offsets and the slots are the binary's.

class UnkType_1098a050_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual int VirtualSlot10();
};

class UnkType_1098a050
{
public:
    int Unk_1098a050(void* Data, int Size);

private:
    int unk_00;
    int unk_04;
    UnkType_1098a050_Archive* unk_08;
    int unk_0c;
};

// UnkType_1098a050::Unk_1098a050
int UnkType_1098a050::Unk_1098a050(void* Data, int Size)
{
    int Start = unk_08->VirtualSlot10();
    unk_08->VirtualSlot1(Data, Size);
    int End = unk_08->VirtualSlot10();
    unk_0c += End - Start;
    return End - Start;
}
