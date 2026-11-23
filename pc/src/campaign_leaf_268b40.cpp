// campaign_leaf_268b40.cpp -- a member function at VA 0x10b68b40 taking an int: it stores the int
// at 0x21c and, when the pointer at 0x15c is set, formats it with L": %i" through the free function
// at VA 0x10cce920 and gives the text of the resulting string (or an empty wide string when it has
// no characters) to that object (its label at 0x38 takes the text and the length the free function
// at VA 0x10f32740 gives for it, and its virtual slot 5 of its base at 0x08 is called when its int
// at 0x34 is set); the string is then destroyed with the destructor at VA 0x1090ba70. The class,
// method, member and parameter names are invented; the offsets, addresses, string and slot are the
// binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b68b40_String
{
public:
    ~UnkType_10b68b40_String();

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

UnkType_10b68b40_String __cdecl Unk_10cce920(const unsigned short* Format, ...);

class UnkType_10b68b40_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b68b40_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b68b40_Base8
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

class UnkType_10b68b40_Text : public UnkType_10b68b40_Base0, public UnkType_10b68b40_Base8
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
    UnkType_10b68b40_Label unk_38;
};

class UnkType_10b68b40
{
public:
    void Unk_10b68b40(int Value);

private:
    unsigned char unk_000[0x15c];
    UnkType_10b68b40_Text* unk_15c;
    unsigned char unk_160[0x21c - 0x160];
    int unk_21c;
};

// UnkType_10b68b40::Unk_10b68b40
void UnkType_10b68b40::Unk_10b68b40(int Value)
{
    unk_21c = Value;
    if ( unk_15c )
    {
        unk_15c->SetUnk38(Unk_10cce920(L": %i", Value).GetText());
    }
}
