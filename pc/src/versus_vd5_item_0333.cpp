// Work item 0333: Versus RVA 0x10df70 and 0x10dfb0 (LTCG units).
// 0x10df70 is UNetConnection::PreSend in shape: the bit writer at +0x23c is
// written with WriteInt(OutPacketId, MAX_PACKETID = 0x4000), its bit count
// (word at +0x288 = +0x23c+0x4c) is checked against the packet limit and
// FlushNet (vtable +0x70) is called when the next send would not fit.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
};
extern FMalloc *GMalloc;

extern BYTE GShift[8];          // bit masks used by FBitWriter
BYTE appCeilLogTwo(DWORD Arg);  // retail 0x12050

// Packet bit writer (layout recovered from WriteInt at 0x220a50).
class FBitWriter
{
public:
    char Pad00[0x2c];
    INT ArIsError;   // +0x2c
    char Pad30[0x40 - 0x30];
    BYTE *Buffer;    // +0x40
    char Pad44[0x4c - 0x44];
    _WORD Num;       // +0x4c
    _WORD Max;       // +0x4e

    void WriteInt(DWORD Value, DWORD ValueMax);
};

class UNetConnection
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual void RemoveEntry(void *Entry, INT Flags); // +0x6c (unidentified)
    virtual void FlushNet();                          // +0x70

    char Pad004[0xc0 - 4];
    INT MaxPacketBits;           // +0xc0
    char Pad0c4[0x23c - 0xc4];
    FBitWriter Out;              // +0x23c
    char Pad28c[0xee0 - 0x23c - sizeof(FBitWriter)];
    INT OutPacketId;             // +0xee0
    char Pad0ee4[0x26f0 - 0xee4];
    void **Entries;              // +0x26f0 (TArray<void*>, unidentified)
    INT EntryNum;                // +0x26f4
    INT EntryMax;                // +0x26f8

    void PreSend(INT SizeBits);
    void EmptyEntries();
};

void UNetConnection::PreSend(INT SizeBits)
{
    if (Out.Num + SizeBits + 1 > MaxPacketBits)
        FlushNet();
    if (Out.Num == 0)
        Out.WriteInt(OutPacketId, 0x4000);
}

void UNetConnection::EmptyEntries()
{
    for (INT i = 0; i < EntryNum; i++)
        RemoveEntry(Entries[i], 0);
    EntryNum = 0;
    if (EntryMax != 32) {
        EntryMax = 32;
        if (Entries == 0)
            Entries = (void **)GMalloc->Malloc(32 * sizeof(void *), L"FArray::Empty");
        else
            Entries = (void **)GMalloc->Realloc(Entries, 32 * sizeof(void *), L"FArray");
    }
}

// Scaffolding for the link, not part of the unit. WriteInt (retail 0x220a50,
// its own LTCG unit) is defined so the linker gives it the retail convention.
void FBitWriter::WriteInt(DWORD Value, DWORD ValueMax)
{
    if (Num + appCeilLogTwo(ValueMax) > Max) {
        ArIsError = 1;
        return;
    }
    DWORD NewValue = 0;
    for (DWORD Mask = 1; NewValue + Mask < ValueMax && Mask; Mask *= 2, Num++) {
        if (Value & Mask) {
            Buffer[Num >> 3] += GShift[Num & 7];
            NewValue += Mask;
        }
    }
}
void Escape(void *);
void Driver_10df70(UNetConnection *P, INT N) { P->PreSend(N); }
void Driver_10df70_b(UNetConnection *P, INT N) { P->PreSend(N * 2); P->FlushNet(); }
void Driver_10df70_c(UNetConnection *P) { P->PreSend(4); P->Slot00(); }
void Driver_10df70_d(UNetConnection *P, INT N) { P->Slot01(); P->PreSend(N + 9); }
void Driver_10dfb0(UNetConnection *P) { Escape(&GMalloc); P->EmptyEntries(); P->EmptyEntries(); }
