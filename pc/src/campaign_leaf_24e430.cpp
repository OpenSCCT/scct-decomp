// campaign_leaf_24e430.cpp -- a member function at VA 0x10b4e430: when the int at 0x50 is zero it
// passes the member at 0x40 to the free function at VA 0x10961f00, sets the int at 0x50 to 2 and
// gives the text the free function at VA 0x10ccc4b0 returns for L"MATCHLIST", L"MatchesSearch" and
// L"Localization\\PreGameMenus" to the object the pointer at 0x4c refers to (its label at 0x38
// takes the text and the length the free function at VA 0x10f32740 gives for it, and its virtual
// slot 5 of its base at 0x08 is called when its int at 0x34 is set). It returns true when the free
// function at VA 0x109620c0 then returns non-zero; otherwise it clears the int at 0x50 and returns
// false, as it does when the int was not zero. The class, method, member and parameter names are
// invented; the offsets, addresses, strings and slot are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b4e430_Unk40
{
private:
    int unk_00;
    int unk_04;
    int unk_08;
};

void __cdecl Unk_10961f00(UnkType_10b4e430_Unk40* Value);
const unsigned short* __cdecl Unk_10ccc4b0(const unsigned short* Key,
                                           const unsigned short* Section,
                                           const unsigned short* Package, int First, int Second,
                                           int Third);
int __cdecl Unk_109620c0();

class UnkType_10b4e430_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b4e430_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b4e430_Base8
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

class UnkType_10b4e430_Text : public UnkType_10b4e430_Base0, public UnkType_10b4e430_Base8
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
    UnkType_10b4e430_Label unk_38;
};

class UnkType_10b4e430
{
public:
    bool Unk_10b4e430();

private:
    unsigned char unk_00[0x40];
    UnkType_10b4e430_Unk40 unk_40;
    UnkType_10b4e430_Text* unk_4c;
    int unk_50;
};

// UnkType_10b4e430::Unk_10b4e430
bool UnkType_10b4e430::Unk_10b4e430()
{
    if ( unk_50 == 0 )
    {
        Unk_10961f00(&unk_40);
        unk_50 = 2;
        unk_4c->SetUnk38(Unk_10ccc4b0(L"MATCHLIST", L"MatchesSearch",
                                      L"Localization\\PreGameMenus", 0, 0, 1));
        if ( !Unk_109620c0() )
        {
            unk_50 = 0;
            return false;
        }
        return true;
    }
    return false;
}
