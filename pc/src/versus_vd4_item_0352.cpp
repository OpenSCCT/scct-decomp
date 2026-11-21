// Work item 0352: Versus RVA 0x9a6b0-0x9a84a.
// Class names are neutral except UESBPatch (from the reflected vtable label).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FVector { FLOAT X, Y, Z; };

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Unnamed float constants bound from retail.
extern const FLOAT Const_10c4da04;
extern const FLOAT Const_10c4da08;
extern const FLOAT Const_10c10c30;
extern const FLOAT Const_10c10a60;
extern const FLOAT Const_10c109fc;

struct UnnamedInner_1a0 { char Pad[0x3b0]; FLOAT Limit; };

struct UnnamedEntry_2fc { void *Key; INT Pad[3]; };

struct UnnamedOwner_54 {
    char Pad0[0x80];
    FVector Vec80;            // 0x80
    char Pad8c[0xe0 - 0x8c];
    FVector VecE0;            // 0xe0
    char PadEc[0x1a0 - 0xec];
    UnnamedInner_1a0 *Inner;  // 0x1a0
    char Pad1a4[0x2fc - 0x1a4];
    UnnamedEntry_2fc *Entries;// 0x2fc
    INT EntryNum;             // 0x300
    char Pad304[0x380 - 0x304];
    INT Value380;             // 0x380
    DWORD Bit0 : 1;           // 0x384
    DWORD Bit1 : 1;
    DWORD Bit2 : 1;
};

class UESBPatch {
public:
    virtual void VSlot00(); virtual void VSlot01(); virtual void VSlot02(); virtual void VSlot03();
    virtual void VSlot04(); virtual void VSlot05(); virtual void VSlot06(); virtual void VSlot07();
    virtual void VSlot08(); virtual void VSlot09(); virtual void VSlot10(); virtual void VSlot11();
    virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15();
    virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19();
    virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23();
    virtual void VSlot24(); virtual void VSlot25(); virtual void VSlot26(); virtual void VSlot27();
    virtual void VSlot28(); virtual void VSlot29(); virtual void VSlot30(); virtual void VSlot31();
    virtual void VSlot32(); virtual void VSlot33(); virtual void VSlot34();
    virtual void Slot35(INT A, INT B);   // 0x8c
    virtual void Slot36(INT B);          // 0x90
    virtual void Slot37();               // 0x94
    virtual void Slot38();               // 0x98
    virtual void Slot39();               // 0x9c
    virtual void Slot40();               // 0xa0
    virtual void Slot41();               // 0xa4
    virtual void Slot42(); virtual void Slot43(); virtual void Slot44(); virtual void Slot45();
    virtual void Slot46();               // 0xb8
    virtual void Slot47();               // 0xbc

    void SetLevel(FLOAT Level);
    UBOOL HasEntry(void *Key);

    char Pad04[0x54 - 4];
    UnnamedOwner_54 *Owner;   // 0x54
    char Pad58[0x11c - 0x58];
    void *Data;               // 0x11c
    INT ArrayNum;             // 0x120
    INT ArrayMax;             // 0x124
    FLOAT Offset;             // 0x128
    FLOAT Level;              // 0x12c
    FLOAT SmoothLevel;        // 0x130
    char Pad134[0x13c - 0x134];
    FVector SavedVec80;       // 0x13c
    FVector SavedVecE0;       // 0x148
    INT SavedValue380;        // 0x154
    UBOOL SavedBit2;          // 0x158
};

inline FLOAT Clamp(FLOAT X, FLOAT Min, FLOAT Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

// RVA 0x9a6b0, UESBPatch vtable slot 35.
void UESBPatch::Slot35(INT A, INT B)
{
    if (Owner && Const_10c4da04 + Offset > Owner->Inner->Limit)
        Slot36(B);
}

// RVA 0x9a6f0
void UESBPatch::SetLevel(FLOAT NewLevel)
{
    SmoothLevel = Level = Clamp(NewLevel, Const_10c10c30, Const_10c10a60) * Const_10c4da08
        + (Const_10c109fc - Const_10c4da08) * SmoothLevel;
    Slot37();
    Slot38();
    Slot39();
    Slot40();
    Slot41();
    Slot46();
    Slot47();
    ArrayNum = 0;
    if (Data) {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
    SavedVecE0 = Owner->VecE0;
    SavedVec80 = Owner->Vec80;
    SavedValue380 = Owner->Value380;
    SavedBit2 = Owner->Bit2;
}

// RVA 0x9a820 (LTCG: Key passed in ESI).
__declspec(noinline) UBOOL UESBPatch::HasEntry(void *Key)
{
    for (INT i = 0; i < Owner->EntryNum; i++)
        if (Owner->Entries[i].Key == Key)
            return 1;
    return 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
INT Driver_9a820(UESBPatch *P, void **Keys, INT N)
{
    INT Count = 0;
    for (INT i = 0; i < N; i++) {
        if (P->HasEntry(Keys[i])) Count++;
        if (P->HasEntry(Keys[i + 1])) Count += 2;
        if (P->HasEntry(Keys[i + 2])) Count += 3;
        if (P->HasEntry(Keys[i + 3])) Count += 4;
        Escape(P);
    }
    return Count;
}
