// Work item 0180 (RVA 0xe0020-0xe04d4): UChannel::SendBunch and its helpers.
// Names follow UE2 UnChan.cpp: the "FOutBunch" allocation tag, the reliable
// buffer limit of 127, the merge test against LastOut/LastEnd and the
// SetClosingFlag call on bClose identify UChannel::SendBunch and
// UChannel::IsNetReady. The copy constructors and assignment operators are the
// compiler-generated members of FArchive, FBitWriter and FOutBunch.
// This object was built with LTCG (custom register conventions) and only
// explicitly inline functions inlined (match flags /O2 /Ob1 /Gy /GX); see the
// drivers at the end. FArchive's copy constructor and FBitWriter's assignment
// are written out of line because retail calls them rather than inlining them.
// Retail inlines the final LastOut assignment in SendBunch but calls
// FOutBunch::operator= for the merge case, so that copy is spelled out member
// by member here.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

void *appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
extern const TCHAR FOutBunchTag[]; // L"FOutBunch"
extern const TCHAR FArrayTag[];    // L"FArray"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);
    FArray(INT InNum, INT ElementSize)
    :   ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArrayTag);
    }
    ~FArray();
};

template<class T> class TArray : public FArray
{
public:
    TArray(const TArray &Other);
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

// TArray copy constructor (RVA 0xe1a90), out of line in retail.
template<class T> TArray<T>::TArray(const TArray &Other)
:   FArray(Other.ArrayNum, sizeof(T))
{
    appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
}

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    INT ArIsLoading;
    INT ArIsSaving;
    INT ArIsTrans;
    INT ArIsPersistent;
    INT ArForEdit;
    INT ArForClient;
    INT ArForServer;
    INT ArIsError;          // 0x2c
    INT ArIsCriticalError;
    INT ArMaxSerializeSize;
    INT ArPad0;
    INT ArPad1;
    FArchive(const FArchive &Other);
    FArchive &operator=(const FArchive &) { return *this; }
};

FArchive::FArchive(const FArchive &Other)
:   ArVer(Other.ArVer), ArNetVer(Other.ArNetVer), ArLicenseeVer(Other.ArLicenseeVer),
    ArIsLoading(Other.ArIsLoading), ArIsSaving(Other.ArIsSaving), ArIsTrans(Other.ArIsTrans),
    ArIsPersistent(Other.ArIsPersistent), ArForEdit(Other.ArForEdit), ArForClient(Other.ArForClient),
    ArForServer(Other.ArForServer), ArIsError(Other.ArIsError), ArIsCriticalError(Other.ArIsCriticalError),
    ArMaxSerializeSize(Other.ArMaxSerializeSize), ArPad0(Other.ArPad0), ArPad1(Other.ArPad1)
{
}

class FBitWriter : public FArchive
{
public:
    TArray<BYTE> Buffer;    // 0x40
    _WORD Num;              // 0x4c
    _WORD Max;              // 0x4e
    BYTE *GetData() { return &((BYTE *)Buffer.Data)[0]; }
    _WORD GetNumBits() { return Num; }
    _WORD GetNumBytes() { return (Num + 7) >> 3; }
    FBitWriter &operator=(const FBitWriter &Other);
};

FBitWriter &FBitWriter::operator=(const FBitWriter &Other)
{
    Buffer = Other.Buffer;
    Num = Other.Num;
    Max = Other.Max;
    return *this;
}

class FBitWriterMark
{
public:
    UBOOL Overflowed;
    _WORD Num;
    FBitWriterMark() {}
    FBitWriterMark(FBitWriter &Writer) : Overflowed(Writer.ArIsError), Num(Writer.GetNumBits()) {}
    void __stdcall Pop(FBitWriter &Writer);
};

class UChannel;

struct FTime { DWORD Lo, Hi; };

class FOutBunch : public FBitWriter
{
public:
    FOutBunch *Next;        // 0x50
    UChannel *Channel;      // 0x54
    FTime Time;             // 0x58
    INT ChIndex;            // 0x60
    INT ChType;             // 0x64
    INT ChSequence;         // 0x68
    INT PacketId;           // 0x6c
    BYTE bOpen;             // 0x70
    BYTE bClose;            // 0x71
    BYTE bReliable;         // 0x72
    BYTE ReceivedAck;       // 0x73
};

struct FNetQueue            // unnamed sub-object at UNetConnection+0x68
{
    BYTE Pad[0x8c];
    INT QueuedBytes;        // 0x8c
};

class UNetConnection
{
public:
    BYTE Pad0[0x68];
    FNetQueue *Queue;       // 0x68
    BYTE Pad1[0xb8 - 0x6c];
    INT OutBunches;         // 0xb8
    BYTE Pad2[0xc0 - 0xbc];
    INT MaxPacket;          // 0xc0
    BYTE Pad3[0x104 - 0xc4];
    FBitWriterMark LastStart;   // 0x104
    FBitWriterMark LastEnd;     // 0x10c
    UBOOL AllowMerge;           // 0x114
    INT Pad4;                   // 0x118
    FOutBunch *LastOutBunch;    // 0x11c
    FOutBunch LastOut;          // 0x120
    BYTE Pad5[0x1f4 - 0x194];
    INT OutBunAcc;              // 0x1f4
    BYTE Pad6[0x23c - 0x1f8];
    FBitWriter Out;             // 0x23c
    BYTE Pad7[0x16ec - 0x28c];
    INT OutReliable[1];         // 0x16ec

    INT __stdcall SendRawBunch(FOutBunch &Bunch, UBOOL InAllowMerge);
    UBOOL IsNetReady(UBOOL Saturate)
    {
        if (Saturate)
            Queue->QueuedBytes = -Out.GetNumBytes();
        return Queue->QueuedBytes + Out.GetNumBytes() <= 0;
    }
};

class UChannel
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22();
    virtual void SetClosingFlag();  // slot 0x5c

    BYTE ObjPad[0x28 - 4];
    UNetConnection *Connection; // 0x28
    INT ChIndex;                // 0x2c
    INT OpenPacketId;           // 0x30
    INT Pad34;
    INT NumOutRec;              // 0x38
    INT Pad3c;
    INT Pad40;
    FOutBunch *OutRec;          // 0x44
    INT OutBytes;               // 0x48
    INT Pad4c;
    INT Pad50;
    _WORD Pad54;
    _WORD OpenTemporary : 1;    // 0x56 bit 0
    _WORD OpenedLocally : 1;    // 0x56 bit 1

    INT SendBunch(FOutBunch *Bunch, UBOOL Merge);
    UBOOL IsNetReady(UBOOL Saturate);
};

INT UChannel::SendBunch(FOutBunch *Bunch, UBOOL Merge)
{
    OutBytes += Bunch->GetNumBytes();

    // Set bunch flags.
    if (OpenPacketId == -1 && OpenedLocally)
    {
        Bunch->bOpen = 1;
        OpenTemporary = !Bunch->bReliable;
    }

    // Contemplate merging.
    FOutBunch *OutBunch = 0;
    if (Merge
        && Connection->LastOut.ChIndex == Bunch->ChIndex
        && Connection->AllowMerge
        && Connection->LastEnd.Num
        && Connection->LastEnd.Num == Connection->Out.GetNumBits()
        && Connection->Out.GetNumBits() + Bunch->GetNumBits() + 65 <= Connection->MaxPacket)
    {
        Connection->LastOut.SerializeBits(Bunch->GetData(), Bunch->GetNumBits());
        Connection->LastOut.bReliable |= Bunch->bReliable;
        Connection->LastOut.bOpen |= Bunch->bOpen;
        Connection->LastOut.bClose |= Bunch->bClose;
        OutBunch = Connection->LastOutBunch;
        Bunch = &Connection->LastOut;
        Connection->LastStart.Pop(Connection->Out);
        Connection->OutBunAcc--;
    }

    // Find outgoing bunch index.
    if (Bunch->bReliable)
    {
        if (!OutBunch)
        {
            Bunch->Next = 0;
            Bunch->ChSequence = ++Connection->OutReliable[ChIndex];
            NumOutRec++;
            Connection->OutBunches++;
            OutBunch = new(FOutBunchTag) FOutBunch(*Bunch);
            FOutBunch **OutLink;
            for (OutLink = &OutRec; *OutLink; OutLink = &(*OutLink)->Next);
            *OutLink = OutBunch;
        }
        else
        {
            Bunch->Next = OutBunch->Next;
            *OutBunch = *Bunch;
        }
        Connection->LastOutBunch = OutBunch;
    }
    else
    {
        OutBunch = Bunch;
        Connection->LastOutBunch = 0;
    }

    // Send the raw bunch.
    OutBunch->ReceivedAck = 0;
    INT PacketId = Connection->SendRawBunch(*OutBunch, 1);
    if (OpenPacketId == -1 && OpenedLocally)
        OpenPacketId = PacketId;
    if (OutBunch->bClose)
        SetClosingFlag();

    // Update channel sequence count.
    FOutBunch &Last = Connection->LastOut;
    Last.Buffer = OutBunch->Buffer;
    Last.Num = OutBunch->Num;
    Last.Max = OutBunch->Max;
    Last.Next = OutBunch->Next;
    Last.Channel = OutBunch->Channel;
    Last.Time = OutBunch->Time;
    Last.ChIndex = OutBunch->ChIndex;
    Last.ChType = OutBunch->ChType;
    Last.ChSequence = OutBunch->ChSequence;
    Last.PacketId = OutBunch->PacketId;
    Last.bOpen = OutBunch->bOpen;
    Last.bClose = OutBunch->bClose;
    Last.bReliable = OutBunch->bReliable;
    Last.ReceivedAck = OutBunch->ReceivedAck;
    Connection->LastEnd = FBitWriterMark(Connection->Out);

    return PacketId;
}

UBOOL UChannel::IsNetReady(UBOOL Saturate)
{
    if (NumOutRec >= 127)
        return 0;
    return Connection->IsNetReady(Saturate);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_e0090(UChannel *C, FOutBunch *B, FOutBunch *B2, UBOOL M)
{
    Escape(&GMalloc);
    C->SendBunch(B, M);
    return C->SendBunch(B2, 0);
}
UBOOL Driver_e0480(UChannel *C, UChannel *D, UBOOL S)
{
    return C->IsNetReady(S) && D->IsNetReady(0) && C->IsNetReady(1);
}
