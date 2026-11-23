// campaign_leaf_254210.cpp -- a member function at VA 0x10b54210 taking two strings and an int: it
// assigns the strings to those at 0x48 and 0x54 with the string assignment at VA 0x109097e0 and
// stores the int at 0x44. It then passes the text of the string at 0x48 (or an empty wide string
// when it has no characters) and the length the free function at VA 0x10f32740 gives for it to the
// member at VA 0x10ad8220 of the member at 0x38 of the object the pointer at 0x40 refers to, and
// calls that object's virtual slot 5 of its base at 0x08 when its int at 0x34 is set. The class,
// method, member and parameter names are invented; the offsets, addresses and slot are the
// binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b54210_String
{
public:
    UnkType_10b54210_String& operator=(const UnkType_10b54210_String& Other);

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

class UnkType_10b54210_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b54210_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b54210_Base8
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

class UnkType_10b54210_Text : public UnkType_10b54210_Base0, public UnkType_10b54210_Base8
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
    UnkType_10b54210_Label unk_38;
};

class UnkType_10b54210
{
public:
    void Unk_10b54210(const UnkType_10b54210_String& First, const UnkType_10b54210_String& Second,
                      int Value);

private:
    unsigned char unk_00[0x40];
    UnkType_10b54210_Text* unk_40;
    int unk_44;
    UnkType_10b54210_String unk_48;
    UnkType_10b54210_String unk_54;
};

// UnkType_10b54210::Unk_10b54210
void UnkType_10b54210::Unk_10b54210(const UnkType_10b54210_String& First,
                                    const UnkType_10b54210_String& Second, int Value)
{
    unk_48 = First;
    unk_54 = Second;
    unk_44 = Value;
    unk_40->SetUnk38(unk_48.GetText());
}
