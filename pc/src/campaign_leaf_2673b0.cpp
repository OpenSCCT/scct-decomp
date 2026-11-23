// campaign_leaf_2673b0.cpp -- a member function at VA 0x10b673b0: it clears bit 1 of the int at
// 0xec of the object the pointer at 0x5c0 of its target refers to, when there is a target and that
// pointer is set (the target is what the member at VA 0x10a45b50 of the object at 0x64 of the entry
// the member at VA 0x10a0e220 gives for the byte at 0x0c returns, both reached through the pointer
// at 0x1c). Then, when the pointer at 0x188 is set, the object it refers to has its pointer at 0x08
// set and that object's pointer at 0x1c is set, it clears bit 0 of the first's byte at 0x18 and
// passes 0 and 0 to the member at VA 0x10d308c0 of the object at 0x1c. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10b673b0_Flags
{
public:
    unsigned char unk_00[0xec];
    int unk_ec;
};

class UnkType_10b673b0_Target
{
public:
    unsigned char unk_000[0x5c0];
    UnkType_10b673b0_Flags* unk_5c0;
};

class UnkType_10b673b0_Lookup
{
public:
    UnkType_10b673b0_Target* Unk_10a45b50();
};

class UnkType_10b673b0_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b673b0_Lookup* unk_64;
};

class UnkType_10b673b0_Table
{
public:
    UnkType_10b673b0_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b673b0_Menu
{
public:
    // guess: the current target (an inline accessor; name invented)
    UnkType_10b673b0_Target* GetTarget()
    {
        return unk_04->Unk_10a0e220(unk_0c)->unk_64->Unk_10a45b50();
    }

    int unk_00;
    UnkType_10b673b0_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b673b0_Control
{
public:
    void Unk_10d308c0(int First, int Second);
};

class UnkType_10b673b0_Part
{
public:
    int unk_00;
    int unk_04;
    UnkType_10b673b0_Control* unk_08;
};

class UnkType_10b673b0_Holder
{
public:
    // guess: the part at 0x14 (an inline accessor; name invented)
    UnkType_10b673b0_Part* GetPart()
    {
        return &unk_14;
    }

    unsigned char unk_00[0x14];
    UnkType_10b673b0_Part unk_14;
};

class UnkType_10b673b0_Item
{
public:
    unsigned char unk_00[0x08];
    UnkType_10b673b0_Holder* unk_08;
    unsigned char unk_0c[0x18 - 0x0c];
    unsigned char unk_18 : 1;
};

class UnkType_10b673b0
{
public:
    void Unk_10b673b0();

private:
    unsigned char unk_000[0x1c];
    UnkType_10b673b0_Menu* unk_01c;
    unsigned char unk_020[0x188 - 0x020];
    UnkType_10b673b0_Item* unk_188;
};

// UnkType_10b673b0::Unk_10b673b0
void UnkType_10b673b0::Unk_10b673b0()
{
    if ( unk_01c->GetTarget() && unk_01c->GetTarget()->unk_5c0 )
    {
        unk_01c->GetTarget()->unk_5c0->unk_ec &= ~2;
    }
    UnkType_10b673b0_Item* Item = unk_188;
    if ( Item && Item->unk_08 && Item->unk_08->GetPart() && Item->unk_08->GetPart()->unk_08 )
    {
        Item->unk_18 = 0;
        Item->unk_08->GetPart()->unk_08->Unk_10d308c0(0, 0);
    }
}
