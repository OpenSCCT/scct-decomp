// Work item 0329: Versus RVA 0x10c760-0x10cd40 (LTCG object).
// Class names are neutral: no vtable labels or strings identify the owner.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;

extern "C" __declspec(dllimport) int __cdecl rand(void);
extern "C" void *__cdecl _alloca(unsigned int);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

// One 0x1048-byte slot filled from a source record (FUN_10a85800).
struct UnnamedSlot_1048 { BYTE Data[0x1048]; };
void UnnamedSlot_Consume(void *Buffer, INT Size);

// FUN_10a85800: copies at most 0x48 bytes of Source onto the stack and parses them into Slot.
void LoadSlot(UnnamedSlot_1048 *Slot, const void *Source, INT Size)
{
    if (Size > 0x48) Size = 0x48;
    void *Buffer = _alloca((Size + 3) & ~3);
    memcpy(Buffer, Source, Size);
    UnnamedSlot_Consume(Buffer, Size);
    Slot->Data[0] = 0;
}

extern void **GSlotSources;   // DAT_10cbc5dc
extern INT GSlotSourceCount;  // DAT_10cbc5e0
extern const FLOAT GRandScale; // 0x10c10a88, 1/32767

class UnnamedClass_10c760
{
public:
    BYTE Pad0[0x2714];
    UnnamedSlot_1048 Slots[2];  // 0x2714
    BYTE SlotKeys[2];           // 0x47a4
    BYTE Pad47a6[2];
    INT Countdown;              // 0x47a8
    INT CurrentSlot;            // 0x47ac

    UnnamedSlot_1048 *GetSlot(BYTE Key);
    void Tick();
};

UnnamedSlot_1048 *UnnamedClass_10c760::GetSlot(BYTE Key)
{
    if (Key == SlotKeys[0])
        return &Slots[0];
    if (Key == SlotKeys[1])
        return &Slots[1];
    INT Index = 1 - CurrentSlot;
    CurrentSlot = Index;
    SlotKeys[Index] = Key;
    UnnamedSlot_1048 *Slot = &Slots[Index];
    LoadSlot(Slot, GSlotSources[Key], 0x48);
    return Slot;
}

void UnnamedClass_10c760::Tick()
{
    if (--Countdown < 0)
    {
        Countdown = rand() * 999 / 0x7fff;
        FLOAT R = rand() * GRandScale;
        BYTE Key = (BYTE)(INT)(GSlotSourceCount * R);
        if (Key == SlotKeys[0])
            CurrentSlot = 0;
        else if (Key == SlotKeys[1])
            CurrentSlot = 1;
        else
            GetSlot(Key);
    }
}

typedef unsigned short WORD;
inline void *operator new(unsigned int, void *Where) { return Where; }

// Helper owned by the members below (called from their out-of-line constructors).
struct UnnamedPart { UnnamedPart(); ~UnnamedPart(); INT Value; };
void UnnamedPart_Use(UnnamedPart *, void *);

// Member at +0x70 (constructor FUN_10a33490, out of line in retail).
struct UnnamedMember_70
{
    UnnamedPart A, B;
    BYTE Pad[0x98 - 8];
    UnnamedMember_70();
    ~UnnamedMember_70();
};
UnnamedMember_70::UnnamedMember_70() { UnnamedPart_Use(&A, this); UnnamedPart_Use(&B, this); }

// Member at +0x108: two words cleared by an inline constructor.
struct UnnamedMember_108
{
    WORD First; BYTE Pad0[6];
    WORD Second; BYTE Pad1[14];
    UnnamedMember_108() { First = 0; Second = 0; }
    ~UnnamedMember_108();
};

// Base with a size parameter (constructor FUN_10b207b0, out of line in retail).
class UnnamedSizedBase
{
public:
    UnnamedPart A, B;
    BYTE Pad[0x50 - 12];
    UnnamedSizedBase(INT Size);
    virtual ~UnnamedSizedBase();
};
UnnamedSizedBase::UnnamedSizedBase(INT Size) { UnnamedPart_Use(&A, this); A.Value = Size; UnnamedPart_Use(&B, this); }

class UnnamedSizedDerived : public UnnamedSizedBase   // vtable 0x10c04760
{
public:
    BYTE Extra[0x11c - 0x50];
    UnnamedSizedDerived() : UnnamedSizedBase(0) {}
    virtual ~UnnamedSizedDerived();
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct __declspec(novtable) UnnamedPrimaryBase
{
    virtual ~UnnamedPrimaryBase();
    BYTE Pad[0x24];
};
struct UnnamedInterfaceA { virtual void InterfaceA(); };   // vtable 0x10c0e3f8
struct UnnamedInterfaceB { virtual void InterfaceB(); };   // vtable 0x10c0e71c

// Owner of the two slots above (vtables 0x10c038b8 / 0x10c03934 / 0x10c0393c).
class UnnamedClass_10c860 : public UnnamedPrimaryBase, public UnnamedInterfaceA, public UnnamedInterfaceB
{
public:
    BYTE Pad30[0x70 - 0x30];
    UnnamedMember_70 Member70;          // 0x70
    UnnamedMember_108 Member108;        // 0x108
    UnnamedSizedDerived Member120;      // 0x120
    UnnamedSizedBase Member23c;         // 0x23c
    UnnamedSizedBase Member28c;         // 0x28c
    BYTE Pad2dc[0x26e4 - 0x2dc];
    FVector Vectors[4];                 // 0x26e4
    UnnamedClass_10c860();
    virtual ~UnnamedClass_10c860();
    virtual void InterfaceA();
    virtual void InterfaceB();
};

UnnamedClass_10c860::UnnamedClass_10c860()
    : Member23c(0), Member28c(0x40)
{
    Vectors[0].X = 0; Vectors[0].Y = 0; Vectors[0].Z = 0;
    Vectors[1].X = 0; Vectors[1].Y = 0; Vectors[1].Z = 0;
    Vectors[2].X = 0; Vectors[2].Y = 0; Vectors[2].Z = 0;
    Vectors[3].X = 0; Vectors[3].Y = 0; Vectors[3].Z = 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_10c760(UnnamedClass_10c760 *C, BYTE K, UnnamedSlot_1048 *S, void *P, INT N)
{
    Escape(&GSlotSources); Escape(&GSlotSourceCount);
    C->GetSlot(K);
    C->Tick();
    LoadSlot(S, P, N);
}
void Driver_10c860(void *Where) { new (Where) UnnamedClass_10c860; }
