/* Item 0303: three LTCG-specialised initialisers for a 0x3C-byte descriptor
   (RVA 0x7cd50, 0x7cda0, 0x7cdc0). The descriptor arrives in EAX; the first
   stack argument is unused in all three. No strings or vtables identify the
   type, so the names are neutral (UnnamedDesc_7cd50). */
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

struct UnnamedDesc_7cd50
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
};

void __stdcall InitDesc_7cd50(UnnamedDesc_7cd50 *D, INT Unused, INT Value, UBOOL Flag)
{
    D->Field28 = 1;
    D->Field18 = 2;
    if (Flag)
    {
        D->Field20 = 0;
        D->Field24 = 2;
        D->Field14 = 7;
    }
    else
    {
        D->Field20 = 2;
        D->Field14 = 2;
    }
    D->Field00 = Value;
    D->Field04 = 3;
    D->Field08 = 3;
    D->Field30 = 1;
    D->Field38 = 0;
}

void __stdcall InitDesc_7cda0(UnnamedDesc_7cd50 *D, INT Unused)
{
    D->Field2C = 1;
    D->Field18 = 3;
    D->Field20 = 0;
    D->Field14 = 2;
}

void __stdcall InitDesc_7cdc0(UnnamedDesc_7cd50 *D, INT Unused, UBOOL Flag, INT Value, UBOOL Flag2)
{
    D->Field28 = 0;
    D->Field24 = 0;
    D->Field20 = 2;
    D->Field18 = 2;
    if (Flag)
        D->Field14 = 7;
    else if (!Value)
        D->Field14 = 3;
    else
        D->Field14 = Flag2 ? 4 : 2;
    D->Field00 = Value;
    D->Field04 = 3;
    D->Field08 = 3;
    D->Field38 = 0;
    if (Value)
        D->Field30 = 1;
}

// Scaffolding for the link, not part of the unit.
#pragma inline_depth(0)
void Driver_7cd50(UnnamedDesc_7cd50 *D, INT U, INT V, UBOOL F)
{
    InitDesc_7cd50(D, U, V, F);
    InitDesc_7cd50(D + 1, V, U, F);
}
void Driver_7cda0(UnnamedDesc_7cd50 *D, INT U)
{
    InitDesc_7cda0(D, U);
    InitDesc_7cda0(D + 1, U);
}
void Driver_7cdc0(UnnamedDesc_7cd50 *D, INT U, UBOOL F, INT V, UBOOL F2)
{
    InitDesc_7cdc0(D, U, F, V, F2);
    InitDesc_7cdc0(D + 1, V, U, F, F2);
}
