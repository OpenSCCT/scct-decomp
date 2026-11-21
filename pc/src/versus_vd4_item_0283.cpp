// Work item 0283: RVA 0x6cf50-0x6d2e5 (LTCG-compiled object).
// Unnamed classes: no vtable label or string evidence for names here.
// UnnamedOwner_6cf50 holds a game/settings object at +0x108 and a pointer to a
// page table at +0x2af10. The table holds a mode flag at +0x198, a default value
// at +0x1a0 and page pointers from +0x534; each page holds 0x7c-byte cells from +0x34.
// Status: 0x6d1e0, 0x6d210, 0x6d260 match (ltcg /O2 /Gy). 0x6d180 and 0x6d2a0 are
// near: same body, but retail keeps Owner on the stack and loads it early.
// 0x6cf50 is not written: it calls 0x6d360 and 0x6d6f0 with custom LTCG
// register conventions, which need those callees defined in the same unit.
typedef int INT;

struct UnnamedOwner_6cf50;

struct UnnamedCell_6cf50
{
    INT Value;      // 0x00
    INT A04;        // 0x04
    INT A08;        // 0x08
    INT A0c;        // 0x0c
    INT A10;        // 0x10
    INT Style;      // 0x14
    INT A18;        // 0x18
    INT A1c;
    INT A20;        // 0x20
    INT A24;        // 0x24
    INT A28;        // 0x28
    INT A2c;        // 0x2c
    INT A30;        // 0x30
    INT A34;
    INT A38;        // 0x38
    INT Rest[(0x7c - 0x3c) / 4];

    void InitA(UnnamedOwner_6cf50 *Owner, INT InValue);
    void InitB(UnnamedOwner_6cf50 *Owner, INT Unused);
    void InitC(UnnamedOwner_6cf50 *Owner);
    void InitD(UnnamedOwner_6cf50 *Owner, INT Unused);
    void InitE(UnnamedOwner_6cf50 *Owner);
};

struct UnnamedPage_6cf50
{
    INT Kind;       // 0x00
    INT P04;
    INT P08;
    INT P0c;        // 0x0c
    INT P10;        // 0x10
    INT P14;        // 0x14
    INT P18;
    INT P1c;
    INT P20;        // 0x20
    INT P24;        // 0x24
    INT P28;        // 0x28
    INT Colour;     // 0x2c
    INT Count;      // 0x30
    UnnamedCell_6cf50 Cells[1];   // 0x34
};

struct UnnamedTable_6cf50
{
    unsigned char Pad0[0x198];
    INT Mode;                       // 0x198
    INT Pad19c;
    INT DefaultValue;               // 0x1a0
    unsigned char Pad1[0x534 - 0x1a4];
    UnnamedPage_6cf50 *Pages[1];    // 0x534
};

struct UnnamedOwner_6cf50
{
    unsigned char Pad0[0x2af10];
    UnnamedTable_6cf50 *Table;      // 0x2af10
};

#pragma auto_inline(off)
// RVA 0x6d180
void UnnamedCell_6cf50::InitA(UnnamedOwner_6cf50 *Owner, INT InValue)
{
    A20 = 2;
    A18 = 2;
    A28 = 1;
    A24 = 1;
    Style = Owner->Table->Mode ? 5 : 4;
    Value = InValue;
    A04 = 3;
    A08 = 3;
    A30 = 1;
    A38 = 0;
}

// RVA 0x6d1e0
void UnnamedCell_6cf50::InitB(UnnamedOwner_6cf50 *Owner, INT Unused)
{
    A24 = 0;
    A2c = 0;
    Style = Owner->Table->Mode ? 5 : 4;
    A18 = 4;
}

// RVA 0x6d210
void UnnamedCell_6cf50::InitC(UnnamedOwner_6cf50 *Owner)
{
    A20 = 0;
    A24 = Owner->Table->Mode ? 0 : A24;
    Style = Owner->Table->Mode ? 7 : 2;
    A28 = 0;
    A18 = 2;
}

// RVA 0x6d260
void UnnamedCell_6cf50::InitD(UnnamedOwner_6cf50 *Owner, INT Unused)
{
    A20 = 0;
    A24 = 1;
    Style = Owner->Table->Mode ? 5 : 4;
    A2c = 1;
    A18 = 3;
}

// RVA 0x6d2a0
void UnnamedCell_6cf50::InitE(UnnamedOwner_6cf50 *Owner)
{
    A2c = 3;
    A24 = 3;
    A28 = 1;
    A20 = 1;
    A18 = 4;
    Style = Owner->Table->Mode ? 5 : 4;
    Value = 0;
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Driver_6d180(UnnamedOwner_6cf50 *O, INT Page, INT Idx)
{
    O->Table->Pages[Page]->Cells[Idx].InitA(O, O->Table->DefaultValue);
    O->Table->Pages[Idx]->Cells[Page].InitA(O, O->Table->DefaultValue);
}
void Driver_6d1e0(UnnamedOwner_6cf50 *O, INT Page, INT Idx)
{
    O->Table->Pages[Page]->Cells[0].InitB(O, 0);
    O->Table->Pages[Idx]->Cells[0].InitB(O, 0);
}
void Driver_6d210(UnnamedOwner_6cf50 *O)
{
    O->Table->Pages[0]->Cells[0].InitC(O);
    O->Table->Pages[1]->Cells[0].InitC(O);
}
void Driver_6d260(UnnamedOwner_6cf50 *O, INT Page, INT Idx)
{
    O->Table->Pages[Page]->Cells[Idx].InitD(O, 1);
    O->Table->Pages[Idx]->Cells[Page].InitD(O, 1);
}
void Driver_6d2a0(UnnamedOwner_6cf50 *O, INT Page, INT Idx)
{
    O->Table->Pages[Page]->Cells[Idx].InitE(O);
    O->Table->Pages[Idx]->Cells[Page].InitE(O);
}
