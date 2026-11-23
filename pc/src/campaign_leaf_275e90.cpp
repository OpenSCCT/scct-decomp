// campaign_leaf_275e90.cpp -- function at VA 0x10b75e90 taking an object: when it is set, for every
// 60-byte entry of its vector at 0x68 (count and index taken as shorts) whose handler at 0x1c is
// set, while its vector of pointers at 0x78 holds more than one (count taken as a char), passes the
// entry's index, 1 and the text of the string the method at VA 0x10ad6950 makes from the string the
// handler's virtual slot 13 (vtable offset 0x34) returns (L"" when empty) to the object's method at
// VA 0x10d2dca0; both temporary strings are destroyed through the destructor at VA 0x1090ba70. The
// vectors never allocate here, so the default allocator stands in. The class, member and function
// names are invented; the offsets, the slot and the addresses are the binary's.

#include <vector>

class UnkType_10b75e90_String
{
public:
    ~UnkType_10b75e90_String();

    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

    UnkType_10b75e90_String Unk_10ad6950() const;

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b75e90_Handler
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual UnkType_10b75e90_String VirtualSlot13();
};

class UnkType_10b75e90_Entry
{
public:
    unsigned char unk_00[0x1c];
    UnkType_10b75e90_Handler* unk_1c;
    unsigned char unk_20[0x3c - 0x20];
};

class UnkType_10b75e90_Item;

class UnkType_10b75e90_Object
{
public:
    void Unk_10d2dca0(int Index, int Flag, const unsigned short* Text);

    unsigned char unk_00[0x68];
    std::vector<UnkType_10b75e90_Entry> unk_68;
    std::vector<UnkType_10b75e90_Item*> unk_78;
};

// Unk_10b75e90
void Unk_10b75e90(UnkType_10b75e90_Object* Object)
{
    if ( !Object )
    {
        return;
    }
    for ( int Index = 0; Index < (short)Object->unk_68.size(); Index++ )
    {
        UnkType_10b75e90_Handler* Handler = Object->unk_68[(short)Index].unk_1c;
        if ( Handler && (char)Object->unk_78.size() > 1 )
        {
            UnkType_10b75e90_String Name = Handler->VirtualSlot13();
            Object->Unk_10d2dca0(Index, 1, *Name.Unk_10ad6950());
        }
    }
}
