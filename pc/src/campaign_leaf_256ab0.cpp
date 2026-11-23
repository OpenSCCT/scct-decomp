// campaign_leaf_256ab0.cpp -- a member function at VA 0x10b56ab0: it clears the text of the objects
// the pointers at 0x48 and 0x4c refer to, when set (each one's label at 0x38 takes L"" and the
// length the free function at VA 0x10f32740 gives for it, and its virtual slot 5 of its base at
// 0x08 is called when its int at 0x34 is set). When the pointer at 0x44 is set, it clears that
// object's pointer at 0x2c, first passing the int at 0x34 and a copy of the int at 0x04 of what
// that pointer refers to (when set) to the member at VA 0x10a0f320 of the object the pointer at
// 0x04 of the object the pointer at 0x14 refers to. The class, method and member names are
// invented; the offsets, addresses, string and slot are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b56ab0_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b56ab0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b56ab0_Base8
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

class UnkType_10b56ab0_Text : public UnkType_10b56ab0_Base0, public UnkType_10b56ab0_Base8
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
    UnkType_10b56ab0_Label unk_38;
};

class UnkType_10b56ab0_Ref
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10b56ab0_Slot
{
public:
    unsigned char unk_00[0x2c];
    UnkType_10b56ab0_Ref* unk_2c;
};

class UnkType_10b56ab0_Registry
{
public:
    void Unk_10a0f320(int Owner, int* Id);
};

class UnkType_10b56ab0_Owner
{
public:
    int unk_00;
    UnkType_10b56ab0_Registry* unk_04;
};

class UnkType_10b56ab0
{
public:
    void Unk_10b56ab0();

private:
    unsigned char unk_00[0x14];
    UnkType_10b56ab0_Owner* unk_14;
    unsigned char unk_18[0x34 - 0x18];
    int unk_34;
    unsigned char unk_38[0x44 - 0x38];
    UnkType_10b56ab0_Slot* unk_44;
    UnkType_10b56ab0_Text* unk_48;
    UnkType_10b56ab0_Text* unk_4c;
};

// UnkType_10b56ab0::Unk_10b56ab0
void UnkType_10b56ab0::Unk_10b56ab0()
{
    if ( unk_48 )
    {
        unk_48->SetUnk38(L"");
    }
    if ( unk_4c )
    {
        unk_4c->SetUnk38(L"");
    }
    if ( unk_44 )
    {
        if ( unk_44->unk_2c )
        {
            int Id = unk_44->unk_2c->unk_04;
            unk_14->unk_04->Unk_10a0f320(unk_34, &Id);
        }
        unk_44->unk_2c = 0;
    }
}
