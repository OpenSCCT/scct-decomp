// campaign_leaf_12e5f0.cpp -- one function at file offset 0x12e5f0, preferred VA 0x10a2e5f0.
// guess: attaches the object to its owner: stores the owner at offset 0xe0 and the flag at bit 0
// of 0x74; while the global at VA 0x11232794 is set it passes its value at 0x4c to its member at
// 0x118 (method at VA 0x10a2d970) and adds itself to the list at 0x39e4 of the owner's member at
// 0x7c (method at VA 0x10a2e0b0). It then calls its method at VA 0x10a2dbf0 with its member at
// 0x28 and true.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

#include "campaign_global_11232794.h"

class UnkType_10a2e5f0;

class UnkType_10a2e5f0_List
{
public:
    void Unk_10a2e0b0(UnkType_10a2e5f0* const& Item);
};

class UnkType_10a2e5f0_Level
{
public:
    unsigned char unk_0[0x39e4];
    UnkType_10a2e5f0_List unk_39e4;
};

class UnkType_10a2e5f0_Owner
{
public:
    unsigned char unk_0[0x7c];
    UnkType_10a2e5f0_Level* unk_7c;
};

class UnkType_10a2e5f0_Value
{
public:
    int unk_0;
};

class UnkType_10a2e5f0_Member
{
public:
    void Unk_10a2d970(UnkType_10a2e5f0_Value& Value);
};

class UnkType_10a2e5f0
{
public:
    unsigned char unk_0[0x28];
    void* unk_28;
    unsigned char unk_2c[0x4c - 0x2c];
    UnkType_10a2e5f0_Value unk_4c;
    unsigned char unk_50[0x74 - 0x50];
    unsigned int unk_74_0 : 1;
    unsigned char unk_78[0xe0 - 0x78];
    UnkType_10a2e5f0_Owner* unk_e0;
    unsigned char unk_e4[0x118 - 0xe4];
    UnkType_10a2e5f0_Member unk_118;

    void Unk_10a2e5f0(UnkType_10a2e5f0_Owner* Owner, int bFlag);
    void Unk_10a2dbf0(void* Value, int bFlag);
};

// UnkType_10a2e5f0::Unk_10a2e5f0
void UnkType_10a2e5f0::Unk_10a2e5f0(UnkType_10a2e5f0_Owner* Owner, int bFlag)
{
    unk_e0 = Owner;
    unk_74_0 = bFlag;
    if ( GUnk_11232794 )
    {
        unk_118.Unk_10a2d970(unk_4c);
        UnkType_10a2e5f0_Level* Level = unk_e0->unk_7c;
        if ( Level )
        {
            UnkType_10a2e5f0* Self = this;
            Level->unk_39e4.Unk_10a2e0b0(Self);
        }
    }
    Unk_10a2dbf0(unk_28, 1);
}
