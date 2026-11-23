// campaign_leaf_254280.cpp -- a member function at VA 0x10b54280 taking two strings: it assigns
// them to the strings at 0x48 and 0x54 with the string assignment at VA 0x109097e0 and gives the
// text of the first (or an empty wide string) to the object the pointer at 0x40 refers to (its
// label at 0x38 takes the text and the length the free function at VA 0x10f32740 gives for it, and
// its virtual slot 5 of its base at 0x08 is called when its int at 0x34 is set). When its own
// virtual slot 16 then returns true, it passes a copy of the string at 0x54 (made with the
// constructor at VA 0x1090ba00 from its text, destroyed with the destructor at VA 0x1090ba70), 0,
// 0, 0 and 0 to the member at VA 0x10ad6330 of the object the pointer at 0xc8 of the object the
// pointer at 0x14 refers to, then passes the pointer at 0x38 to that object's member at VA
// 0x10ad56f0. The class, method, member and parameter names are invented; the offsets, addresses
// and slots are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b54280_String
{
public:
    UnkType_10b54280_String(const unsigned short* Text);
    ~UnkType_10b54280_String();
    UnkType_10b54280_String& operator=(const UnkType_10b54280_String& Other);

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

class UnkType_10b54280_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b54280_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b54280_Base8
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

class UnkType_10b54280_Text : public UnkType_10b54280_Base0, public UnkType_10b54280_Base8
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
    UnkType_10b54280_Label unk_38;
};

class UnkType_10b54280_Page;

class UnkType_10b54280_Menu
{
public:
    void Unk_10ad56f0(UnkType_10b54280_Page* Page);
    void Unk_10ad6330(const UnkType_10b54280_String& Text, int First, int Second, int Third,
                      int Fourth);
};

class UnkType_10b54280_Owner
{
public:
    unsigned char unk_00[0xc8];
    UnkType_10b54280_Menu* unk_c8;
};

class UnkType_10b54280
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
    virtual bool VirtualSlot16();

    void Unk_10b54280(const UnkType_10b54280_String& First, const UnkType_10b54280_String& Second);

private:
    unsigned char unk_04[0x14 - 0x04];
    UnkType_10b54280_Owner* unk_14;
    unsigned char unk_18[0x38 - 0x18];
    UnkType_10b54280_Page* unk_38;
    unsigned char unk_3c[0x40 - 0x3c];
    UnkType_10b54280_Text* unk_40;
    int unk_44;
    UnkType_10b54280_String unk_48;
    UnkType_10b54280_String unk_54;
};

// UnkType_10b54280::Unk_10b54280
void UnkType_10b54280::Unk_10b54280(const UnkType_10b54280_String& First,
                                    const UnkType_10b54280_String& Second)
{
    unk_48 = First;
    unk_54 = Second;
    unk_40->SetUnk38(unk_48.GetText());
    if ( VirtualSlot16() )
    {
        {
            UnkType_10b54280_String Text(unk_54.GetText());
            unk_14->unk_c8->Unk_10ad6330(Text, 0, 0, 0, 0);
        }
        unk_14->unk_c8->Unk_10ad56f0(unk_38);
    }
}
