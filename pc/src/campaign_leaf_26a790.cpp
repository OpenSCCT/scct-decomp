// campaign_leaf_26a790.cpp -- a member function at VA 0x10b6a790: when the pointer at 0x60 is set
// it first, when the pointer at 0x5c is set, passes an empty wide string and the length the free
// function at VA 0x10f32740 gives for it to the member at VA 0x10ad8220 of the member at 0x38 of
// that object, calling its virtual slot 5 of its base at 0x08 when its int at 0x34 is set; it then
// calls the member at VA 0x10d5ba90 of the object at 0x60 and sets that object's flags at 0x20 to
// 2 within the mask 0x0d. Last it calls the member at VA 0x10b69740 with 0. The class, method and
// member names are invented; the offsets, constants, addresses and slot are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b6a790_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b6a790_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b6a790_Base8
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

class UnkType_10b6a790_Text : public UnkType_10b6a790_Base0, public UnkType_10b6a790_Base8
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
    UnkType_10b6a790_Label unk_38;
};

class UnkType_10b6a790_Owner
{
public:
    void Unk_10d5ba90();

    unsigned char unk_00[0x20];
    unsigned int unk_20;
};

class UnkType_10b6a790
{
public:
    void Unk_10b69740(int Value);
    void Unk_10b6a790();

private:
    unsigned char unk_00[0x5c];
    UnkType_10b6a790_Text* unk_5c;
    UnkType_10b6a790_Owner* unk_60;
};

// UnkType_10b6a790::Unk_10b6a790
void UnkType_10b6a790::Unk_10b6a790()
{
    if ( unk_60 )
    {
        if ( unk_5c )
        {
            unk_5c->SetUnk38(L"");
        }
        unk_60->Unk_10d5ba90();
        unk_60->unk_20 = ( unk_60->unk_20 & ~0x0d ) | 2;
    }
    Unk_10b69740(0);
}
