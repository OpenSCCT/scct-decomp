// Work item 0284: Versus RVA 0x6d2f0 and 0x6d360 (LTCG, custom register conventions).
// Class and field names are neutral; no symbol evidence ties these to UE2 names.

typedef int INT;
typedef unsigned char BYTE;

// 15-dword state block filled by InitState_6d2f0 (eax in retail).
struct UnnamedState_6d2f0
{
    INT Value;      // 0x00
    INT A;          // 0x04
    INT B;          // 0x08
    INT Pad0C[2];   // 0x0c
    INT Mode;       // 0x14
    INT F18;        // 0x18
    INT Pad1C;      // 0x1c
    INT F20;        // 0x20
    INT F24;        // 0x24
    INT F28;        // 0x28
    INT Pad2C;      // 0x2c
    INT F30;        // 0x30
    INT Pad34;      // 0x34
    INT F38;        // 0x38
};

struct UnnamedInner_198
{
    BYTE Pad[0x194];
    INT Enabled;    // 0x194
    INT Flag;       // 0x198
    INT Pad19C;     // 0x19c
    INT Value;      // 0x1a0
    BYTE Pad1A4[0x534 - 0x1a4];
    BYTE *Groups[1];    // 0x534
};

struct UnnamedOwner_2af10
{
    BYTE Pad[0x2af10];
    UnnamedInner_198 *Inner;    // 0x2af10
};

void __stdcall InitState_6d2f0(UnnamedState_6d2f0 *S, INT Value, UnnamedOwner_2af10 *Owner, INT Enabled)
{
    S->F28 = 0;
    S->F20 = 2;
    S->F24 = 0;
    S->F18 = 2;
    if (Value == 0)
        S->Mode = 3;
    else if (Enabled == 0)
        S->Mode = 2;
    else
        S->Mode = (Owner->Inner->Flag != 0) + 4;
    S->Value = Value;
    S->A = 1;
    S->B = 1;
    S->F30 = 1;
    S->F38 = 0;
}

// Objects reached from the context at ebx in 0x6d360.
struct UnnamedLevel_4658
{
    BYTE Pad[0x4658];
    INT Default;    // 0x4658
};

struct UnnamedView_130
{
    BYTE Pad[0x130];
    INT X;          // 0x130
    INT Y;          // 0x134
};

struct UnnamedResult_30
{
    BYTE Pad[0x30];
    INT Override;   // 0x30
};

struct UnnamedContext_108
{
    BYTE Pad[0x108];
    UnnamedLevel_4658 *Level;   // 0x108
    UnnamedView_130 *View;      // 0x10c
};

class UnnamedKey_8c
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual INT GetKey();   // vtable +0x8c
};

class UnnamedSource_90
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual UnnamedKey_8c *Resolve(INT X, INT Y, UnnamedView_130 *View);   // vtable +0x90
    BYTE Pad[0x59];
    BYTE ModeA;     // 0x5d
    BYTE ModeB;     // 0x5e
};

struct UnnamedEntry_6d360
{
    UnnamedResult_30 *Result;
    INT A;
    INT B;
    INT C;
};

UnnamedResult_30 * __stdcall Lookup_620f0(UnnamedContext_108 *Ctx, INT Key);

void FillEntry_6d360(UnnamedContext_108 *Ctx, UnnamedSource_90 *Src, UnnamedEntry_6d360 *Out)
{
    if (Src != 0) {
        UnnamedView_130 *View = Ctx->View;
        Out->Result = Lookup_620f0(Ctx, Src->Resolve(View->X, View->Y, View)->GetKey());
        if (Out->Result->Override) {
            Out->A = Ctx->Level->Default;
            Out->B = Ctx->Level->Default;
        } else {
            switch (Src->ModeA) {
            case 0: Out->A = 1; break;
            case 1: Out->A = 3; break;
            }
            switch (Src->ModeB) {
            case 0: Out->B = 1; break;
            case 1: Out->B = 3; break;
            }
        }
        Out->C = Ctx->Level->Default;
    } else {
        Out->Result = 0;
    }
}

// Scaffolding for the link, not part of the unit (mirrors the retail callers
// at 0x6ee7d and 0x70e47).
void Driver_6d2f0(UnnamedOwner_2af10 *Owner, INT Group, INT Index)
{
    UnnamedInner_198 *In = Owner->Inner;
    InitState_6d2f0((UnnamedState_6d2f0 *)(In->Groups[Group] + Index * 0x7c + 0x34), In->Value, Owner, In->Enabled);
}
void Driver_6d2f0b(UnnamedOwner_2af10 *Owner, INT Group, INT Index)
{
    UnnamedInner_198 *In = Owner->Inner;
    InitState_6d2f0((UnnamedState_6d2f0 *)(In->Groups[Group + 1] + Index * 0x7c + 0x34), In->Value, Owner, In->Enabled);
    InitState_6d2f0((UnnamedState_6d2f0 *)(In->Groups[Group + 2] + Index * 0x7c + 0x34), In->Value, Owner, In->Enabled);
    InitState_6d2f0((UnnamedState_6d2f0 *)(In->Groups[Group + 3] + Index * 0x7c + 0x34), In->Value, Owner, In->Enabled);
}
void Driver_6d360(UnnamedContext_108 *Ctx, UnnamedSource_90 *Src, UnnamedEntry_6d360 *Out)
{
    FillEntry_6d360(Ctx, Src, Out);
    Out[1].A = 2;
    Out[1].B = 1;
    Out[1].C = 1;
}
