// Work item 0331: UNetConnection::InitOut (0x10d580) and
// UNetConnection::ReceivedRawPacket (0x10d5f0). Names inferred from the
// UE2 shape of the code (FBitWriter/FBitReader temporaries built from
// MaxPacket and the raw packet, InBytes/InPackets counters). This object was
// built with LTCG; the callees FBitWriter::FBitWriter, FBitReader::FBitReader,
// FBitReader::~FBitReader and UNetConnection::ReceivedPacket take `this` on the
// stack in retail, written here as __stdcall members.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;

void *appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);
};

template<class T> class TArray : public FArray
{
public:
    TArray();
    ~TArray();
    TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            Empty(sizeof(T), Other.ArrayNum);
            appMemcpy(Data, Other.Data, sizeof(T) * Other.ArrayNum);
            ArrayNum = Other.ArrayNum;
        }
        return *this;
    }
};

class FArchive
{
public:
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);
    BYTE ArPad[0x3c];
};

class FBitWriter : public FArchive
{
public:
    TArray<BYTE> Buffer;    // 0x40
    _WORD Num;              // 0x4c
    _WORD Max;              // 0x4e
    FBitWriter(INT InMaxBits);
    FBitWriter &operator=(const FBitWriter &Other);
};

class FBitReader : public FArchive
{
public:
    TArray<BYTE> Buffer;
    _WORD Num;
    _WORD Pos;
    FBitReader(BYTE *Src, INT CountBits);
    ~FBitReader();
};

class UNetConnection
{
public:
    BYTE Pad0[0xc0];
    INT MaxPacket;          // 0xc0
    INT PacketOverhead;     // 0xc4
    BYTE Pad1[0x1e8 - 0xc8];
    INT InPackets;          // 0x1e8
    BYTE Pad2[0x1f8 - 0x1ec];
    INT InBytes;            // 0x1f8
    BYTE Pad3[0x23c - 0x1fc];
    FBitWriter Out;         // 0x23c

    void InitOut();
    void ReceivedRawPacket(void *InData, INT Count);
    void __stdcall ReceivedPacket(FBitReader &Reader);
};

#pragma auto_inline(off)
FBitWriter &FBitWriter::operator=(const FBitWriter &Other)
{
    Buffer = Other.Buffer;
    Num = Other.Num;
    Max = Other.Max;
    return *this;
}
#pragma auto_inline(on)

void UNetConnection::InitOut()
{
    Out = FBitWriter(MaxPacket);
}

void UNetConnection::ReceivedRawPacket(void *InData, INT Count)
{
    BYTE *Data = (BYTE *)InData;
    InBytes += Count + PacketOverhead;
    InPackets++;
    if (Count > 0)
    {
        BYTE LastByte = Data[Count - 1];
        if (LastByte)
        {
            INT BitSize = Count * 8 - 1;
            while (!(LastByte & 0x80))
            {
                LastByte *= 2;
                BitSize--;
            }
            FBitReader Reader(Data, BitSize);
            ReceivedPacket(Reader);
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Ext(void *, INT);
#pragma auto_inline(off)
FBitWriter::FBitWriter(INT InMaxBits)
{
    INT Bytes = (InMaxBits + 7) >> 3;
    for (INT i = 0; i < Bytes; i++) Ext(this, i * InMaxBits + Bytes);
    Ext(&Buffer, Bytes); Num = 0; Max = (_WORD)InMaxBits;
    Ext(Buffer.Data, Buffer.ArrayNum + Bytes);
}
FBitReader::FBitReader(BYTE *Src, INT CountBits)
{
    INT Bytes = (CountBits + 7) >> 3;
    for (INT i = 0; i < Bytes; i++) Ext(Src + i, i * CountBits + Bytes);
    Ext(&Buffer, Bytes); Num = (_WORD)CountBits; Pos = 0;
    Ext(Src, Buffer.ArrayNum + Bytes);
}
FBitReader::~FBitReader() { Ext(this, 0); }
#pragma auto_inline(on)
void Driver_10d580(UNetConnection *C) { void (UNetConnection::*P)() = &UNetConnection::InitOut; Escape(&P); C->InitOut(); }
void Driver_10d5f0(UNetConnection *C, void *D, INT N) { C->ReceivedRawPacket(D, N); }
