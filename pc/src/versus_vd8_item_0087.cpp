// Work item 0087 (Versus RVA 0x14a580-0x14a85d):
// FOutBunch (Unreal Engine 2 UnNet.h / UnBunch.cpp), FBitWriter::Reset,
// and an unnamed 0x3c-byte Magma object factory (0x14a800).

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { MAX_BUNCH_OVERHEAD_BITS = 0x51 };
enum { RELIABLE_BUFFER = 128 };

extern "C" void *__cdecl memset(void *Dest, int Val, unsigned int Size);
#pragma intrinsic(memset)
void *appMemcpy(void *Dest, const void *Src, INT Count);

inline void appMemzero(void *Dest, INT Count)
{
    memset(Dest, 0, Count);
}

extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor" (0x10c10944)
extern const TCHAR Text_Magma[];               // L"Magma" (0x10c47428)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum)
        , ArrayMax(InNum)
    {
        if (ArrayMax == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    void Empty(INT ElementSize, INT Slack);
};

template<class T> class TArray : public FArray
{
public:
    TArray(INT InNum)
        : FArray(InNum, sizeof(T))
    {
    }
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

    T &operator()(INT i)
    {
        return ((T *)Data)[i];
    }
};

class FName;
class UObject;
class UClass;
class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(FName &N);
    virtual FArchive &operator<<(UObject *&Res);
    virtual INT MapName(FName *Name);
    virtual INT MapObject(UObject *Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual void Seek(INT InPos);
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader);
    virtual void DetachLazyLoader(FLazyLoader *LazyLoader);
    virtual void Precache(INT HintCount);
    virtual void VirtualSlot17();
    virtual UBOOL Close();
    virtual void Flush();

    BYTE unk_04[0x28];
    UBOOL ArIsError;    // 0x2c
    BYTE unk_30[0x10];
};

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    BYTE unk_04[0x24];

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UPackageMap : public UObject
{
public:
    virtual UBOOL CanSerializeObject(UObject *Obj);
    virtual UBOOL SerializeObject(FArchive &Ar, UClass *Class, UObject *&Obj);
    virtual UBOOL SerializeName(FArchive &Ar, FName &Name);
};

class UNetConnection
{
public:
    BYTE unk_00[0xb4];
    UPackageMap *PackageMap; // 0xb4
    BYTE unk_b8[0x08];
    INT MaxPacket;           // 0xc0
};

class UChannel : public UObject
{
public:
    UNetConnection *Connection; // 0x28
    INT ChIndex;                // 0x2c
    BYTE unk_30[0x08];
    INT NumOutRec;              // 0x38
    BYTE unk_3c[0x18];
    _WORD ChType;               // 0x54
};

class FBitWriter : public FArchive
{
public:
    TArray<BYTE> Buffer;    // 0x40
    _WORD Num;              // 0x4c
    _WORD Max;              // 0x4e

    FBitWriter(INT InMaxBits);
    void Reset(INT InMaxBits);
    void SetOverflowed() { ArIsError = 1; }
    void Reset()
    {
        Num = 0;
        ArIsError = 0;
        appMemzero(&Buffer(0), (Max + 7) / 8);
    }
};

class FOutBunch : public FBitWriter
{
public:
    BYTE unk_50[0x04];
    UChannel *Channel;      // 0x54
    BYTE unk_58[0x08];
    INT ChIndex;            // 0x60
    INT ChType;             // 0x64
    BYTE unk_68[0x08];
    BYTE bOpen;             // 0x70
    BYTE bClose;            // 0x71
    BYTE bReliable;         // 0x72
    BYTE unk_73;

    FOutBunch(UChannel *InChannel, UBOOL bInClose);
    void Init(UChannel *InChannel, BYTE bInClose, BYTE bInReliable);
    FArchive &operator<<(FName &N);
    FArchive &operator<<(UObject *&Object);
};

// RVA 0x14a580: FOutBunch::FOutBunch
FOutBunch::FOutBunch(UChannel *InChannel, UBOOL bInClose)
    : FBitWriter(InChannel->Connection->MaxPacket - MAX_BUNCH_OVERHEAD_BITS)
    , Channel(InChannel)
    , ChIndex(InChannel->ChIndex)
    , ChType(InChannel->ChType)
    , bOpen(0)
    , bClose((BYTE)bInClose)
    , bReliable(0)
{
    if (Channel->NumOutRec >= RELIABLE_BUFFER - 1 + bClose)
    {
        SetOverflowed();
    }
}

// RVA 0x14a5e0: FOutBunch::Init (near miss: retail inlines UE2's UnVcWin32.h
// inline-asm appMemzero, which also disables global register optimization here).
void FOutBunch::Init(UChannel *InChannel, BYTE bInClose, BYTE bInReliable)
{
    INT MaxBits = InChannel->Connection->MaxPacket - MAX_BUNCH_OVERHEAD_BITS;
    if (Max < MaxBits)
    {
        Reset(MaxBits);
    }
    else
    {
        Reset();
    }
    Channel = InChannel;
    ChIndex = InChannel->ChIndex;
    ChType = InChannel->ChType;
    bOpen = 0;
    bClose = bInClose;
    bReliable = bInReliable;
}

// RVA 0x14a6a0: FOutBunch::operator<<(FName &)
FArchive &FOutBunch::operator<<(FName &N)
{
    Channel->Connection->PackageMap->SerializeName(*this, N);
    return *this;
}

// RVA 0x14a6c0: FOutBunch::operator<<(UObject *&)
FArchive &FOutBunch::operator<<(UObject *&Object)
{
    Channel->Connection->PackageMap->SerializeObject(*this, UObject::StaticClass(), Object);
    return *this;
}

// RVA 0x14a6f0: FBitWriter::Reset(INT) (near miss: retail inlines UE2's
// UnVcWin32.h inline-asm appMemzero, which disables global register
// optimization and keeps `this` on the stack).
void FBitWriter::Reset(INT InMaxBits)
{
    Max = (_WORD)InMaxBits;
    Buffer = TArray<BYTE>((InMaxBits + 7) / 8);
    Reset();
}

// Unnamed 0x3c-byte Magma object (base ctor 0x10b9f4d0, derived ctor 0x10a4c100,
// vtable 0x10c0348c, operator delete 0x10a4c0f0).
class UnnamedMagmaBase_14a800
{
public:
    UnnamedMagmaBase_14a800();
    ~UnnamedMagmaBase_14a800();
    BYTE unk_00[0x34];
};

class UnnamedMagmaObject_14a800 : public UnnamedMagmaBase_14a800
{
public:
    INT unk_34;
    INT unk_38;

    static void *operator new(unsigned int Size)
    {
        return GMalloc->Malloc(Size, Text_Magma);
    }
    static void operator delete(void *Ptr);

    UnnamedMagmaObject_14a800();
};

// RVA 0x14a800: CreateMagmaObject_14a800 (factory for UnnamedMagmaObject_14a800)
UnnamedMagmaObject_14a800 *CreateMagmaObject_14a800()
{
    return new UnnamedMagmaObject_14a800();
}

// Scaffolding for LTCG links, not part of the unit.
void Escape(void *);
void Ext(void *, INT);

#pragma auto_inline(off)
FBitWriter::FBitWriter(INT InMaxBits)
    : Buffer((InMaxBits + 7) / 8)
{
    INT Bytes = (InMaxBits + 7) >> 3;
    for (INT i = 0; i < Bytes; i++)
    {
        Ext(this, i * InMaxBits + Bytes);
    }
    Ext(&Buffer, Bytes);
    Num = 0;
    Max = (_WORD)InMaxBits;
    Ext(Buffer.Data, Buffer.ArrayNum + Bytes);
}

UnnamedMagmaObject_14a800::UnnamedMagmaObject_14a800()
{
    unk_34 = 0;
    unk_38 = 0;
    Ext(this, 0);
}
#pragma auto_inline(on)

void Driver_14a580(UChannel *C, UBOOL bClose, INT n)
{
    if (n == 0) { FOutBunch B(C, bClose); Ext(&B, 0); }
    else if (n == 1) { FOutBunch B(C, 0); Ext(&B, 1); }
    else if (n == 2) { FOutBunch B(C, 1); Ext(&B, 2); }
    else if (n == 3) { FOutBunch B(C, bClose); Ext(&B, 3); }
    else if (n == 4) { FOutBunch B(C, 0); Ext(&B, 4); }
    else { FOutBunch B(C, 1); Ext(&B, 5); }
    Ext(C, n);
}

void Driver_14a5e0(FOutBunch *B, UChannel *C, BYTE bClose, BYTE bReliable)
{
    B->Init(C, bClose, bReliable);
}

void Driver_14a6f0(FBitWriter *W, INT MaxBits)
{
    Escape(&GMalloc);
    W->Reset(MaxBits);
}

UnnamedMagmaObject_14a800 *Driver_14a800()
{
    Escape(&GMalloc);
    return CreateMagmaObject_14a800();
}
