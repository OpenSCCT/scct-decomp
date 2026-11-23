// campaign_leaf_25f8a0.cpp -- a member function at VA 0x10b5f8a0 taking an int: it sets the byte at
// 0x40 when the byte at 0x28 of the object the global at VA 0x111f9f64 points to differs from the
// int, passes the int to the member at VA 0x10d5f720 of the object the pointer at 0x4c refers to,
// and gives the text of the int formatted with L"%i" through the free function at VA 0x10cce920
// to the object the pointer at 0x54 refers to (its label at 0x38 takes the text and the length the
// free function at VA 0x10f32740 gives for it, and its virtual slot 5 of its base at 0x08 is
// called when its int at 0x34 is set). The string is then destroyed: emptied, its block
// reallocated to no bytes through Realloc of the allocator the global at VA 0x111c88a0 points
// to, tagged L"FArray::_WORD"; then the member at VA 0x10907710 removes all its 2-byte
// characters, its block is freed through that allocator's Free and it is cleared. The class,
// method, member, parameter and global names are invented; the offsets, addresses, strings and
// slot are the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111f9f64.h"

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b5f8a0_Array
{
public:
    void Unk_10907710(int Index, int Count, int Size);

    // guess: removes the characters and frees the block (an inline destructor)
    ~UnkType_10b5f8a0_Array()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_08 = 0;
        unk_04 = 0;
    }

protected:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b5f8a0_String : public UnkType_10b5f8a0_Array
{
public:
    // guess: empties the string first (an inline destructor)
    ~UnkType_10b5f8a0_String()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::_WORD");
    }

    // guess: the text, or L"" when empty (an inline accessor; name invented)
    const unsigned short* GetText() const
    {
        return unk_04 ? (const unsigned short*)unk_00 : L"";
    }
};

class UnkType_10b5f8a0_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b5f8a0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5f8a0_Base8
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

class UnkType_10b5f8a0_Text : public UnkType_10b5f8a0_Base0, public UnkType_10b5f8a0_Base8
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
    UnkType_10b5f8a0_Label unk_38;
};

UnkType_10b5f8a0_String __cdecl Unk_10cce920(const unsigned short* Format, ...);

class UnkType_10b5f8a0_Slider
{
public:
    void Unk_10d5f720(int Value);
};

class UnkType_10b5f8a0
{
public:
    void Unk_10b5f8a0(int Value);

private:
    unsigned char unk_00[0x40];
    bool unk_40;
    unsigned char unk_41[0x4c - 0x41];
    UnkType_10b5f8a0_Slider* unk_4c;
    unsigned char unk_50[0x54 - 0x50];
    UnkType_10b5f8a0_Text* unk_54;
};

// UnkType_10b5f8a0::Unk_10b5f8a0
void UnkType_10b5f8a0::Unk_10b5f8a0(int Value)
{
    if ( GUnk_111f9f64->unk_28 != Value )
    {
        unk_40 = true;
    }
    unk_4c->Unk_10d5f720(Value);
    UnkType_10b5f8a0_String Text = Unk_10cce920(L"%i", Value);
    unk_54->SetUnk38(Text.GetText());
}
