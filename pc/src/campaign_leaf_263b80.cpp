// campaign_leaf_263b80.cpp -- a member function at VA 0x10b63b80 taking a value: when its target
// (what the member at VA 0x10a45b50 of the object at 0x64 of the entry the member at VA 0x10a0e220
// of the object the pointer at 0x04 of the object the pointer at 0x14 refers to gives for that
// object's byte at 0x0c returns) has its pointer at 0x488 set, it sets the byte at 0x40 when bit 0
// of the int at 0x28 of the object that pointer refers to differs from the value, passes whether
// the value is non-zero to the virtual slot 7 of the object the pointer at 0x9c refers to, and
// sets the text of the object the pointer at 0xa0 refers to (its label at 0x38 takes the text and
// the length the free function at VA 0x10f32740 gives for it, and its virtual slot 5 of its base
// at 0x08 is called when its int at 0x34 is set) to what the free function at VA 0x10ccc4b0
// returns for L"MenuSettings", L"ON" or L"OFF" (by the byte at 0x50 of the object at 0x9c),
// L"Localization\\PreGame_PC", 0, 0 and 1. The class, method, member and parameter names are
// invented; the offsets, addresses, strings and slots are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);
const unsigned short* __cdecl Unk_10ccc4b0(const unsigned short* Key,
                                           const unsigned short* Section,
                                           const unsigned short* Package, int First, int Second,
                                           int Third);

class UnkType_10b63b80_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b63b80_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b63b80_Base8
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();

private:
    unsigned char unk_04[0x34 - 0x0c];
};

class UnkType_10b63b80_Text : public UnkType_10b63b80_Base0, public UnkType_10b63b80_Base8
{
public:
    // guess: sets the displayed text (an inline helper; name invented)
    void SetUnk38(const unsigned short* Text)
    {
        unk_38.Unk_10ad8220(Text, Unk_10f32740(Text));
        if ( unk_34 )
        {
            VirtualSlot5();
        }
    }

    int unk_34;
    UnkType_10b63b80_Label unk_38;
};

class UnkType_10b63b80_Setting
{
public:
    unsigned char unk_00[0x28];
    int unk_28;
};

class UnkType_10b63b80_Target
{
public:
    unsigned char unk_000[0x488];
    UnkType_10b63b80_Setting* unk_488;
};

class UnkType_10b63b80_Lookup
{
public:
    UnkType_10b63b80_Target* Unk_10a45b50();
};

class UnkType_10b63b80_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b63b80_Lookup* unk_64;
};

class UnkType_10b63b80_Table
{
public:
    UnkType_10b63b80_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b63b80_Menu
{
public:
    // guess: the current target (an inline accessor; name invented)
    UnkType_10b63b80_Target* GetTarget()
    {
        return unk_04->Unk_10a0e220(unk_0c)->unk_64->Unk_10a45b50();
    }

    int unk_00;
    UnkType_10b63b80_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b63b80_Toggle
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(bool Value);

    unsigned char unk_04[0x50 - 0x04];
    bool unk_50;
};

class UnkType_10b63b80
{
public:
    void Unk_10b63b80(int Value);

private:
    unsigned char unk_00[0x14];
    UnkType_10b63b80_Menu* unk_14;
    unsigned char unk_18[0x40 - 0x18];
    bool unk_40;
    unsigned char unk_41[0x9c - 0x41];
    UnkType_10b63b80_Toggle* unk_9c;
    UnkType_10b63b80_Text* unk_a0;
};

// UnkType_10b63b80::Unk_10b63b80
void UnkType_10b63b80::Unk_10b63b80(int Value)
{
    UnkType_10b63b80_Setting* Setting = unk_14->GetTarget()->unk_488;
    if ( Setting )
    {
        if ( (Setting->unk_28 & 1) != Value )
        {
            unk_40 = true;
        }
        unk_9c->VirtualSlot7(Value != 0);
        unk_a0->SetUnk38(unk_9c->unk_50
                             ? Unk_10ccc4b0(L"MenuSettings", L"ON",
                                            L"Localization\\PreGame_PC", 0, 0, 1)
                             : Unk_10ccc4b0(L"MenuSettings", L"OFF",
                                            L"Localization\\PreGame_PC", 0, 0, 1));
    }
}
