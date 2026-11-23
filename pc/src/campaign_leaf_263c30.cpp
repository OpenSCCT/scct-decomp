// campaign_leaf_263c30.cpp -- a member function at VA 0x10b63c30 taking a float: when its target
// (what the member at VA 0x10a45b50 of the object at 0x64 of the entry the member at VA 0x10a0e220
// of the object the pointer at 0x04 of the object the pointer at 0x14 refers to gives for that
// object's byte at 0x0c returns) has its pointer at 0x488 set, it sets the byte at 0x40 when the
// float at 0x2c of the object that pointer refers to differs from the value, passes the value to
// the member at VA 0x10d5f5f0 of the object the pointer at 0xa4 refers to, and gives the text of
// the value truncated to an int and formatted with L"%i" through the free function at VA
// 0x10cce920 to the object the pointer at 0xa8 refers to (its label at 0x38 takes the text and the
// length the free function at VA 0x10f32740 gives for it, and its virtual slot 5 of its base at
// 0x08 is called when its int at 0x34 is set); the string is then destroyed with the destructor at
// VA 0x1090ba70. The class, method, member and parameter names are invented; the offsets,
// addresses, string and slot are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b63c30_String
{
public:
    ~UnkType_10b63c30_String();

    // guess: the text, or an empty string when there is none (an inline accessor; name invented)
    const unsigned short* GetText() const
    {
        return unk_04 ? unk_00 : L"";
    }

private:
    const unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_10b63c30_String __cdecl Unk_10cce920(const unsigned short* Format, ...);

class UnkType_10b63c30_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b63c30_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b63c30_Base8
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

class UnkType_10b63c30_Text : public UnkType_10b63c30_Base0, public UnkType_10b63c30_Base8
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
    UnkType_10b63c30_Label unk_38;
};

class UnkType_10b63c30_Setting
{
public:
    unsigned char unk_00[0x2c];
    float unk_2c;
};

class UnkType_10b63c30_Target
{
public:
    unsigned char unk_000[0x488];
    UnkType_10b63c30_Setting* unk_488;
};

class UnkType_10b63c30_Lookup
{
public:
    UnkType_10b63c30_Target* Unk_10a45b50();
};

class UnkType_10b63c30_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b63c30_Lookup* unk_64;
};

class UnkType_10b63c30_Table
{
public:
    UnkType_10b63c30_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b63c30_Menu
{
public:
    // guess: the current target (an inline accessor; name invented)
    UnkType_10b63c30_Target* GetTarget()
    {
        return unk_04->Unk_10a0e220(unk_0c)->unk_64->Unk_10a45b50();
    }

    int unk_00;
    UnkType_10b63c30_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b63c30_Slider
{
public:
    void Unk_10d5f5f0(float Value);
};

class UnkType_10b63c30
{
public:
    void Unk_10b63c30(float Value);

private:
    unsigned char unk_00[0x14];
    UnkType_10b63c30_Menu* unk_14;
    unsigned char unk_18[0x40 - 0x18];
    bool unk_40;
    unsigned char unk_41[0xa4 - 0x41];
    UnkType_10b63c30_Slider* unk_a4;
    UnkType_10b63c30_Text* unk_a8;
};

// UnkType_10b63c30::Unk_10b63c30
void UnkType_10b63c30::Unk_10b63c30(float Value)
{
    UnkType_10b63c30_Setting* Setting = unk_14->GetTarget()->unk_488;
    if ( Setting )
    {
        if ( Setting->unk_2c != Value )
        {
            unk_40 = true;
        }
        unk_a4->Unk_10d5f5f0(Value);
        UnkType_10b63c30_String Text = Unk_10cce920(L"%i", (int)Value);
        unk_a8->SetUnk38(Text.GetText());
    }
}
