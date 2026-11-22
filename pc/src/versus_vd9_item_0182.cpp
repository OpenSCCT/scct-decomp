// Work item w3 0182: Versus RVA 0xe0580-0xe0719 (Engine UnChan.cpp, UControlChannel).
//
// 0xe0580 UControlChannel::Destroy        (vtable 0x3045b8 slot 9)
// 0xe05a0 UControlChannel::ReceivedBunch  (vtable 0x3045b8 slot 25)
// 0xe0660 UControlChannel::Serialize      (FOutputDevice subobject at +0x58,
//                                          vtable 0x304628 slot 0)
//
// The unit was compiled /GL and linked /LTCG: the helpers it calls
// (UChannel::RouteDestroy at 0xdfb30, operator<<(FArchive&,FString&) at
// 0x11b80, FOutBunch::FOutBunch at 0x14a580, UChannel::SendBunch at 0xe0090)
// take custom register conventions, so they are defined below for the linker
// to choose those conventions. Names follow Unreal Engine 2.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef double DOUBLE;

enum EName { NAME_None = 0 };

enum
{
    RF_Unreachable  = 0x00000002,
    RF_Destroyed    = 0x00800000,
    RF_DebugDestroy = 0x80000000,
};

class UObject;
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArchive
{
public:
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(UObject *&Res);
    virtual void v1c(); virtual void v20(); virtual void v24();
    virtual INT GetStringKey(); // slot 0x28; Versus string obfuscation key (by use)

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsError() { return ArIsError; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    BYTE Pad18[0x14];
    UBOOL ArIsError;          // +0x2c
    UBOOL ArIsCriticalError;  // +0x30
    INT Pad34[2];
    INT ArMaxSerializeSize;   // +0x3c (by layout; FArchive is 0x40 bytes)

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArray();                // ??1?$TArray@E@@QAE@XZ, RVA 0xf250
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR *In); // RVA 0x46c0
    ~FString();               // RVA 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

// ---------------------------------------------------------------------------
// FString serialiser, RVA 0x11b80 (not part of this item; body from work item
// 0139, defined so the linker gives it the retail convention: Ar in EAX, S in EBX).
void FArray_Realloc(FString &S, INT ElementSize);
extern const TCHAR FArray_Tag[]; // L"FArray"
inline INT Abs(INT A) { return A >= 0 ? A : -A; }
struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))
// RVA 0x1ea40 (body approximated, not a match; defined so LINK /LTCG assigns its convention).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Original < 0 ? -Original : Original;
    BYTE B0 = (BYTE)(((Original >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        BYTE B1 = (BYTE)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
        Ar.Serialize(&B1, 1);
        I.Value = B1 & 0x7f;
    }
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}

void FString_Empty(FString &S, INT Slack);
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FString &A)
{
    // Body reduced (Core's FString serialiser is not part of this item).
    Ar.CountBytes(A.ArrayNum * sizeof(TCHAR), A.ArrayMax * sizeof(TCHAR));
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        FString_Empty(A, NewNum);
        A.ArrayNum = NewNum;
        Ar.Serialize(A.Data, NewNum * sizeof(TCHAR));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        Ar.Serialize(A.Data, A.ArrayNum * sizeof(TCHAR));
    }
    return Ar;
}

// ---------------------------------------------------------------------------
class UObject
{
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual ~UObject();       // slot 3 (deleting destructor)
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void Destroy();   // slot 9

    INT Index;                // +0x04
    BYTE Pad08[0x14];
    DWORD ObjectFlags;        // +0x1c
    BYTE Pad20[0x08];

    DWORD GetFlags() { return ObjectFlags; }
    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    void ClearFlags(DWORD NewFlags) { ObjectFlags &= ~NewFlags; }
    UBOOL ConditionalDestroy()
    {
        if (Index != -1 && !(GetFlags() & RF_Destroyed))
        {
            SetFlags(RF_Destroyed);
            ClearFlags(RF_DebugDestroy);
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UNetConnection;
class FNetworkNotify
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void NotifyReceivedText(UNetConnection *Connection, const TCHAR *Text); // slot 4
};

class UNetDriver : public UObject
{
public:
    BYTE Pad28[0x14];
    FNetworkNotify *Notify;   // +0x3c
};

class UNetConnection : public UObject
{
public:
    BYTE Pad28[0x40];
    UNetDriver *Driver;       // +0x68
    BYTE Pad6c[0x54];
    INT MaxPacketBits;        // +0xc0 (by use)
    INT SendRawBunch(class FOutBunch &Bunch, UBOOL InAllowMerge); // RVA 0x10e140
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    UBOOL bSuppressEventTag;
    UBOOL bAutoEmitLineTerminator;
};

class FBitWriter : public FArchive
{
public:
    FBitWriter(INT InMaxBits); // RVA 0x2207b0
    TArray<BYTE> Buffer;       // +0x40
    _WORD Num;                 // +0x4c
    _WORD Max;                 // +0x4e
};

class FInBunch : public FArchive
{
};

class UChannel;
#pragma pack(push, 4)
class FOutBunch : public FBitWriter
{
public:
    FOutBunch *Next;          // +0x50
    UChannel *Channel;        // +0x54
    DOUBLE Time;              // +0x58
    INT ChIndex;              // +0x60
    INT ChType;               // +0x64
    INT ChSequence;           // +0x68
    INT PacketId;             // +0x6c
    BYTE bOpen;               // +0x70
    BYTE bClose;              // +0x71
    BYTE bReliable;           // +0x72
    BYTE bReceivedAck;        // +0x73

    FOutBunch(UChannel *InChannel, UBOOL bInClose);
};
#pragma pack(pop)

#define RELIABLE_BUFFER 128

class UChannel : public UObject
{
public:
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void ReceivedBunch(FInBunch &Bunch); // slot 25

    UNetConnection *Connection; // +0x28
    INT ChIndex;                // +0x2c
    INT OpenPacketId;           // +0x30
    INT Pad34;
    INT NumOutRec;              // +0x38
    INT Pad3c;
    FOutBunch *InRec;           // +0x40
    FOutBunch *OutRec;          // +0x44
    INT NumOutBits;             // +0x48
    INT Pad4c[2];
    _WORD ChType;               // +0x54
    _WORD Flags;                // +0x56

    void Destroy();             // RVA 0xdfc20
    UBOOL RouteDestroy();
    INT SendBunch(FOutBunch *Bunch, UBOOL Merge);
};

class UControlChannel : public UChannel, public FOutputDevice
{
public:
    void Destroy();
    void ReceivedBunch(FInBunch &Bunch);
    void Serialize(const TCHAR *Data, EName MsgType);
};

// RVA 0x14a580 (not part of this item; UnBunch.cpp).
__declspec(noinline) FOutBunch::FOutBunch(UChannel *InChannel, UBOOL bInClose)
    : FBitWriter(InChannel->Connection->MaxPacketBits - 0x51)
    , Channel(InChannel)
    , ChIndex(InChannel->ChIndex)
    , ChType(InChannel->ChType)
    , bOpen(0)
    , bClose(bInClose)
    , bReliable(0)
{
    if (Channel->NumOutRec >= RELIABLE_BUFFER - 1 + bClose)
        ArIsError = 1;
}

// RVA 0xdfb30 (not part of this item).
__declspec(noinline) UBOOL UChannel::RouteDestroy()
{
    if (Connection && (Connection->GetFlags() & RF_Unreachable))
    {
        ClearFlags(RF_Destroyed);
        if (Connection->ConditionalDestroy())
            return 1;
        SetFlags(RF_Destroyed);
    }
    return 0;
}

// RVA 0xe0090 (not part of this item; body reduced, not a match; defined so
// LINK /LTCG gives it the retail convention: this in ECX, Bunch in EAX).
__declspec(noinline) INT UChannel::SendBunch(FOutBunch *Bunch, UBOOL Merge)
{
    if (Bunch->bReliable)
        NumOutRec++;
    return Connection->SendRawBunch(*Bunch, Merge);
}

// ---------------------------------------------------------------------------
// RVA 0xe0580
void UControlChannel::Destroy()
{
    if (RouteDestroy())
        return;
    UChannel::Destroy();
}

// RVA 0xe05a0
void UControlChannel::ReceivedBunch(FInBunch &Bunch)
{
    for (;;)
    {
        FString Text;
        Bunch << Text;
        if (Bunch.IsError())
            break;
        Connection->Driver->Notify->NotifyReceivedText(Connection, *Text);
    }
}

// RVA 0xe0660
void UControlChannel::Serialize(const TCHAR *Data, EName MsgType)
{
    // Deliver the line to the remote.
    FOutBunch Bunch(this, 0);
    Bunch.bReliable = 1;
    FString Text = Data;
    Bunch << Text;
    if (!Bunch.IsError())
        SendBunch(&Bunch, 1);
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: constructing the object
// emits the vtables, which reference the three methods with standard
// conventions, as retail's vtables do.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_e0580(void *Mem, FArchive *Ar, FString *S)
{
    Escape(&GMalloc);
    *Ar << *S;
    Escape(new (Mem) UControlChannel);
}
