// Work item 0286: Versus RVA 0x71b00 (LTCG unit, custom calling conventions).
// Class and field names are neutral: no symbol evidence for this subsystem.
typedef int INT;

// 0x7c-byte entry stored in a page (array at page + 0x34).
struct UnnamedEntry_6d180
{
    INT Field00;
    INT Field04;
    INT Field08;
    INT Field0C;
    INT Field10;
    INT Field14;
    INT Field18;
    INT Field1C;
    INT Field20;
    INT Field24;
    INT Field28;
    INT Field2C;
    INT Field30;
    INT Field34;
    INT Field38;
    INT Pad[(0x7c - 0x3c) / 4];
};

struct UnnamedPage_71b00
{
    INT Pad0[0x30 / 4];
    INT Count;                          // +0x30
    UnnamedEntry_6d180 Entries[16];     // +0x34
};

struct UnnamedState_71b00
{
    char Pad0[0x198];
    INT Flag198;                        // +0x198
    INT Pad19C;
    INT Value1A0;                       // +0x1a0
    char Pad1A4[0x534 - 0x1a4];
    UnnamedPage_71b00 *Pages[8];        // +0x534
    INT Flag554;                        // +0x554
};

struct UnnamedOwner_71b00
{
    char Pad0[0x2af10];
    UnnamedState_71b00 *State;          // +0x2af10
    void Fn_71b00();
};

// RVA 0x6d210 (entry in EAX, owner in EDX). Defined here, kept out of line,
// so LTCG gives it the same register convention as retail (not part of this item).
__declspec(noinline) void InitEntryA_6d210(UnnamedEntry_6d180 *E, UnnamedOwner_71b00 *Owner)
{
    E->Field20 = 0;
    E->Field24 = Owner->State->Flag198 ? 0 : E->Field24;
    E->Field14 = Owner->State->Flag198 ? 7 : 2;
    E->Field28 = 0;
    E->Field18 = 2;
}

// RVA 0x6d180 (entry in EAX, owner and value on the stack)
__declspec(noinline) void __stdcall InitEntryB_6d180(UnnamedOwner_71b00 *Owner, UnnamedEntry_6d180 *E, INT Value)
{
    E->Field20 = 2;
    E->Field18 = 2;
    E->Field28 = 1;
    E->Field24 = 1;
    INT Flag = Owner->State->Flag198;
    E->Field00 = Value;
    E->Field04 = 3;
    E->Field08 = 3;
    E->Field30 = 1;
    E->Field14 = (Flag != 0) + 4;
    E->Field38 = 0;
}

void UnnamedOwner_71b00::Fn_71b00()
{
    InitEntryA_6d210(&State->Pages[0]->Entries[0], this);
    INT Count = 1;
    if (State->Value1A0)
    {
        InitEntryB_6d180(this, &State->Pages[0]->Entries[1], State->Value1A0);
        Count = 2;
    }
    State->Pages[0]->Count = Count;
    State->Flag554 = 1;
}

// Scaffolding for the link, not part of the unit.
void Driver_71b00(UnnamedOwner_71b00 *O) { O->Fn_71b00(); }
void Driver2_71b00(UnnamedEntry_6d180 *E, UnnamedOwner_71b00 *O, INT V)
{
    InitEntryA_6d210(E, O); InitEntryB_6d180(O, E, V);
    InitEntryA_6d210(E + 2, O); InitEntryB_6d180(O, E + 3, V);
    InitEntryA_6d210(E + 4, O); InitEntryB_6d180(O, E + 5, V);
}
