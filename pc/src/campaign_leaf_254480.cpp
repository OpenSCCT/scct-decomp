// campaign_leaf_254480.cpp -- a member function at VA 0x10b54480 taking an unused value: when the
// virtual slot 16 of the object the pointer at 0x40 refers to returns true, it advances the index
// at 0x48 and, when the index is then at least 0 and below the count at 0x50, passes it, 0 and 0
// to the member at VA 0x10d2a830 of the list the pointer at 0x44 refers to, makes a string from
// the text of the std::wstring that starts the list's item at that index (its items are a
// std::vector at 0x68; the default allocator is used, as this function never allocates) with the
// constructor at VA 0x1090ba00, and passes it and the matching string of the array at 0x4c to the
// object's member at VA 0x10b54280; the string is destroyed with the destructor at VA 0x1090ba70.
// When the index is out of range it passes 0 to that object's virtual slot 15 instead. The class, method, member and parameter
// names are invented; the offsets, addresses and slots are the binary's.

#include <string>
#include <vector>

class UnkType_10b54480_String
{
public:
    UnkType_10b54480_String(const unsigned short* Text);
    ~UnkType_10b54480_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b54480_Item
{
public:
    std::basic_string<unsigned short> unk_00;
    unsigned char unk_1c[0x3c - 0x1c];
};

class UnkType_10b54480_List
{
public:
    // guess: the item at an index (an inline accessor; name invented)
    UnkType_10b54480_Item& GetItem(short Index)
    {
        return unk_68[Index];
    }

    void Unk_10d2a830(unsigned short Index, int First, int Second);

    unsigned char unk_00[0x68];
    std::vector<UnkType_10b54480_Item> unk_68;
};

class UnkType_10b54480_Page
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
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15(int Value);
    virtual bool VirtualSlot16();

    void Unk_10b54280(const UnkType_10b54480_String& First, const UnkType_10b54480_String& Second);
};

class UnkType_10b54480
{
public:
    void Unk_10b54480(int Unused);

private:
    unsigned char unk_00[0x40];
    UnkType_10b54480_Page* unk_40;
    UnkType_10b54480_List* unk_44;
    int unk_48;
    UnkType_10b54480_String* unk_4c;
    int unk_50;
};

// UnkType_10b54480::Unk_10b54480
void UnkType_10b54480::Unk_10b54480(int Unused)
{
    if ( unk_40->VirtualSlot16() )
    {
        if ( ++unk_48 >= 0 && unk_48 < unk_50 )
        {
            unk_44->Unk_10d2a830((unsigned short)unk_48, 0, 0);
            UnkType_10b54480_String Text(unk_44->GetItem(unk_48).unk_00.c_str());
            unk_40->Unk_10b54280(Text, unk_4c[unk_48]);
        }
        else
        {
            unk_40->VirtualSlot15(0);
        }
    }
}
