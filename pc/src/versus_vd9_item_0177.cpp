typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef int INT;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) double __cdecl floor(double);

// FArchive from Unreal Engine 2 (only the slots used here).
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);            // slot 1
    virtual void SerializeBits(void* V, INT LengthBits);    // slot 2
    virtual void SerializeInt(DWORD& Value, DWORD Max);     // slot 3
    INT ArVer;                                              // +0x04
    INT ArNetVer;                                           // +0x08
    INT ArLicenseeVer;                                      // +0x0c
    UBOOL ArIsLoading;                                      // +0x10
    UBOOL IsLoading() { return ArIsLoading; }
    FArchive& operator<<(BYTE& B) { Serialize(&B, 1); return *this; }
};

inline INT appRound(FLOAT F) { return (INT)floor(F + 0.5f); }
template<class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Clamp(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }

// Retail 0x12050 (published as CeilLog2_12050); defined here so the LTCG
// link gives it its retail register convention (argument in EDX).
extern const BYTE CeilLogTable_12050[256];
__declspec(noinline) BYTE appCeilLogTwo(DWORD Arg)
{
    if (--Arg == (DWORD)-1)
        return 0;
    BYTE Shift = Arg <= 0x10000 ? (Arg <= 0x100 ? 0 : 8) : (Arg <= 0x1000000 ? 16 : 24);
    return Shift + CeilLogTable_12050[Arg >> Shift];
}

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    void SerializeCompressed(FArchive& Ar);
};

class FRotator
{
public:
    INT Pitch, Yaw, Roll;
    void SerializeCompressed(FArchive& Ar);
};

// RVA 0xdf840: UE2 FRotator::SerializeCompressed shape (free function to
// match the vector one). Near: the linker passes Ar in ESI here, retail in EAX.
__declspec(noinline) void SerializeCompressedRotator(FArchive& Ar, FRotator& R)
{
    BYTE BytePitch = R.Pitch >> 8;
    BYTE ByteYaw = R.Yaw >> 8;
    BYTE ByteRoll = R.Roll >> 8;

    BYTE B = (BytePitch != 0);
    Ar.SerializeBits(&B, 1);
    if (B) Ar << BytePitch; else BytePitch = 0;

    B = (ByteYaw != 0);
    Ar.SerializeBits(&B, 1);
    if (B) Ar << ByteYaw; else ByteYaw = 0;

    B = (ByteRoll != 0);
    Ar.SerializeBits(&B, 1);
    if (B) Ar << ByteRoll; else ByteRoll = 0;

    if (Ar.IsLoading())
    {
        R.Pitch = BytePitch << 8;
        R.Yaw = ByteYaw << 8;
        R.Roll = ByteRoll << 8;
    }
}

// RVA 0xdf930: UE2 FVector::SerializeCompressed shape, written as a free
// function: retail is caller-pop with the vector on the stack, which a
// member function under LTCG does not give (it becomes ret 4).
__declspec(noinline) void SerializeCompressedVector(FArchive& Ar, FVector& V)
{
    INT IntX = appRound(V.X);
    INT IntY = appRound(V.Y);
    INT IntZ = appRound(V.Z);
    DWORD Bits = Clamp<DWORD>(appCeilLogTwo(1 + Max(Max(Abs(IntX), Abs(IntY)), Abs(IntZ))), 1, 20) - 1;
    Ar.SerializeInt(Bits, 20);
    INT Bias = 1 << (Bits + 1);
    DWORD Max = 1 << (Bits + 2);
    DWORD DX = IntX + Bias;
    DWORD DY = IntY + Bias;
    DWORD DZ = IntZ + Bias;
    Ar.SerializeInt(DX, Max);
    Ar.SerializeInt(DY, Max);
    Ar.SerializeInt(DZ, Max);
    if (Ar.IsLoading())
        V = FVector((INT)DX - Bias, (INT)DY - Bias, (INT)DZ - Bias);
}

// RVA 0xdfab0: neutral names. Serializes a compressed location and,
// optionally, rotation, mirroring them into a recorder's state block.
struct UnnamedState_dfab0
{
    char Pad00[0x80];
    FVector Location;                   // +0x80
    char Pad8c[0xe0 - 0x8c];
    FRotator Rotation;                  // +0xe0
};
struct UnnamedRecorder_dfab0
{
    char Pad00[0x8c];
    UnnamedState_dfab0* State;          // +0x8c
    UBOOL bActive;                      // +0x90
};

__declspec(noinline) void SerializeMovement_dfab0(FArchive& Ar, FRotator& Rotation, UnnamedRecorder_dfab0* Recorder, FVector& Location, UBOOL bRotation)
{
    SerializeCompressedVector(Ar, Location);
    if (Recorder && Recorder->bActive)
        Recorder->State->Location = Location;
    if (bRotation)
    {
        SerializeCompressedRotator(Ar, Rotation);
        if (Recorder && Recorder->bActive)
            Recorder->State->Rotation = Rotation;
    }
}


// RVA 0xdfb30: neutral names; the node and its link share the UObject flag
// word at +0x1c (bit 1 tested on the link, bit 23 = pending, bit 31 cleared
// on relink). Index at +4 compared against INDEX_NONE.
class UnnamedNode_dfb30
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08();
    virtual void Refresh();             // slot 9
    INT Index;                          // +0x04
    char Pad08[0x14];
    DWORD Flags;                        // +0x1c
    char Pad20[0x08];
    UnnamedNode_dfb30* Link;            // +0x28
};
class UnnamedOwner_dfb30;

__declspec(noinline) UBOOL RelinkNode_dfb30(UnnamedNode_dfb30* Node)
{
    UnnamedNode_dfb30* Link = Node->Link;
    if (Link && (Link->Flags & 2))
    {
        Node->Flags &= ~0x800000;
        if (Link->Index != -1 && !(Link->Flags & 0x800000))
        {
            Link->Flags = (Link->Flags & 0x7f7fffff) | 0x800000;
            Link->Refresh();
            return 1;
        }
        Node->Flags |= 0x800000;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// UE2 UnChan.cpp: UChannel::Close (0xdfb90) and UChannel::Destroy (0xdfc20).
// ---------------------------------------------------------------------------
enum EConnectionState { USOCK_Invalid = 0, USOCK_Closed = 1, USOCK_Pending = 2, USOCK_Open = 3 };

// FArray from Unreal Engine 2; Remove is retail 0x109119c0.
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize);
};

class UChannel;
class UNetConnection
{
public:
    char Pad00[0x6c];
    INT State;                              // +0x6c
    char Pad70[0xef0 - 0x70];
    UChannel* Channels[(0x26fc - 0xef0) / 4]; // +0xef0
    FArray OpenChannels;                    // +0x26fc, TArray<UChannel*>
};

class FInBunch
{
public:
    virtual ~FInBunch();
    char Pad04[0x4c];
    FInBunch* Next;                         // +0x50
};

class FOutBunch
{
public:
    char Pad04[0x4c];
    FOutBunch* Next;                        // +0x50
    char Pad54[0x72 - 0x54];
    BYTE bReliable;                         // +0x72
    BYTE bClose;                            // +0x73
    FOutBunch(UChannel* InChannel, UBOOL bClose);
    virtual ~FOutBunch();
};

class UObject
{
public:
    virtual ~UObject();
    void Destroy();                         // retail 0x10915ce0
};

class UChannel : public UObject
{
public:
    virtual void Close();
    char Pad04[0x24];
    UNetConnection* Connection;             // +0x28
    INT ChIndex;                            // +0x2c
    char Pad30[0x10];
    FOutBunch* OutRec;                      // +0x40
    FInBunch* InRec;                        // +0x44
    char Pad48[0x56 - 0x48];
    BYTE Pad56Bits : 5;
    BYTE Closing : 1;                       // +0x56 bit 5
    INT SendBunch(FOutBunch* Bunch, UBOOL Merge);
    void Destroy();
};

// RVA 0xdfb90: UE2 UChannel::Close.
void UChannel::Close()
{
    if (!Closing && (Connection->State == USOCK_Open || Connection->State == USOCK_Pending))
    {
        FOutBunch CloseBunch(this, 1);
        CloseBunch.bReliable = 1;
        SendBunch(&CloseBunch, 0);
    }
}

// RVA 0xdfc20: UE2 UChannel::Destroy (checks compiled out).
void UChannel::Destroy()
{
    for (FInBunch* In = InRec; In; )
    {
        FInBunch* Next = In->Next;
        delete In;
        In = Next;
    }
    for (FOutBunch* Out = OutRec; Out; )
    {
        FOutBunch* Next = Out->Next;
        delete Out;
        Out = Next;
    }
    FArray& Open = Connection->OpenChannels;
    for (INT i = 0; i < Open.ArrayNum; i++)
    {
        if (((UChannel**)Open.Data)[i] == this)
            Open.Remove(i--, 1, sizeof(UChannel*));
    }
    Connection->Channels[ChIndex] = 0;
    Connection = 0;
    UObject::Destroy();
}

// ===========================================================================
// Scaffolding for the LTCG links, not part of the unit. The bunch
// constructor/destructor and SendBunch are defined only so the linker gives
// them link-time conventions like retail's; their bodies are placeholders.
// ===========================================================================
void Escape(void*);
class FMalloc { public: virtual void* Malloc(DWORD, const TCHAR*); virtual void* Realloc(void*, DWORD, const TCHAR*); virtual void Free(void*); };
extern FMalloc* GMalloc;
__declspec(noinline) FOutBunch::FOutBunch(UChannel* InChannel, UBOOL InClose)
{
    Escape(InChannel->Connection);
    Escape(this);
    *(UChannel**)Pad04 = InChannel;
    *(INT*)(Pad04 + 4) = InChannel->ChIndex;
    bClose = (BYTE)InClose;
    bReliable = 0;
}
__declspec(noinline) FOutBunch::~FOutBunch()
{
    void*& Data = *(void**)(Pad04 + 0x1c);
    if (Data) GMalloc->Free(Data);
    Data = 0;
}
__declspec(noinline) INT UChannel::SendBunch(FOutBunch* Bunch, UBOOL Merge)
{
    INT Result = Bunch->bReliable + ChIndex;
    if (Merge) Escape(Connection);
    return Result;
}
inline void* operator new(unsigned int, void* Mem) { return Mem; }
void Driver_dfb90(UChannel* C, void* Mem) { C->Close(); Escape(new (Mem) UChannel); }
INT Driver_dfb30(UnnamedOwner_dfb30* Owner, UnnamedNode_dfb30* Node) { return RelinkNode_dfb30(Node); }
void Driver_dfab0(FArchive& Ar, FRotator& Rotation, UnnamedRecorder_dfab0* Recorder, FVector& Location, UBOOL bRotation)
{
    SerializeMovement_dfab0(Ar, Rotation, Recorder, Location, bRotation);
}
