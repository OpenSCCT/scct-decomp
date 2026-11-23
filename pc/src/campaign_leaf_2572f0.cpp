// campaign_leaf_2572f0.cpp -- a member function at VA 0x10b572f0: it gives an empty wide string to
// the objects the pointers at 0x50 and 0x54 refer to (each one's label at 0x38 takes the text and
// the length the free function at VA 0x10f32740 gives for it, and its virtual slot 5 of its base
// at 0x08 is called when its int at 0x34 is set). Then, when the pointer at 0x48 is set, it passes
// the int at 0x34 and a copy of the int at 0x04 of the object that object's pointer at 0x2c refers
// to (when there is one) to the member at VA 0x10a0f320 of the object at 0x04 of the one the
// pointer at 0x14 refers to, and clears that pointer at 0x2c. The class, method and member names
// are invented; the offsets, addresses and slot are the binary's.

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b572f0_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b572f0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b572f0_Base8
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

class UnkType_10b572f0_Text : public UnkType_10b572f0_Base0, public UnkType_10b572f0_Base8
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
    UnkType_10b572f0_Label unk_38;
};

class UnkType_10b572f0_Handle
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10b572f0_Slot
{
public:
    unsigned char unk_00[0x2c];
    UnkType_10b572f0_Handle* unk_2c;
};

class UnkType_10b572f0_Table
{
public:
    void Unk_10a0f320(int Index, int* Value);
};

class UnkType_10b572f0_Owner
{
public:
    int unk_00;
    UnkType_10b572f0_Table* unk_04;
};

class UnkType_10b572f0
{
public:
    void Unk_10b572f0();

private:
    unsigned char unk_00[0x14];
    UnkType_10b572f0_Owner* unk_14;
    unsigned char unk_18[0x34 - 0x18];
    int unk_34;
    unsigned char unk_38[0x48 - 0x38];
    UnkType_10b572f0_Slot* unk_48;
    unsigned char unk_4c[0x50 - 0x4c];
    UnkType_10b572f0_Text* unk_50;
    UnkType_10b572f0_Text* unk_54;
};

// UnkType_10b572f0::Unk_10b572f0
void UnkType_10b572f0::Unk_10b572f0()
{
    unk_50->SetUnk38(L"");
    unk_54->SetUnk38(L"");
    if ( unk_48 )
    {
        if ( unk_48->unk_2c )
        {
            int Value = unk_48->unk_2c->unk_04;
            unk_14->unk_04->Unk_10a0f320(unk_34, &Value);
        }
        unk_48->unk_2c = 0;
    }
}
