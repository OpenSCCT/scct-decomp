// Work item 0181: Versus RVA 0xe04e0-0xe0535.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

// 0xe04e0: checks a slot in an 8-entry pointer table (neutral names; table at 0x10c924f0).
extern void *GSlotTable_e04e0[8];

__declspec(noinline) UBOOL IsSlotUsed_e04e0(INT Index)
{
    if (Index >= 0 && Index < 8 && GSlotTable_e04e0[Index] != 0)
        return 1;
    return 0;
}

// 0xe0500: walks a linked list of entries and releases those owned by Owner.
// Neutral names; layout from offsets only.
struct UnnamedEntry_e0500
{
    BYTE Pad0[0x50];
    UnnamedEntry_e0500 *Next;      // 0x50
    BYTE Pad54[0x6c - 0x54];
    INT Owner;                     // 0x6c
    BYTE Pad70[3];
    BYTE Flag;                     // 0x73
};

void __stdcall UnnamedFunc_a0e140(void *Context, UnnamedEntry_e0500 *Entry, INT Mode);

class UnnamedClass_e0500
{
public:
    BYTE Pad0[0x28];
    void *Context;                 // 0x28
    BYTE Pad2c[0x44 - 0x2c];
    UnnamedEntry_e0500 *Entries;   // 0x44

    void ReleaseOwned(INT Owner);
};

void UnnamedClass_e0500::ReleaseOwned(INT Owner)
{
    for (UnnamedEntry_e0500 *E = Entries; E; E = E->Next)
    {
        if (E->Owner == Owner && !E->Flag)
            UnnamedFunc_a0e140(Context, E, 0);
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
UBOOL Driver_e04e0(INT Index) { Escape(GSlotTable_e04e0); return IsSlotUsed_e04e0(Index) + IsSlotUsed_e04e0(Index ^ 3); }
