// campaign_leaf_250750.cpp -- a member function at VA 0x10b50750 taking a flag: it stores the flag
// in the byte at 0x944 and, when that changed it, clears the text of the object the pointer at
// 0x920 refers to (its label at 0x38 takes L"" and the length the free function at VA 0x10f32740
// gives for it, and its virtual slot 5 of its base at 0x08 is called when its int at 0x34 is set).
// It then sets bit 2 of that object's byte at 0x58 to the inverse of the flag, passes L"" when the
// flag is set (or else the text of the string at VA 0x1122dd64) to its own member at VA
// 0x10b4fe40, and passes the flag to the member at VA 0x10d32e70 of the objects the pointers at
// 0x918 and 0x91c refer to. The class, method, member, parameter and global names are invented;
// the offsets, addresses, string and slot are the binary's.

#include "campaign_global_1122dd64.h"

int __cdecl Unk_10f32740(const unsigned short* Text);

class UnkType_10b50750_Label
{
public:
    void Unk_10ad8220(const unsigned short* Text, int Length);

private:
    int unk_00;
};

class UnkType_10b50750_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b50750_Base8
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

class UnkType_10b50750_Text : public UnkType_10b50750_Base0, public UnkType_10b50750_Base8
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
    UnkType_10b50750_Label unk_38;
    unsigned char unk_3c[0x58 - 0x3c];
    unsigned char unk_58 : 2;
    unsigned char unk_58_2 : 1;
};

class UnkType_10b50750_Part
{
public:
    void Unk_10d32e70(bool Flag);
};

class UnkType_10b50750
{
public:
    void Unk_10b4fe40(const unsigned short* Text);
    void Unk_10b50750(bool Flag);

private:
    unsigned char unk_000[0x918];
    UnkType_10b50750_Part* unk_918;
    UnkType_10b50750_Part* unk_91c;
    UnkType_10b50750_Text* unk_920;
    unsigned char unk_924[0x944 - 0x924];
    bool unk_944;
};

// UnkType_10b50750::Unk_10b50750
void UnkType_10b50750::Unk_10b50750(bool Flag)
{
    bool Changed = false;
    if ( Flag != unk_944 )
    {
        Changed = true;
    }
    unk_944 = Flag;
    if ( Changed )
    {
        unk_920->SetUnk38(L"");
    }
    unk_920->unk_58_2 = !Flag;
    Unk_10b4fe40(Flag ? L"" : *GUnk_1122dd64);
    unk_918->Unk_10d32e70(Flag);
    unk_91c->Unk_10d32e70(Flag);
}
