// campaign_leaf_1d5f20.cpp -- thiscall method at VA 0x10ad5f20. It sets its second argument, a
// string, to the empty string (assignment at VA 0x10907a00); asks the object at 0x04 for an object
// (VA 0x10a0e220), passes the byte at 0x0c to the method at VA 0x10a45c10 of that object's member
// at 0x64, and calls slot 32 of the result with the first argument. When that returns an object, it
// returns the result of the function at VA 0x10a37880 called with the first argument, the object
// and the string; otherwise 0. The class, method and member names are invented.

class UnkType_10ad5f20_String
{
public:
    UnkType_10ad5f20_String& operator=(const unsigned short* Other);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad5f20_Finder
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
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void* VirtualSlot32(int Value);
};

class UnkType_10ad5f20_Table
{
public:
    UnkType_10ad5f20_Finder* Unk_10a45c10(unsigned char Index);
};

struct UnkType_10ad5f20_Owner
{
    char unk_00[0x64];
    UnkType_10ad5f20_Table* unk_64;
};

class UnkType_10ad5f20_Source
{
public:
    UnkType_10ad5f20_Owner* Unk_10a0e220();
};

int Unk_10a37880(int Value, void* Object, UnkType_10ad5f20_String& Text);

class UnkType_10ad5f20
{
public:
    int Unk_10ad5f20(int Value, UnkType_10ad5f20_String& Text);

private:
    int unk_00;
    UnkType_10ad5f20_Source* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

// UnkType_10ad5f20::Unk_10ad5f20
int UnkType_10ad5f20::Unk_10ad5f20(int Value, UnkType_10ad5f20_String& Text)
{
    Text = L"";
    void* Object = unk_04->Unk_10a0e220()->unk_64->Unk_10a45c10(unk_0c)->VirtualSlot32(Value);
    if ( Object != 0 )
    {
        return Unk_10a37880(Value, Object, Text);
    }
    return 0;
}
